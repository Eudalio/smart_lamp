#include <Ethernet.h>
#include <SPI.h>
#include <PubSubClient.h>
#include "RestClient.h"

int ledPin = 7; //Led no pino 7
int ldrPin = 0; //LDR no pino analígico 8
int ldrValor = 0; //Valor lido do LDR

byte mac[] = {  0xDE, 0xED, 0xBA, 0xFE, 0xFE, 0xED };
IPAddress ip(192, 168, 0, 110);
IPAddress server(192, 168, 0, 102);

EthernetClient ethClient;
PubSubClient client(ethClient);

//Setup
void setup() {
  Serial.begin(9600);
  pinMode(ledPin,OUTPUT); //define a porta 7 como saída
  
  // Connect via DHCP
  Serial.println("connect to network");
  Ethernet.begin(mac, ip);
  client.setServer(server, 1883);
  Serial.println("Setup!");
  
  client.setCallback(callback);

  //subscreve no tópico
  client.subscribe("casa/lampada");
}

void callback(char* topic, byte* payload, unsigned int length) {
 
  //armazena msg recebida em uma sring
  payload[length] = '\0';
  String strMSG = String((char*)payload);
 
  Serial.print("Mensagem chegou do tópico: ");
  Serial.println(topic);
  Serial.print("Mensagem:");
  Serial.print(strMSG);
  Serial.println();
  Serial.println("-----------------------");
 
  //aciona saída conforme msg recebida 
  if (strMSG == "ligar"){         //se msg "ligar"
    digitalWrite(ledPin, HIGH);    //coloca saída em LOW para ligar a Lampada
  }else if (strMSG == "desligar"){   //se msg "desligar"
     digitalWrite(ledPin, LOW);   //coloca saída em HIGH para desligar a Lampada
  }
}

//função pra reconectar ao servido MQTT
void reconect() {
  //Enquanto estiver desconectado
  while (!client.connected()) {
    Serial.println("Tentando conectar ao servidor MQTT");
 
    if(client.connect("arduinoClient")) {
      Serial.println("Conectado!");
      //subscreve no tópico
      client.subscribe("casa/lampada");
    } else {
      Serial.println("Falha durante a conexão.Code: ");
      Serial.println( String(client.state()).c_str());
      Serial.println("Tentando novamente em 5 s");
      //Aguarda 5 segundos 
      delay(5000);
    }
  }
}

void loop() {
  if (!client.connected()) {
    reconect();
  }
  
  //ler o valor do LDR
  ldrValor = analogRead(ldrPin); //O valor lido será entre 0 e 1023
  char msg[55];
  sprintf(msg, "%d", ldrValor);

  Serial.println("Publicar no topico casa/lampada/estado o estado da lampada");
  client.publish("casa/lampada/estado", msg); 
  
  //imprime o valor lido do LDR no monitor serial
  Serial.println(ldrValor);
  delay(2000);
 
  client.loop();
}
