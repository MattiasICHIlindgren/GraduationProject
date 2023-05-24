//Libraries and c header files for the project 
#pragma once

#include "Weather.h"    // Deriverd class header file containing the neccessary decleration of  functions that the cpp file needs in order to read
#include "Component.h" //The Baseclass header file 
#include <string>   //Access to string library 
#include <Arduino.h>  // Include the Arduino library to access setup and update as virtual functions
#include <SPI.h>  // "Helper" for the TFT library 
#include <TFT_eSPI.h>   // Hardware-specific library. TFT library enables call to tft functions and methods , to display them on the modules screen 
#include <ArduinoJson.h>          //https://github.com/bblanchon/ArduinoJson.git 
#include <NTPClient.h>           //https://github.com/taranais/NTPClient 

//Defining Colours 
#define TFT_GREY 0x5AEB
#define lightblue 0x01E9
#define darkred 0xA041
#define blue 0x5D9B

#include "Orbitron_Medium_20.h" // Custom Font
#include <WiFi.h> //Access to Wifi library and enables Wifi
#include <WiFiUdp.h> //Enables to keep the component updated trough wifi 
#include <HTTPClient.h> //TimeClient


// defining values  
const int pwmFreq = 5000;
const int pwmResolution = 8;
const int pwmLedChannelTFT = 0;

 
String town="Orebro";              
String Country="SE";   

//API             
const String endpoint = "http://api.openweathermap.org/data/2.5/weather?q="+town+","+Country+"&units=metric&APPID=";
const String key = "03583b3e02667d4637e85e17c27d8479";              

//Variabels for saving temp and humidity
String payload=""; //whole json 
 String tmp="" ; //temperatur
  String hum="" ; //humidity
  
//JsonDocument
StaticJsonDocument<1000> doc;

// Define NTP Client to get time
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP,"pool.ntp.org");

// Variables to save date and time
String formattedTime;
String dayStamp;
String timeStamp;

// setting value to adjust screen brightness
int backlight[5] = {10,30,60,120,220};
byte b=1;


WeatherComponent::WeatherComponent(TFT_eSPI*tft) //Contructor for Wheather Component
{
  
}


void WeatherComponent::setup(TFT_eSPI*tft) //Setup function for Weather with a TFT parameter to access the TFT library from Main
{
   //Defining only one internal button since one will be used to switch components
   pinMode(35,INPUT);

   //Setting up the screen with fonts
  tft->setRotation(0);
  tft->setTextColor(TFT_WHITE,TFT_BLACK);  tft->setTextSize(1);

  ledcSetup(pwmLedChannelTFT, pwmFreq, pwmResolution);
  ledcAttachPin(TFT_BL, pwmLedChannelTFT);
  ledcWrite(pwmLedChannelTFT, backlight[b]);
  

    tft->setTextColor(TFT_WHITE,TFT_BLACK);  tft->setTextSize(1);

   
      
          tft->setCursor(2, 232, 1);
          tft->println(WiFi.localIP());
           tft->setCursor(80, 204, 1);
           tft->println("BRIGHT:");

          tft->setCursor(80, 152, 2);
          tft->println("SEC:");
          tft->setTextColor(TFT_WHITE,lightblue);
           tft->setCursor(4, 152, 2);
          tft->println("TEMP:");

          tft->setCursor(4, 192, 2);
          tft->println("HUM: ");
          tft->setTextColor(TFT_WHITE,TFT_BLACK);

            tft->setFreeFont(&Orbitron_Medium_20);
            tft->setTextColor(TFT_ORANGE);
            tft->setCursor(30, 140);
           tft->println(town);

           tft->fillRect(68,152,1,74,TFT_GREY);

           for(int i=0;i<b+1;i++)
           tft->fillRect(78+(i*7),216,3,10,blue);

// Initialize a NTPClient to get time
timeClient.setUpdateInterval(1);
  timeClient.begin(); 
  // Set offset time in seconds to adjust for your timezone, for example:
  // GMT +1 = 3600
  // GMT +8 = 28800
  // GMT -1 = -3600
  // GMT 0 = 0
  timeClient.setTimeOffset(7200);                  
  getData(tft);
  delay(100);
}

// More variabels 
int i=0;
String tt1="";
int count=0;
bool inv=1;
int press1=0; 
int press2=0;////
long long int TimeBreak=0;
int frame=0;
String curSeconds="";
unsigned long timeBreak=0;


//function to get data
 void WeatherComponent::getData(TFT_eSPI*tft)
{
    tft->fillRect(1,170,64,20,TFT_BLACK);
    tft->fillRect(1,210,64,20,TFT_BLACK);
   if ((WiFi.status() == WL_CONNECTED)) { //Check the current connection status
 
    HTTPClient http;
 
    http.begin(endpoint + key); //Specify the URL
    int httpCode = http.GET();  //Make the request
 
    if (httpCode > 0) { //Check for the returning code
 
         payload = http.getString();
       // Serial.println(httpCode);
        Serial.println(payload);
        
      }
 
    else {
      Serial.println("Error on HTTP request");
    }
 
    http.end(); //Free the resources
  }
 char inp[1000];
 payload.toCharArray(inp,1000);
 deserializeJson(doc,inp);
  
  String tmp2 = doc["main"]["temp"];
  String hum2 = doc["main"]["humidity"];
  String town2 = doc["name"];
  tmp=tmp2;
  hum=hum2;
  
   Serial.println("Temperature"+String(tmp));
   Serial.println("Humidity"+hum);
   Serial.println(town);
   
 }

// Function for time called in void loop 
 void WeatherComponent::Time(TFT_eSPI*tft) 
 {
   // Extract time 
   formattedTime = timeClient.getFormattedTime();

// print time in the serial monitor for debugging but also on the modules display 
  Serial.println(formattedTime);

// Extract date
  int splitT = formattedTime.indexOf("T");
  dayStamp = formattedTime.substring(0, splitT);
  Serial.print("DATE: ");
  Serial.println(dayStamp);
  
  // Extract time
  timeStamp = formattedTime.substring(splitT+1, formattedTime.length()-1);
  Serial.print("HOUR: ");
  Serial.println(timeStamp);


         //tft colours and background
         
         tft->fillRect(78,170,48,28,darkred);
         tft->setFreeFont(&Orbitron_Light_24);
         tft->setCursor(81, 192); 
         tft->println(timeClient.getSeconds());
         
         tft->setFreeFont(&Orbitron_Light_32);
         String current=timeStamp.substring(0,5);
         if(current!=tt1)
         {
          tft->fillRect(3,8,130,30,TFT_BLACK);
          tft->setCursor(20, 34);
          tft->println(timeStamp.substring(0,5));
          tt1=timeStamp.substring(0,5);
         }
  }

   void WeatherComponent::update(TFT_eSPI*tft) //the loop function for Weather with a TFT parameter
  {

//Call on the time function and 250 ms delay
  unsigned long  now = millis();
  if (now >= timeBreak) {
     Time(tft); 
    timeBreak = now + 250;}

    
Serial.println(1); //used for debugging tool
timeClient.update(); //client for updating time 
   delay(16);

// If statement to increase the screen brightness
   if(digitalRead(35)==0){
   if(press2==0)
   {press2=1;
   tft->fillRect(78,216,44,12,TFT_BLACK);
 
   b++;
   if(b>=5)
   b=0;
Serial.println(3);
//Increase backlight
   for(int i=0;i<b+1;i++)
   tft->fillRect(78+(i*7),216,3,10,blue);
   ledcWrite(pwmLedChannelTFT, backlight[b]);}
   }else press2=0;
Serial.println(4);

   
   Serial.println(5);
   if(count==0)
   getData(tft);
   count++;
   Serial.println(6);
   if(count>2000)
   count=0;
   
    tft->setFreeFont(&Orbitron_Medium_20); //Font
    tft->setCursor(2, 187);
         tft->println(tmp.substring(0,5));

         tft->setCursor(2, 227);
         tft->println(hum+"%");

       
           tft->setTextColor(TFT_WHITE);


}
