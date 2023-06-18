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
#include <JsonListener.h>
#include <time.h>
#include "OpenWeatherMapForecast.h"

// initiate the client
OpenWeatherMapForecast client;

// See https://docs.thingpulse.com/how-tos/openweathermap-key/
String OPEN_WEATHER_MAP_APP_ID = "baa51dba99e56c51316821fcc4a50f27";
/*
Go to https://openweathermap.org/find?q= and search for a location. Go through the
result set and select the entry closest to the actual location you want to display 
data for. It'll be a URL like https://openweathermap.org/city/2657896. The number
at the end is what you assign to the constant below.
 */
// cairo = 360630
// Afgooye = 65785
String OPEN_WEATHER_MAP_LOCATION_ID = "360630";
String OPEN_WEATHER_MAP_LANGUAGE = "en";
boolean IS_METRIC = false;
uint8_t MAX_FORECASTS = 4;
int delay_weather = 0;
int delay_hour = 10800000;
int delay_second = 1000;
// uint8_t foundForecasts;

String user_ID ="6ZUQqbE5NFSwNKEFi18wAUooJXY2/farm2";

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

unsigned long time_soil_moisture;
unsigned long time1;
unsigned long time_weather_station;


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
  time_soil_moisture=millis();
  time_weather_station=millis();
 ////////////////////

 ////////////////////
  if (Firebase.getFloat(fbdo, "/users/" + user_ID + "/location/ID")) {
    if (fbdo.dataTypeEnum() == fb_esp_rtdb_data_type_integer) {
      OPEN_WEATHER_MAP_LOCATION_ID = fbdo.to<String>();
    }
  }else {
    Serial.println(fbdo.errorReason());
  }
  Serial.println(OPEN_WEATHER_MAP_LOCATION_ID);
  ///////////////////
}

void loop() {
  // Read plant ID from firebase   
  if (Firebase.getInt(fbdo, "/users/" + user_ID + "/plant")) {
    if (fbdo.dataTypeEnum() == fb_esp_rtdb_data_type_integer) {
    plant_ID = fbdo.to<int>();
    // Serial.print("Plant ID: ");
    // Serial.println(fbdo.to<int>());
    }
  }else {
    Serial.println(fbdo.errorReason());
  }
  
  // Wait a few seconds between measurements.
  if(millis()-time_soil_moisture >= delay_weather){
    
    soil_moisture();
    soil_PH();
    time_soil_moisture=millis();
  }

  if(millis()-time1>=1000){

    Battery_level_charging();
    Temperature_H();    
    
    if(!digitalRead(Rain_Sencor)){
      Serial.println("Rainy weather");
      Firebase.setInt(fbdo,"/users/"+ user_ID + "/weather/rainy", 1);
    }else{
      Serial.println("It's not raining"); 
      Firebase.setInt(fbdo,"/users/"+ user_ID + "/weather/rainy", 0);
    }
      time1=millis();
  }  
    
  if(millis()-time_weather_station >= 10000){
    
    OpenWeatherMapForecastData data[MAX_FORECASTS];
    client.setMetric(IS_METRIC);
    client.setLanguage(OPEN_WEATHER_MAP_LANGUAGE);
    uint8_t allowedHours[] = {0,6,12,18};
    client.setAllowedHours(allowedHours, 4);
    uint8_t foundForecasts = client.updateForecastsById(data, OPEN_WEATHER_MAP_APP_ID, OPEN_WEATHER_MAP_LOCATION_ID, MAX_FORECASTS);
    // Serial.printf("Found %d forecasts in this call\n", foundForecasts);
    // Serial.println("------------------------------------");
    time_t time;  
    for (uint8_t i = 0; i < foundForecasts; i++) {
      Serial.printf("#################\n\nForecast number: %d\n", i);
      // {"dt":1527066000, uint32_t observationTime;
      time = data[i].observationTime;
      Serial.printf("observationTime: %d, full date: %s", data[i].observationTime, ctime(&time));
      // "main":{
      // },"weather":[{"id":802, uint16_t weatherId;
      Serial.printf("weatherId: %d\n", data[i].weatherId);
      //   "main":"Clouds", String main;
      Serial.printf("main: %s\n", data[i].main.c_str());
      //   "description":"scattered clouds", String description;
      Serial.printf("description: %s\n", data[i].description.c_str());
      // rain: {3h: 0.055}, float rain;
      Serial.printf("rain: %f\n", data[i].rain);
      // },"sys":{"pod":"d"}
      // dt_txt: "2018-05-23 09:00:00"   String observationTimeText;
      Serial.printf("observationTimeText: %s\n", data[i].observationTimeText.c_str());
    }
    
    if(data[0].rain >= 0.055){
      delay_weather = delay_hour;
    }
    else{
      delay_weather = delay_second;
    }
    Serial.println(delay_weather);
    time_weather_station=millis();
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
 
  Serial.printf("Humidity: %f\n", h);
  Serial.printf("%  Temperature: %f\n", t);

  Firebase.setInt(fbdo,"/users/"+ user_ID + "/airhumidity_realtime/RT", h );
  Firebase.setInt(fbdo,"/users/"+ user_ID + "/temperature_realtime/RT", t );
}

void soil_moisture(){
  RT_Soil_value = ads.readADC_SingleEnded(0);
  Serial.printf("Moisture Value: %f\n", RT_Soil_value);
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
 
  if (Firebase.getFloat(fbdo, Soil_path)) {
    if (fbdo.dataTypeEnum() == fb_esp_rtdb_data_type_integer) {
    Soil_value = fbdo.to<int>();
    }
  }else {
    Serial.println(fbdo.errorReason());
  } 
  
  digitalWrite(zero_pin, 0);
  if((RT_Soil_value < Soil_value) && digitalRead(Rain_Sencor)){
    Serial.println("Pump is work");
    digitalWrite(Water_Pump, 1);
  }else {
    digitalWrite(Water_Pump, 0);  
  }
}

void soil_PH(){
  // RT_PH_value = ads.readADC_SingleEnded(1);
  Serial.printf("PH Value: %f\n", RT_PH_value);
  // Firebase.setInt(fbdo,"/users/"+ user_ID + "/ph_realtime/RT", RT_PH_value );

  // if(plant_ID == 0){
  //   Soil_path = "";
  //   Soil_path = "/users/" + user_ID + "/phc/value";     
  // }else if(plant_ID == 1){
  //   Soil_path = "";
  //   Soil_path = "/users/" + user_ID + "/php/value";     
  // }else if(plant_ID == 2){
  //   Soil_path = "";
  //   Soil_path = "/users/" + user_ID + "/pht/value"; 
  // }

  if (Firebase.getFloat(fbdo, "/users/" + user_ID + "/ph_realtime/RT")) {
    if (fbdo.dataTypeEnum() == fb_esp_rtdb_data_type_integer) {
    RT_PH_value = fbdo.to<int>();
    Serial.print("Soil PH value: ");
    Serial.println(fbdo.to<int>());
    }
  }else {
    Serial.println(fbdo.errorReason());
  } 

  digitalWrite(zero_pin, 0);
  if(RT_PH_value == 1){
    digitalWrite(Chemical_Pump, 1);
  }else if(RT_PH_value == 0){
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
  Serial.printf("Battery level: %f\n", in_voltage);
  Firebase.setInt(fbdo,"/users/"+ user_ID + "/battery/value", Battery_level );
}