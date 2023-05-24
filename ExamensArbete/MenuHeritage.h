/*
 
 #Can be used to further develop the system with external och internal buttons to create a menu like visualization

 
 #ifndef MENUHERITAGE_H
#define MENUHERITAGE_H

#include "Menu.h"
#include <TFT_eSPI.h>

class MenuHeritage : public Menu {
public:
  MenuHeritage(TFT_eSPI& tft, int buttonUpPin, int buttonDownPin); // Constructor
  void setup(); // Override the setup function from the base class
  void handleInput(); // Override the handleInput function from the base class
  void drawMenu(); // Override the drawMenu function from the base class

private:
  TFT_eSPI& tft; // Reference to the TFT display object
  int buttonUpPin; // GPIO pin for the "Up" button
  int buttonDownPin; // GPIO pin for the "Down" button
 // Button buttonUp; // Button object for the "Up" button
 // Button buttonDown; // Button object for the "Down" button
  int menuSelection; // Current menu selection
  
};
#endif*/
