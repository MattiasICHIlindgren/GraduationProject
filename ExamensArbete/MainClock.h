//Iclude guards so the header file won't be dublicated
#ifndef MAINCLOCK_H
#define MAINCLOCK_H

//The Baseclass header file 
#include "Component.h" 
#include <string>  //Access to string library 
#include <Arduino.h> // Include the Arduino library to access setup and update as virtual functions
#include <TFT_eSPI.h> //TFT library enables call to tft functions and methods , to display them on the modules screen 

//Derivered class 
class MainClock : public Component
{
  public: 
   //functions for the MainClock CPP file.
   MainClock(TFT_eSPI*tft);
   virtual void update(TFT_eSPI*tft);
   virtual void setup(TFT_eSPI*tft);
   void printLocalTime(TFT_eSPI*tft);

//end of the derivered class
};

 //End of include guards
#endif
