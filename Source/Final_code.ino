#include <ESP8266WiFi.h>
#include <String>
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>
#include <Ticker.h>
#include <DoubleResetDetect.h>
#include <FirebaseESP8266.h>
#include "DHT.h"

String user_ID ="6ZUQqbE5NFSwNKEFi18wAUooJXY2";

#define DHTPIN D1         // Digital pin connected to the DHT sensor
#define DHTTYPE DHT11     // type of DHT

#define Pump_speed2 D2      // Digital pin to controll the Pump speed
#define Chemical_Pump D7   // Digiatl pin connected to the Chemical pump
#define Water_Pump D4      // Digital pin connected to the Water pump
#define Pump_speed D5      // Digital pin to controll the Pump speed

#define Soil_Moisture A0    // Analog pin connected to the Soil moisture sensor 
float Soil_value = 0.0;
float RT_Soil_value = 0.0;
String Soil_path = "";

#define Soil_PH D8
float PH_value = 0.0;
float RT_PH_value = 0.0;
String PH_path = "";

#define Rain_Sencor D6      // Digital pin connceted to the Rain sensor


// #define FIREBASE_HOST "https://plantera-677c5-default-rtdb.firebaseio.com" 
#define FIREBASE_HOST "https://plant-329fc-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "dGglN1c3cUe80ELe6QHC9XNemIFpIREdsVeMlAds"

//Define Firebase Data object
FirebaseData fbdo;
String output = "output";

int i=20;
int plant_ID = 0;

String namee="";

unsigned long time1;
unsigned long time2;


Ticker ticker;    // obj
#define DRD_TIMEOUT 2.0 // time
#define DRD_ADRESS 0x00 // adress

DoubleResetDetect drd(DRD_TIMEOUT, DRD_ADRESS);
DHT dht(DHTPIN, DHTTYPE);

// Functions
void tick();
void Temperature_H();
void soil_moisture();
void soil_PH();

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  
  pinMode(Water_Pump, OUTPUT);
  pinMode(Chemical_Pump, OUTPUT);
  pinMode(Pump_speed, OUTPUT);
  pinMode(Pump_speed2, OUTPUT);
  pinMode(Rain_Sencor, INPUT);
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
  // delay(10000);
  if (Firebase.getInt(fbdo, "/users/" + user_ID + "/farm1/plant")) {
    if (fbdo.dataTypeEnum() == fb_esp_rtdb_data_type_integer) {
    plant_ID = fbdo.to<int>();
    Serial.print("Plant ID: ");
    Serial.println(fbdo.to<int>());
    }
  }else {
    Serial.println(fbdo.errorReason());
  }

  if(millis()-time2>=1000){
  soil_moisture();
  // soil_PH();
  
  time2=millis();
  }
  
  Temperature_H();
  if(!digitalRead(Rain_Sencor)){
    Serial.println("Rainy weather");
  }else{
    Serial.println("It is not raining"); 
  }
}

void tick(){
  // toggel state
  int state = digitalRead(BUILTIN_LED);       // get the current state of GPIO pin
  digitalWrite(BUILTIN_LED, !state);           // set pin to opposit state
}

void Temperature_H(){
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

  Firebase.setInt(fbdo,"/users/"+ user_ID + "/farm1/airhumidity_realtime/RT", h );
  Firebase.setInt(fbdo,"/users/"+ user_ID + "/farm1/temperature_realtime/RT", t );
}

void soil_moisture(){
  RT_Soil_value = analogRead(Soil_Moisture);
  Serial.print("Moisture Value: ");
  Serial.println(RT_Soil_value);
  RT_Soil_value = 100 - ((RT_Soil_value / 1024)*100.0);
  Firebase.setInt(fbdo,"/users/"+ user_ID + "/farm1/soilmoisture_realtime/RT", RT_Soil_value );

  if(plant_ID == 0){
    Soil_path = "";
    Soil_path = "/users/" + user_ID + "/farm1/soilc/value";     
  }else if(plant_ID == 1){
    Soil_path = "";
    Soil_path = "/users/" + user_ID + "/farm1/soilp/value";     
  }else if(plant_ID == 2){
    Soil_path = "";
    Soil_path = "/users/" + user_ID + "/farm1/soilt/value"; 
  }
 
  Serial.print("Soil path: ");
  Serial.println(Soil_path);
  if (Firebase.getFloat(fbdo, Soil_path)) {
    if (fbdo.dataTypeEnum() == fb_esp_rtdb_data_type_integer) {
    Soil_value = fbdo.to<int>();
    Serial.print("Soil humidity value: ");
    Serial.println(fbdo.to<int>());
    }
  }else {
    Serial.println(fbdo.errorReason());
  } 
    
  if(RT_Soil_value < Soil_value){
    Serial.println("Pump is work");
    analogWrite(Pump_speed, 255);
    digitalWrite(Water_Pump, 1);
  }else {
    digitalWrite(Water_Pump, 0);  
  }
}

void soil_PH(){
  RT_PH_value = analogRead(Soil_PH);
  Serial.print("PH Value: ");
  Serial.println(RT_PH_value); 
  Firebase.setInt(fbdo,"/users/"+ user_ID + "/farm1/ph_realtime/RT", RT_PH_value );

  if(plant_ID == 0){
    Soil_path = "";
    Soil_path = "/users/" + user_ID + "/farm1/phc/value";     
  }else if(plant_ID == 1){
    Soil_path = "";
    Soil_path = "/users/" + user_ID + "/farm1/php/value";     
  }else if(plant_ID == 2){
    Soil_path = "";
    Soil_path = "/users/" + user_ID + "/farm1/pht/value"; 
  }

  if (Firebase.getFloat(fbdo, PH_path)) {
    if (fbdo.dataTypeEnum() == fb_esp_rtdb_data_type_integer) {
    PH_value = fbdo.to<int>();
    Serial.print("Soil PH value: ");
    Serial.println(fbdo.to<int>());
    }
  }else {
    Serial.println(fbdo.errorReason());
  } 

  if(RT_PH_value < PH_value){
    analogWrite(Pump_speed2, 255);
    digitalWrite(Chemical_Pump, 1);
  }else {
    digitalWrite(Chemical_Pump, 0);  
  }
}
