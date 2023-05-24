#include <Arduino.h> //Access to string library 
#include "Component.h" //The Baseclass header file 
#include "MainClock.h" //Clock component 
#include "Weather.h" // Weather component  
#include "StopWatch.h" // StopWatch Component

//#include "MenuHeritage.h"
#include "EulaBG.h" //Cutom Background
#include "time.h" //Enables time function and methods an this case to get the time with wifi
#include <WiFi.h>  //Access to Wifi library and enables Wifi
#include <SPI.h>  // "Helper" for the TFT library 
#include <TFT_eSPI.h> //TFT library enables call to tft functions and methods , to display them on the modules screen 
TFT_eSPI tft = TFT_eSPI();       // Invoke custom library, Can only be included in main , if the components / function needs to access TFT it needs to have the TFT parameter in it's argument 


//MenuHeritage Menu(tft, buttonUpPin, buttonDownPin);

// Baseclass Array to store the components, calling the components in the loop function.
Component*components[3] = { 
    new MainClock(&tft),  // activeComponent = 0
    new StopwatchComponent(&tft), // activeComponent = 1
    new WeatherComponent(&tft),  // activeComponent = 2
    };

// userData
const char* ssid       = "ICHI NEETwork";  
const char* password   = "D1skasug3r!?"; 

//values of the internal buttons of the module.
const int PUSHBUTTON1 = 0;
const int PUSHBUTTON2 = 35;

//value of the variable is zero since the system should show the clock component first
int activeComponent = 0;
// button set to high to easily register the button will be pressed (LOW)
int activeButton = HIGH;

//Function connecting to the network with Wifi
void Connecting()
{  
  Serial.begin(9600) ;
   Serial.println(1);
  tft.setRotation(0);
   tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_WHITE,TFT_BLACK);  tft.setTextSize(1);
  tft.print("Connecting to ");
  tft.println(ssid);
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(300);
    tft.print(".");
  }
  
  tft.println("");
  tft.println("WiFi connected.");
  tft.println("IP address: ");
  tft.println(WiFi.localIP());
  delay(3000);
  tft.setTextColor(TFT_WHITE,TFT_BLACK);  tft.setTextSize(1);


}


void setup()
{  
    Serial.begin(9600);
   tft.init(); //initialize TFT for system.
   Connecting(); // calling the function to connetc to wifi.
 
    
   components[0]->setup(&tft); // calling the setup function in MainClock with the TFT parameter

  
   
  //Defining the internal buttons 
  pinMode(PUSHBUTTON1, INPUT_PULLUP);
  pinMode(PUSHBUTTON2, INPUT_PULLUP);
}

void loop()
{ 
  
  tft.setRotation(0); // Set screen position 
  Serial.println(activeComponent);
  components[activeComponent]->update(&tft); // Since the components are in array , we call the update function for the active component and display it on the screen.
 
 //Defining button to make it read that button will only be pressed once so the system will not reapeat button pressing.
 int NewactiveButton = digitalRead(PUSHBUTTON1);
if (NewactiveButton == HIGH && activeButton == LOW )
{
   // increasing the activeComponent by one to vhenge to a different component , ex from MainClock to StopWatch
  activeComponent++;
  
   components[1]->setup(&tft);  //Since the activeComponent is the StopWatch , we need to initialize the setup for Stopwatch so it can run. Setup function can't be in the setup function since it will overlap the other setup.
    
    //If statement to run setup for Wheater component when the activeComponent = 2.Setup function can't be in the setup function since it will overlap the other setup.
    if (activeComponent == 2)
    { 
      //Sets the background for the Wheather component
     tft.fillScreen(TFT_BLACK);
    tft.setSwapBytes(true);
    tft.pushImage(0,0,135,240,EulaBG);
    tft.setSwapBytes(true);

     components[2]->setup(&tft);
      tft.fillScreen(TFT_BLACK);
    tft.setSwapBytes(true);
    tft.pushImage(0,0,135,240,EulaBG);
    tft.setSwapBytes(true);
      }

      //If statement to reset the value of activeComponent to keep the system alive after the last component has been called 
  if (activeComponent>2)
  { 
    activeComponent = 0;
    //sets the Backround to clear the values from previous components
    tft.fillScreen(TFT_BLACK);
    tft.setSwapBytes(true);
    tft.pushImage(0,0,135,240,EulaBG);
    tft.setSwapBytes(true);
   
  }
}   
    //Declaring the activeButton to register the button is only pressed once
    activeButton = NewactiveButton;
    delay(100);
}
