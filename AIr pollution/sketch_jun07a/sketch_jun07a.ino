#define BLYNK_TEMPLATE_ID "TMPL3_3VYUesW"
#define BLYNK_TEMPLATE_NAME "Air Pollution Monitiring System"
#define BLYNK_AUTH_TOKEN "XIT8fEccbFRxxQP5EA9bqaWddOcoVcmm"
#define BLYNK_PRINT Serial
#include <WiFi.h> 
#include <BlynkSimpleEsp32.h>

#include "MQ135.h"

#include <Wire.h>

#include "SSD1306.h"

SSD1306 display(0x3c,21,22);
String myString;
String message;


#define SENSOR 32

char auth[] = BLYNK_AUTH_TOKEN;

char ssid[] = "Airtel";  // type your wifi name
char pass[] = "vidhi0707";  // type your wifi password

void setup()
{
  OLEDInit();
  Serial.begin(9600);
  delay(5000);
  Blynk.begin(auth, ssid, pass);
}


  void loop()
  {
    Blynk.run();
    MQ135 gasSensor = MQ135(SENSOR);
    float air_quality = gasSensor.getPPM();
    Serial.print("Air Quality: ");  
    Serial.print(air_quality);
    Serial.println("  PPM");   
    Serial.println();
    Serial.println("Waiting...");

    delay(2000);    
    OLEDUpdate();
}

void OLEDInit() {
  display.init();
}

void OLEDUpdate() {
  MQ135 gasSensor = MQ135(SENSOR);
  float air_quality = gasSensor.getPPM();
  Blynk.virtualWrite(V1,air_quality);
  display.clear();
  myString = "Hello";
  if(air_quality < 1000){
    message = "Fresh Air";
    myString = "Fresh Air";
    Serial.println(message);
    Blynk.logEvent("pollution_alert","Fresh Air");
    Blynk.virtualWrite(V0,message);
    Blynk.setProperty(V1, "color", "#23C48E");
    
  }else if(air_quality > 1000 && air_quality < 3000){
    message = "Polluted Air";
    myString = "Polluted Air";
    Serial.println(message);
    Blynk.logEvent("pollution_alert","Bad Air");
    Blynk.virtualWrite(V0,message);
    Blynk.setProperty(V1, "color", "#D3435C");
  }else if(air_quality > 3000){
    message = "Danger Zone !!";
    myString = "Danger Zone !!";
    Serial.println(message);
    Blynk.logEvent("pollution_alert","Danger Alert");
    Blynk.virtualWrite(V0,message);
    Blynk.setProperty(V1, "color", "#D3435C");
  }
  display.drawString(0,0,myString);
  display.display();
}
