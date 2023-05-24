
#pragma once
#include "Component.h" //The Baseclass header file 
#include <string>  //Access to string library 
#include <WiFi.h> //Access to Wifi library and enables Wifi
#include "time.h"  //Enables time function and methods
#include "EulaBG.h" //Custom backgrounds 
#include "Orbitron_Medium_20.h" //Custom Font
#include <SPI.h> // "Helper" for the TFT library 
#include <TFT_eSPI.h> //TFT library enables call to tft functions and methods , to display them on the modules screen 
#include "MainClock.h" // Deriverd class header file containing the neccessary decleration of  functions that the cpp file needs in order to read 

//Colour definition
#define TFT_BLACK 0x0000 // black
#define darkred 0xA041


const char* ntpServer = "pool.ntp.org"; //Server to get time
const long  gmtOffset_sec = 3600; //Timezone 
const int   daylightOffset_sec = 3600; //DaylightOffset time

 
 MainClock::MainClock(TFT_eSPI*tft) //Contructor for MainClock
 {
  
 }
 
  void MainClock::setup(TFT_eSPI*tft) //Setup function for MainClock with a TFT parameter to access the TFT library from Main
 {  
     //Setting the background
     tft->fillScreen(TFT_WHITE);
    tft->setSwapBytes(true);
    tft->pushImage(0,0,135,240,EulaBG);
    tft->setSwapBytes(true); 

    //init and get the time 
    //call to the server with declared timezone and daylightOffset/summertime.
    configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
     //Setting the background
     tft->fillScreen(TFT_WHITE);
    tft->setSwapBytes(true);
    tft->pushImage(0,0,135,240,EulaBG);
    tft->setSwapBytes(true); 
}
 
  void MainClock::printLocalTime(TFT_eSPI*tft)  //Function to print time with a TFT parameter
{ 
  //If the module isn't connecting to the network, it can't get the time.
  struct tm timeinfo;
  if(!getLocalTime(&timeinfo)){
    Serial.println("Failed to obtain time");
    return;
  }
  
    //Printing day of the week
  Serial.println(5);
  tft->setCursor(15, 195, 0);
  tft->setTextColor(TFT_WHITE);  
  tft->println(&timeinfo, "%A");

  //Printing Month and date
  tft->setCursor(20, 175, 0);
  tft->setTextColor(TFT_WHITE);    
  tft->println(&timeinfo, "%B %d");

  //Printing time with a custom font
  tft->setCursor(17, 220, 2);
  tft->fillRect(10,200,115,28,darkred);
  tft->setFreeFont(&Orbitron_Medium_20);
  tft->setTextColor(TFT_WHITE,TFT_BLACK);  
  tft->setTextSize(1);
  tft->println(&timeinfo,"%H:%M:%S");
  Serial.println(6);
    
}
    
   void MainClock::update(TFT_eSPI*tft) //the loop function for MainClock with a TFT parameter
  {  
     
     //Calling the function with a TFT parameter to print the time in a loop ,
     printLocalTime(tft);
    
  }
  
 
