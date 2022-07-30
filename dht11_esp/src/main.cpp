#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESPAsyncWebServer.h>
#include <ESPAsyncTCP.h>
#include <LittleFS.h>
#include <Adafruit_Sensor.h>
#include "DHT.h"

#define DHTPIN 2     // Digital pin connected to the DHT sensor
#define DHTTYPE DHT11   // DHT 11

//declare credential wifi
const char* ssid = "MasterAce";
const char* password = "arin26112001";

//open connection web server
AsyncWebServer server(80);

DHT dht(DHTPIN, DHTTYPE);

// current temperature & humidity, updated in loop()
float t = 0.0;
float h = 0.0;

//declare led
#define led1 16 //D0
#define led2 5 //D1


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

String getHumidity() {
  return String(h);
}

String getTemp() {
  return String(t);
}

String statusH(){
  String value;
  if (h > 45 && h < 65){
    return "Kelembapan Ideal (45-65)";
  } else if (h < 45) {
    return "Kelembapan Kering (<45)";
  } else if (h > 65) {
    return "Kelembapan terlalu tinggi (>65)";
  } else {
    return "kelembapan tidak diketahui";
  }
  
}

// Server handlerequest for routing from client
void handleRequest(){
  //handle request web -> menampilkan file index html 
  server.on("/", HTTP_GET, [](AsyncWebServerRequest * request){
    request->send(LittleFS, "/index.html", "text/html");
  });

  //handle request nilai humidity
  server.on("/humidity", HTTP_GET, [](AsyncWebServerRequest * request){
    request->send_P(200, "text/plain", getHumidity().c_str());
  });

  server.on("/temperature", HTTP_GET, [](AsyncWebServerRequest * request){
    request->send_P(200, "text/plain", getTemp().c_str());
  });

  server.on("/hstatus", HTTP_GET, [](AsyncWebServerRequest * request){
    request->send_P(200, "text/plain", statusH().c_str());
  });

  server.serveStatic("/", LittleFS, "/");
  server.begin();
}

void newLed() {
  if (t > 24 && t < 29 ){
    digitalWrite(led1, HIGH);
    digitalWrite(led2, HIGH);
  }
  else if (t > 28) {
    digitalWrite(led1, HIGH);
    digitalWrite(led2, LOW);
    delay(100);
    digitalWrite(led1, LOW);
    digitalWrite(led2, HIGH);
    delay(100);
  } else {
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
  }

}



void setup() {
  Serial.begin(115200);
  initWiFi();
  initFS();
  handleRequest();
  Serial.println(F("DHTxx test!"));

  dht.begin();

  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);

}

void loop() {

  delay(2000);

  float newT = dht.readTemperature();
  if (isnan(newT)) {
    Serial.println("Failed to read from DHT sensor!");
  }
  t = newT;

  h = dht.readHumidity();
  if (isnan(h)) {
    Serial.println("Failed to read from DHT sensor!");
  }
  
  newLed();
  
}

