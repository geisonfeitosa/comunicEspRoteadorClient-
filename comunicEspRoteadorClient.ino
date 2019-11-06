#include <WiFi.h>

#define PINBUT 4 //Botão
#define PINLEDL 2 //Led embutido

const char* ssid      = "LIVE TIM_41F9_2G";
const char* password  = "2pxtrvv3hd";
const String clientID = "Cliente 01"; //Id do Client

IPAddress server(192,168,25,240);
const int porta = 80;

WiFiClient client;

void setup() {
  Serial.begin(115200);
  
  pinMode(PINBUT, INPUT);
  pinMode(PINLEDL, OUTPUT);

  WiFi.begin(ssid, password);
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  EspRequest();
}

void loop() {
  ReadButton();
}

void ReadButton() {
  int reading = digitalRead(PINBUT);
  if(reading == HIGH) {
    int ledState = !digitalRead(PINLEDL);
    digitalWrite(PINLEDL, ledState);
    Serial.println("<" + clientID + "-" + ledState + ">");
    client.println("<" + clientID + "-" + ledState + ">");
    client.flush();
  }
  delay(1000);
}

void EspRequest() {
  client.stop();
  if(client.connect(server, porta)) {
    Serial.println("<" + clientID + "- Connected>");
    client.println("<" + clientID + "- Connected>");
    client.flush();
  }
}
