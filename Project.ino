#define BLYNK_TEMPLATE_ID "TMPLzDumbQJO"
#define BLYNK_DEVICE_NAME "Project IoT Deteksi Longsor"
#define BLYNK_AUTH_TOKEN "WkXOvrvY3lpYKPAUBi3DzAD71wMwQC7Y"

#include "TRIGGER_WIFI.h"               
#include "TRIGGER_GOOGLESHEETS.h" 
#define BLYNK_PRINT Serial
#include <SPI.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
BlynkTimer timer;
WidgetLED led1(V1);

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "Davit";
char pass[] = "davitseptiawan";

char column_name_in_sheets[ ][20] = {"value1","value2"};
String Sheets_GAS_ID = "AKfycbwiuWE02hPoDqlFkqEBZzl-UUHt1f_V8wnJkBYmcZNzoSBvIOuTpUz2GSEkSlhtIuGo";
int No_of_Parameters = 2;

int sensorPin = A0;  
float sensorValue;
int pinHujan = 5;
float hujan;
int limit = 650; 
int bz = 2;
int red = 4;
int green = 0 ;

void setup() {
 Blynk.begin(auth, ssid, pass,"blynk.cloud",8080);
 Serial.begin(9600);
 pinMode(bz, OUTPUT);
 pinMode(red, OUTPUT);
 pinMode(green, OUTPUT);
 pinMode(pinHujan, INPUT);

 WIFI_Connect(ssid,pass);
 Google_Sheets_Init(column_name_in_sheets, Sheets_GAS_ID, No_of_Parameters );
}

void loop() {
  Blynk.run();
  timer.run();

 hujan = digitalRead(pinHujan);
 sensorValue = analogRead(sensorPin);

 Serial.print("Soil Moisture Value : ");
 Serial.println(sensorValue);
 Serial.print("Rain Value : ");
 Serial.println(hujan);
 Blynk.virtualWrite(V0, sensorValue);

 Data_to_Sheets(No_of_Parameters,  sensorValue,  hujan);
 
 if ( hujan == 1 && sensorValue<limit) {
 Serial.println("PERINGATAN LONGSOR !!!");
 digitalWrite(13, HIGH);
 digitalWrite(red, HIGH);
 digitalWrite(bz, HIGH);   
 digitalWrite(green, LOW);
 led1.on();
 Blynk.logEvent("PERINGATAN","WASPADA POTENSI LONGSOR");
 
 }
 else if (hujan == 0 && sensorValue<limit) {
 Serial.println("PERINGATAN DINI !");
 digitalWrite(red, HIGH);
 delay(400);
 digitalWrite(red, LOW);
 delay(100);  
 digitalWrite (green,LOW);
 digitalWrite(bz, HIGH);
 delay(200);
 digitalWrite(bz, LOW);
 delay(100);
 led1.off();
 Blynk.logEvent("PERINGATAN","PERINGATAN DINI POTENSI LONGSOR");
 
 }else if(hujan ==1 && sensorValue>=limit){
 Serial.println("HUJAN");
 digitalWrite(green, HIGH);
 delay(400) ;
 digitalWrite(green, LOW);
 delay(200) ;
  
 digitalWrite(red, HIGH);
 delay(400);
 digitalWrite(red, LOW);
 delay(200);  

 digitalWrite(bz, LOW);
 led1.on();
 }
 else {
 Serial.println("NORMAL");
 digitalWrite(green, HIGH);
 digitalWrite(bz, LOW);
 led1.off();   
 }
 

 delay(1000);
}
