
#pragma once //another type of include guard
#include <Arduino.h> // Include the Arduino library to enable arduino functions 
#include "Component.h" //BaseClass header file 
#include <string>  //Access to string library 
#include "stop.h" //cutom images for the component
#include "play.h" //cutom images for the component
#include "Eula.h" //Custom background for the component
#include "StopWatch.h" // Deriverd class header file containing the neccessary decleration of  functions that the cpp file needs in order to read 

#include <SPI.h> // "Helper" for the TFT library 
#include <TFT_eSPI.h> //TFT library enables call to tft functions and methods , to display them on the modules screen                


#include "DSEG7_Classic_Regular_16.h" //Custom font

//Colour definition
#define grey 0x65DB
#define color 0xF251

//variables for the Component
int ss=0; //miliseconds/10
int s=0;   //seconds
int m=0;  //minutes

int lss[30];
int ls[30];
int lm[30];

String minutesL;
String secondsL;
String milisL;
int laps=0;
String lapTime[30];
int pom=0;  //debouncing button
int pom2=0;
int pres3 =0;//deboun

int fase=0;
int c=0;

const int pwmFreq = 5000;
const int pwmResolution = 8;
const int pwmLedChannelTFT = 0;

String seconds,minutes,milis;
String current,temp;

int winer=0;

long tt=0;
long tt2=0;

StopwatchComponent::StopwatchComponent(TFT_eSPI*tft) //StopWatch Contructor with TFT parameter to enable TFT in the component
{
  
}

void StopwatchComponent::setup(TFT_eSPI*tft) //Setup function for StopWatch with a TFT parameter to access the TFT library from 
{

   
   pinMode(35,INPUT_PULLUP); // Setting the button 
 
  //Decalring the setup functions for the stopwatch
  ledcSetup(pwmLedChannelTFT, pwmFreq, pwmResolution);
  ledcAttachPin(TFT_BL, pwmLedChannelTFT);
  ledcWrite(pwmLedChannelTFT, 67);
  //resets the values 
   reset(tft);
}




void StopwatchComponent::buttons(TFT_eSPI*tft) // Function for the internal buttons for the component 
{
    //when button pressed 
    if(digitalRead(35)==0 )
  {
   if(pom2==0)
     {
    fase++;
    if(fase==3)
    {
      tft->fillScreen(TFT_BLACK);
       tft->setRotation(0);
    tft->setSwapBytes(true);
    tft->pushImage(0,0,135,240,LAwrence_Eula);
      tft->setFreeFont(&DSEG14_Classic_Mini_Regular_15);
      tft->drawString("TIME:",10,6,2);
      tft->drawString("LAP:",10,50,2);
      tft->drawString(current+":"+milis,10,28);
      for(int i=0;i<laps;i++){
      
      tft->drawString(String(i+1)+".   "+lapTime[i],10,68+(14*i),2);}
      }
    if(fase>3)
       {
         
         reset(tft);

       }
   
    pom2=1;
     }
  }else{pom2=0;}

  }

  
  void StopwatchComponent::reset(TFT_eSPI*tft) //Reset the values 
  {
    tft->fillScreen(TFT_BLACK); //Clear screen
        tft->setRotation(0);
    tft->setSwapBytes(true);
    tft->pushImage(0,0,135,240,LAwrence_Eula);
    tft->pushImage(7,75,48,48,stop);
    tft->pushImage(30,136,72,72,play);
    tft->drawString("STOPWATCH",30,7,2);
    tft->drawString("BAT 72%",15,222,2);
    
    tft->fillRect(105,224,4,12,color); 
    tft->setFreeFont(&DSEG7_Classic_Regular_32);
    tft->drawLine(0,220,128,220,grey);
    laps=0;
    lss[0]=0;
    ls[0]=0;
    lm[0]=0;
    ss=0;
    s=0;
    m=0;
    fase=0;
    winer=0;
  }
  
  void StopwatchComponent::update(TFT_eSPI*tft) //the loop function for StopWatch with a TFT parameter
  {

     
 if(fase<3){
  tt=millis();
  tft->setFreeFont(&DSEG7_Classic_Regular_32);
  if(s<10) seconds="0"+String(s);else seconds=String(s);
  if(m<10) minutes="0"+String(m);else minutes=String(m);
  current=minutes+":"+seconds;

  
  if(current!=temp){
  tft->drawString(current,10,30);
  temp=current;
  }
  
  if(ss<10) milis="0"+String(ss);else milis=String(ss);
  tft->drawString(milis,60,76,7);
  }

  if(tt>tt2+8)
  {  
     tt2=tt;
     if(fase==1)
     ss++;
  }

  if(ss>99)
{
  s++;
  ss=0;
}
  if(s>59)
  {
    s=0;
    m++;
  }
 buttons(tft); 
}
  
