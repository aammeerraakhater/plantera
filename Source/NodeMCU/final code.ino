#include <ESP8266WiFi.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>
#include <Ticker.h>
#include <DoubleResetDetect.h>
#include<FirebaseESP8266.h>
#include "DHT.h"

#define DHTPIN D1     // Digital pin connected to the DHT sensor
#define DHTTYPE DHT11
 
#define FIREBASE_HOST "https://plantera-677c5-default-rtdb.firebaseio.com" 
#define FIREBASE_AUTH "ex7HebcoI75A4aexJz8JEUU4R5GlCt5lmVDJHRL7"

//Define Firebase Data object
FirebaseData fbdo;
String output = "output";

int i=20;

String namee="";

unsigned long time1;
unsigned long time2;


Ticker ticker;    // obj
#define DRD_TIMEOUT 2.0 // time
#define DRD_ADRESS 0x00 // adress

DoubleResetDetect drd(DRD_TIMEOUT, DRD_ADRESS);
DHT dht(DHTPIN, DHTTYPE);
void tick(){
  // toggel state
  int state = digitalRead(BUILTIN_LED);       // get the current state of GPIO pin
  digitalWrite(BUILTIN_LED, !state);           // set pin to opposit state
}
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  WiFiManager wifiM;

  pinMode(BUILTIN_LED, OUTPUT);
  ticker.attach(0.5, tick);
  
  if (drd.detect()){
    Serial.println("** Double reset boot **");
    wifiM.resetSettings();
  }      
  Serial.println("** Noraml boot **"); 
  wifiM.setTimeout(60);
  if(!wifiM.autoConnect("Plantera")){
    Serial.println("Failed to connect and hit timeout");
    delay(3000);
    // reset and try again, or maybe put it to deep sleep
    ESP.reset();
    delay(5000);
  }  

  Serial.println("Connected");  
  ticker.detach();
  digitalWrite(BUILTIN_LED, 1); 
  dht.begin();

  ////////////////////
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);
  time1=millis();
  time2=millis();
  ////////////////////
}

void loop() {
  // Wait a few seconds between measurements.
  delay(1000);
  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) ) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.print(F("%  Temperature: "));
  Serial.println(t);

  if(millis()-time2>=3000){
  Firebase.setInt(fbdo,"/ESP/Temperature", t );
  Firebase.setInt(fbdo,"/ESP/Humidity", h );
  time2=millis();
  }
}
