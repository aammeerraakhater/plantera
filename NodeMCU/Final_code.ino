#include <ESP8266WiFi.h>
#include <String>
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>
#include <Ticker.h>
#include <DoubleResetDetect.h>
#include <FirebaseESP8266.h>
#include <Adafruit_ADS1X15.h>
#include "DHT.h"

String user_ID ="6ZUQqbE5NFSwNKEFi18wAUooJXY2/farm1";

#define DHTPIN D4         // Digital pin connected to the DHT sensor
#define DHTTYPE DHT11     // type of DHT

#define Chemical_Pump D5     // Digiatl pin connected to the Chemical pump
#define Water_Pump D6        // Digital pin connected to the Water pump
#define zero_pin D7          

#define Rain_Sencor D3        // Digital pin connceted to the Rain sensor
#define PV_charger D8         // Digital pin connected to relay to charge Battery 
float Soil_value = 0.0;
float RT_Soil_value = 0.0;
String Soil_path = "";

float PH_value = 0.0;
float RT_PH_value = 0.0;
String PH_path = "";

#define Battery A0
// Floats for ADC voltage & Input voltage
float adc_voltage = 0.0;
float in_voltage = 0.0;
float R1 = 28400.0;
float R2 = 7500.0;
int flag = 100;
float ref_voltage = 3.3;      // Float for Reference Voltage
int adc_value = 0;            // Integer for ADC value
int Battery_level = 0;


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

// ADS 1115 pins
int adc0, adc1, adc2, adc3;

Ticker ticker;    // obj
#define DRD_TIMEOUT 2.0 // time
#define DRD_ADRESS 0x00 // adress

DoubleResetDetect drd(DRD_TIMEOUT, DRD_ADRESS);
DHT dht(DHTPIN, DHTTYPE);

Adafruit_ADS1115 ads;

// Functions
void tick();
void Temperature_H();
void soil_moisture();
void soil_PH();
void Battery_level_charging();

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  
  pinMode(Water_Pump, OUTPUT);
  pinMode(Chemical_Pump, OUTPUT);
  pinMode(zero_pin, OUTPUT);
  pinMode(Rain_Sencor, INPUT);
  pinMode(PV_charger, OUTPUT);
  pinMode(Battery, INPUT);
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

  if (!ads.begin()) {
    Serial.println("Failed to initialize ADS.");
    while (1);
  }

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
  if (Firebase.getInt(fbdo, "/users/" + user_ID + "/plant")) {
    if (fbdo.dataTypeEnum() == fb_esp_rtdb_data_type_integer) {
    plant_ID = fbdo.to<int>();
    // Serial.print("Plant ID: ");
    // Serial.println(fbdo.to<int>());
    }
  }else {
    Serial.println(fbdo.errorReason());
  }

  if(millis()-time2>=3000){
  soil_moisture();
  // soil_PH();
  Battery_level_charging();
  Temperature_H();
  if(!digitalRead(Rain_Sencor)){
  Serial.println("Rainy weather");
  Firebase.setInt(fbdo,"/users/"+ user_ID + "/weather/rainy", 1);
  }else{
    Serial.println("It is not raining"); 
    Firebase.setInt(fbdo,"/users/"+ user_ID + "/weather/rainy", 0);

  }
  time2=millis();
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

  Firebase.setInt(fbdo,"/users/"+ user_ID + "/airhumidity_realtime/RT", h );
  Firebase.setInt(fbdo,"/users/"+ user_ID + "/temperature_realtime/RT", t );
}

void soil_moisture(){
  RT_Soil_value = ads.readADC_SingleEnded(0);
  Serial.print("Moisture Value: ");
  Serial.println(RT_Soil_value);
  RT_Soil_value = 100 - ((RT_Soil_value / 20000)*100.0);
  Firebase.setInt(fbdo,"/users/"+ user_ID + "/soilmoisture_realtime/RT", RT_Soil_value );

  if(plant_ID == 0){
    Soil_path = "";
    Soil_path = "/users/" + user_ID + "/soilc/value";     
  }else if(plant_ID == 1){
    Soil_path = "";
    Soil_path = "/users/" + user_ID + "/soilp/value";     
  }else if(plant_ID == 2){
    Soil_path = "";
    Soil_path = "/users/" + user_ID + "/soilt/value"; 
  }
 
  // Serial.print("Soil path: ");
  // Serial.println(Soil_path);
  if (Firebase.getFloat(fbdo, Soil_path)) {
    if (fbdo.dataTypeEnum() == fb_esp_rtdb_data_type_integer) {
    Soil_value = fbdo.to<int>();
    // Serial.print("Soil humidity value: ");
    // Serial.println(fbdo.to<int>());
    }
  }else {
    Serial.println(fbdo.errorReason());
  } 
  
  digitalWrite(zero_pin, 0);
  if(RT_Soil_value < Soil_value){
    Serial.println("Pump is work");
    digitalWrite(Water_Pump, 1);
  }else {
    digitalWrite(Water_Pump, 0);  
  }
}

void soil_PH(){
  RT_PH_value = ads.readADC_SingleEnded(1);
  Serial.print("PH Value: ");
  Serial.println(RT_PH_value); 
  Firebase.setInt(fbdo,"/users/"+ user_ID + "/ph_realtime/RT", RT_PH_value );

  if(plant_ID == 0){
    Soil_path = "";
    Soil_path = "/users/" + user_ID + "/phc/value";     
  }else if(plant_ID == 1){
    Soil_path = "";
    Soil_path = "/users/" + user_ID + "/php/value";     
  }else if(plant_ID == 2){
    Soil_path = "";
    Soil_path = "/users/" + user_ID + "/pht/value"; 
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

  digitalWrite(zero_pin, 0);
  if(RT_PH_value < PH_value){
    digitalWrite(Chemical_Pump, 1);
  }else {
    digitalWrite(Chemical_Pump, 0);  
  }
}

void Battery_level_charging(){
  
  adc_value = analogRead(Battery);                 // Read the Analog Input
  adc_voltage  = (adc_value * ref_voltage) / 1024.0;  // Determine voltage at ADC input
  in_voltage = adc_voltage / (R2 / (R1 + R2));        // Calculate voltage at divider input

  if(in_voltage >= 12.6){
     Battery_level = 100;
  }else if((in_voltage >= 12.5) && (in_voltage < 12.6)){
     Battery_level = 90;    
  }else if((in_voltage >= 12.4) && (in_voltage < 12.5)){
     Battery_level = 80;    
  }else if((in_voltage >= 12.3) && (in_voltage < 12.4)){
     Battery_level = 70;    
  }else if((in_voltage >= 12.2) && (in_voltage < 12.3)){
     Battery_level = 60;    
  }else if((in_voltage >= 12.1) && in_voltage < 12.2){
     Battery_level = 50;    
  }else if((in_voltage >= 11.9) && in_voltage < 12.1){
     Battery_level = 40;    
  }else if((in_voltage >= 11.8) && in_voltage < 11.9){
     Battery_level = 30;    
  }else if((in_voltage >= 11.6) && (in_voltage < 11.8)){
     Battery_level = 20;    
  }else if((in_voltage >= 11.3) && (in_voltage < 11.6)){
     Battery_level = 10;    
  }else if((in_voltage >= 10.5) && (in_voltage < 11.3)){
     Battery_level = 0;    
  }

  if(Battery_level <= 50){
    digitalWrite(PV_charger, 1);
  }else if(Battery_level > 50){
    digitalWrite(PV_charger, 0);
  }
  Serial.print("Battery level: ");
  Serial.println(in_voltage);  
  Firebase.setInt(fbdo,"/users/"+ user_ID + "/battery/value", Battery_level );
}