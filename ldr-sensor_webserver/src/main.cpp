#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESPAsyncWebServer.h>
#include <ESPAsyncTCP.h>
#include <LittleFS.h>

//declare credential wifi
const char* ssid = "MasterAce";
const char* password = "arin26112001";

//open connection web server
AsyncWebServer server(80);

//declare pin ldr
#define ldrPin A0 

//declare variable data value
float ldrValue = 0;

// Checking connection to LittleFS
void initFS() {
  if(!LittleFS.begin()) {
    Serial.println("Error to connection LittleFS");
  }
  Serial.println("LittleFS mounted successfuly");
}

// Make Connection to WiFi
void initWiFi(){
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("Connecting to WiFi");
  while(WiFi.status() != WL_CONNECTED) {
    Serial.println(".");
    delay(1000);
  }
  Serial.println(WiFi.localIP());
}

// function return nilai sensor ldr
String getValue(){
  ldrValue = analogRead(ldrPin);
  return String(ldrValue);
}

// Server handlerequest for routing from client
void handleRequest(){
  //handle request web -> menampilkan file index html 
  server.on("/", HTTP_GET, [](AsyncWebServerRequest * request){
    request->send(LittleFS, "/index.html", "text/html");
  });

  //handle request nilai ldr
  server.on("/ldrValue", HTTP_GET, [](AsyncWebServerRequest * request){
    request->send_P(200, "text/plain", getValue().c_str());
  });

  server.serveStatic("/", LittleFS, "/");
  server.begin();
}

void setup() {
  Serial.begin(115200);
  initWiFi();
  initFS();
  handleRequest();
  
}

void loop() {

}