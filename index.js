const express = require('express')
const bodyparser = require("body-parser")
const routes = require('./src/routes')

const app = express()

app.set("views", __dirname + '/src')
app.set("view engine", "ejs")
app.use(bodyparser.urlencoded({ extended: true }))

app.use('/', routes);

app.listen(8000, () => {
    console.log('Server listing on port 8000')
})
