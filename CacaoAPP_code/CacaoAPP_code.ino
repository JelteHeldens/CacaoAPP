#include <Arduino.h>
#include <stdint.h>
//WiFi Includes
#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <ESPmDNS.h>
//Temp&Hum Sensor
#include <DHT.h>

#include "arduino_secrets.h"

//WiFi Init
char ssid[] = SECRET_SSID;
char pass[] = SECRET_PASS;

WebServer server(80);

void handleRoot() {
  char msg[3000];

  snprintf(msg, 3000,
           "<html>\
	<head>\
		<meta http-equiv='refresh' content='30'/>\
		<meta name='viewport' content='width=device-width, initial-scale=1'>\
		<title>Cacao Checker</title>\
		<link rel='preconnect' href='https://fonts.googleapis.com'>\
		<link rel='preconnect' href='https://fonts.gstatic.com' crossorigin>\
		<link href='https://fonts.googleapis.com/css2?family=Darumadrop+One&family=Monomaniac+One&display=swap' rel='stylesheet'>\
		<link rel='stylesheet' href='https://fonts.googleapis.com/css2?family=Material+Symbols+Outlined:opsz,wght,FILL,GRAD@24,400,0,0&icon_names=device_thermostat,humidity_indoor' />\
		<style>\
			body { margin: 0; background-color: #49291c; color: white;}\
			.darumadrop-one-regular {font-family: 'Darumadrop One', serif; font-weight: 400; font-style: normal;}\
			.monomaniac-one-regular {font-family: 'Monomaniac One', serif; font-weight: 400; font-style: normal;}\
			h1 {font-family:'Darumadrop One'; text-align: center; font-size: 4em; font-weight: normal;}\
			a {font-family: 'Monomaniac One'; margin-left: 5%; font-size: 2.5em;}\
			.container{margin: auto; text-align: center;}\
			.material-symbols-outlined{font-size: 2.5em;}\
		</style>\
	</head>\
	<body><br><br>\
		<h1>Cacao Checker</h1>\
		<div class='container'><br><br>\
			<span class='material-symbols-outlined'>device_thermostat</span>\
			<a>%.1f&deg;C</a><br>\
			<span class='material-symbols-outlined'>humidity_indoor</span>\
			<a>%.1f&#37</a><br><br>\
		</div>\
	</body>\
</html>",
  readTemperature(), readHumidity());

  server.send(200, "text/html", msg);
}

//Temp&Hum Init
DHT dht(26, DHT22);

int debug = 1;                      //0 = Debug OFF 
                                    //1 = Debug ON
void setup(){
  Serial.begin(115200);             // Debug Port
  //Serial1.begin(115200,SERIAL_8N1,16,17);

  //MQTT Setup
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  //Debug | SCAN NETWORKS
  if (debug){
    Serial.println("\n--- OPSTARTEN IN DEBUG MODE ---\n");
    Serial.println("Zoeken naar netwerken...");
    int n = WiFi.scanNetworks();
    Serial.println("Scan klaar");
    if (n == 0) {
        Serial.println("Geen netwerken gevonden");
    } else {
      Serial.print(n);
      Serial.println(" netwerken gevonden");
      for (int i = 0; i < n; ++i) {
        //Print SSID en RSSI van elk netwerk
        Serial.print("-> ");
        Serial.print(i + 1);
        Serial.print(": ");
        Serial.println(WiFi.SSID(i));
      }
    }
  }  
  Serial.print("\nProbeer te verbinden met netwerk: ");
  Serial.println(ssid);
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(1000);
  }
  if(WiFi.status() == WL_CONNECTED){
    Serial.println("\nU bent verbonden!");
    Serial.print("-> IP:   ");
    Serial.println(WiFi.localIP());
    Serial.print("-> RSSI: ");
    Serial.println(WiFi.RSSI());
  }
  else{
    Serial.println("\nKan niet verbinden met het netwerk");
  }

  //Webserver
  if (MDNS.begin("cacao")) {
    Serial.println("MDNS responder started");
  }
  server.on("/", handleRoot);

  server.begin();
  Serial.println("HTTP server started");

  //Temp&Hum Sensor
  dht.begin();
}

void loop(){
  server.handleClient();
  delay(2);
}

float readTemperature(){
  float t = dht.readTemperature();
  if (isnan(t)) {return -404;}
  else{ return t;}
}

float readHumidity(){
  float h = dht.readHumidity();
  if (isnan(h)) {return -404;}
  else{ return h;}
}