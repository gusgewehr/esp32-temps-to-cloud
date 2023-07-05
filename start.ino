// this example is public domain. enjoy! https://learn.adafruit.com/thermocouple/

#include "max6675.h"
#include  <WiFi.h>

//192.168.0.100

const char* ssid = "labredes";

int thermoDO = 19;
int thermoCS = 23;
int thermoCLK = 5;

MAX6675 thermocouple(thermoCLK, thermoCS, thermoDO);
WiFiServer server(80);

void setup() {
  Serial.begin(115200);


  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid);

  while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
  server.on("/temperatura", temperatura);


  Serial.println(WiFi.localIP());


  
  // wait for MAX chip to stabilize
  delay(500);
}

void loop() {
  // basic readout test, just print the current temp
  
  server.handleClient();
  
}

void temperatura(){
  //Serial.print("C = "); 
  //Serial.println(thermocouple.readCelsius());
  float t = thermocouple.readCelsius(); /* leitura de Temperatura */
  String message = "";
  message = "Temperatura = ";      /* Escreve Temperatura */
  message += t;          

  server.send(200, "text/plain", message);
}
