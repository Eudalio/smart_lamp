
const express = require('express')
let mqtt = require('mqtt')

const routes = express.Router();

let client = mqtt.connect([{ host: 'localhost', port: 1883}]);
let qtdPessoasNoQuarto = 0;


client.on('connect', function () {
  client.subscribe("casa/lampada")
  client.subscribe("casa/lampada/estado")
})

client.on('message', function (topic, message) {
  // message is Buffer
  let valor = parseInt(message.toString())
  if(topic == 'casa/lampada/estado' && valor >= 600 && qtdPessoasNoQuarto > 0) {
      client.publish("casa/lampada", "ligar")
      console.log(topic, valor)
  } else if(topic == 'casa/lampada/estado' && valor < 600) {
    client.publish("casa/lampada", "desligar")
    console.log(topic, valor)
  }
  
})

routes.get('/', (req, res) => {
    res.render('view', { qtd: qtdPessoasNoQuarto })
});

routes.post('/add', (req, res) => {
    qtdPessoasNoQuarto += parseInt(req.body.add);
    res.render('view', { qtd: qtdPessoasNoQuarto })
})

routes.post('/remove', (req, res) => {
    let value = parseInt(req.body.del);
    qtdPessoasNoQuarto <= 0 ? qtdPessoasNoQuarto : qtdPessoasNoQuarto -= value 
    res.render('view', { qtd: qtdPessoasNoQuarto })
})

routes.post('/acender', (req, res) => {
    let ligar = req.body.acender;
    console.log(ligar)
    client.publish("casa/lampada", ligar)
    res.render('view', { qtd: qtdPessoasNoQuarto })
})

routes.post('/apagar', (req, res) => {
    let desligar = req.body.apagar;
    console.log(desligar)
    client.publish("casa/lampada", desligar)
    res.render('view', { qtd: qtdPessoasNoQuarto })
})

module.exports = routes;
