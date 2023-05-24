//Iclude guards 
#ifndef WEATHER_H
#define WEATHER_H
//The Baseclass header file 
#include "Component.h"
#include <string>  //Access to string library 
#include <Arduino.h> // Include the Arduino library to access setup and update as virtual functions
#include <TFT_eSPI.h> //TFT library enables call to tft functions and methods , to display them on the modules screen 

//Derivered class for Weather
class WeatherComponent : public Component

 {
  public:
   //functions for the Weather CPP file.
  WeatherComponent(TFT_eSPI*tft);
  void Time(TFT_eSPI*tft); 
  void getData(TFT_eSPI*tft);
  virtual void update(TFT_eSPI*tft);
  virtual void setup(TFT_eSPI*tft);
  

 }; // end of the class

 #endif //end of include guards
