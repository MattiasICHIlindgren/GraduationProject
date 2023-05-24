
//BaseClass headerfile

//Include guards
#ifndef COMPONENT_H
#define COMPONENT_H

#include <TFT_eSPI.h> //include the TFT library to pass it on as a parameter to the declared functions
#include <Arduino.h> // Include the Arduino library to access setup and update as virtual functions

//Baseclass
class Component 
{
public:
  //Since we need to call on multiple setup and update functions from each component , they need to be virtual 
  //The functions pass the TFT parameter to enable TFT in each component
  virtual void setup(TFT_eSPI*tft);
  virtual void update(TFT_eSPI*tft);
  
  
}; //End of the BaseClass
#endif //End of the include guard
