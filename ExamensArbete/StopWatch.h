//Iclude guards so the header file won't be dublicatedv
#ifndef STOPWATCH_H
#define STOPWATCH_H

//The Baseclass header file 
#include "Component.h"
#include <string>  //Access to string library 
#include <Arduino.h> // Include the Arduino library to access setup and update as virtual functions
#include <TFT_eSPI.h> //TFT library enables call to tft functions and methods , to display them on the modules screen 

//Derivered class for the stopwatch
class StopwatchComponent : public Component 
{
 public :
  //functions for the StopWatch CPP file.
  StopwatchComponent(TFT_eSPI*tft);
  void reset(TFT_eSPI*tft); 
  void buttons(TFT_eSPI*tft);
  virtual void setup(TFT_eSPI*tft);
  virtual void update(TFT_eSPI*tft);
  

};// End of class 

 #endif //End of the include guards
