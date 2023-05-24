/*

#Can be used to further develop the system with external och internal buttons to create a menu like visualization
 
#include "Menu.h"

Menu::Menu(TFT_eSPI*tft, int buttonUpPin, int buttonDownPin)
  : tft(tft), buttonUpPin(buttonUpPin), buttonDownPin(buttonDownPin) {
  // Initialize the button objects
  buttonUp.setup(buttonUpPin);
  buttonDown.setup(buttonDownPin);
}

  void MenuHeritage::setup() {
  // Perform any necessary setup for the menu
  // This could include initializing the display, setting up the buttons, etc.
  tft.init();
  tft.setRotation(0); // Set the display rotation if needed
}

void MenuHeritage::handleInput() {
   // Read the button states and handle user input
  if (buttonUp.isPressed()) {
    menuSelection--;
    if (menuSelection < 0) {
      menuSelection = 2; // Set the maximum menu selection index
    }
  } else if (buttonDown.isPressed()) {
    menuSelection++;
    if (menuSelection > 2) {
      menuSelection = 0; // Set the minimum menu selection index
    }
  }
}

void Menu::drawMenu() {
  // Clear the screen
  tft.fillScreen(TFT_BLACK);

  // Display menu items
  tft.setTextColor(TFT_WHITE);
  tft.setTextSize(2);
  tft.setCursor(50, 50);
  tft.println("Menu Item 1");

  tft.setCursor(50, 100);
  tft.println("Menu Item 2");

  tft.setCursor(50, 150);
  tft.println("Menu Item 3");

  // Highlight the selected menu item
  int menuItemY = 50 + (menuSelection * 50);
  tft.drawRect(40, menuItemY - 10, 200, 40, TFT_WHITE);
}*/
