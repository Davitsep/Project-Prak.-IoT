#define BLYNK_TEMPLATE_ID "TMPLzDumbQJO"
#define BLYNK_DEVICE_NAME "Project IoT Deteksi Longsor"
#define BLYNK_AUTH_TOKEN "WkXOvrvY3lpYKPAUBi3DzAD71wMwQC7Y"

#define BLYNK_PRINT Serial
#include <SPI.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <BlynkSimpleEsp8266.h>
BlynkTimer timer;
WidgetLED led1(V1);

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "Davit";
char pass[] = "davitseptiawan";
const char *host = "192.168.104.94";

int sensorPin = A0;  
int sensorValue;
int pinHujan = 5;
int hujan;
String kondisi;
int limit = 650; 
int bz = 2;
int red = 4;
int green = 0 ;
String keterangan;
String sendval,sendval2,sendval3;

void setup() {
 Blynk.begin(auth, ssid, pass,"blynk.cloud",8080);
 Serial.begin(9600);
 pinMode(bz, OUTPUT);
 pinMode(red, OUTPUT);
 pinMode(green, OUTPUT);
 pinMode(pinHujan, INPUT);

 WiFi.mode(WIFI_STA);           
 WiFi.begin(ssid, pass);
 Serial.print("Connecting to ");
 Serial.print(ssid);
 while (WiFi.status() != WL_CONNECTED) 
  { Serial.print(".");
    delay(500); }

Serial.println("");
Serial.print("Connected to ");
Serial.println(ssid);
Serial.print("IP Address : ");
Serial.println(WiFi.localIP());    //print local IP address
}

void loop() {
  Blynk.run();
  timer.run();

 hujan = digitalRead(pinHujan);
 sensorValue = analogRead(sensorPin);

 if (hujan == 1) {
  kondisi = "1";
 } else {
  kondisi = "2";
 }
 
 Serial.print("Soil Moisture Value : ");
 Serial.println(sensorValue);
 Serial.print("Rain Value : ");
 Serial.println(hujan);
 Blynk.virtualWrite(V0, sensorValue);
 
 if ( hujan == 1 && sensorValue<limit) {
 keterangan = "1";
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
 keterangan = "2";
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
 keterangan = "3";
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
 keterangan = "4";
 digitalWrite(green, HIGH);
 digitalWrite(bz, LOW);
 led1.off();   
 }
 WiFiClient client;
 const int httpPort = 80;
 if(!client.connect(host,httpPort)){
  Serial.println("Connection Failed");
  return;
 }

 String url = "/data_longsor/writedata.php?";
 url += "&sendval="+String(sensorValue);
 url += "&sendval2="+String(kondisi);
 url += "&sendval3="+String(keterangan);

 Serial.print("Requesting URL: ");
 Serial.println(url);

 client.print(String("GET ") + url + " HTTP/1.1\r\n" + 
 "Host: " + host + "\r\n" +
 "Connection: close\r\n\r\n");
 
 unsigned long timeout = millis();
 while (client.available() == 0) {
  if (millis() - timeout > 2000) {
    Serial.println(">>>Client Timeout !");
    client.stop();
    return;
  }
 }

 while (client.available()) {
  String line = client.readStringUntil('\r');
  Serial.print(line);
 }
 Serial.println();
 Serial.println("closing connection");
}
