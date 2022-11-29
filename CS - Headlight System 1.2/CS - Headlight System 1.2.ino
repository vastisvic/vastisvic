// CS - Headlight System 1.2
// Created: 2022-10-16
// Author: Victoria Rea Vastis

// Libraries
#include <FastLED.h>              // Imports FastLED library

// General Variables
#define MAX_BRIGHTNESS 150        // Ranges from 0 to 255 (Brightness is defined as a byte)
#define MIC_PIN A0                // Sets microphone pin
#define DIAL_PIN A1               // Sets dial pin (Allows for change in LED colour)
#define SENSITIVITY 180           // Sets sensitivity value - Ranges from 0 to 1300 --> Lower to raise sensitivity
#define BUTTON_PIN A2              // Sets button pin
#define SATURATION 200            // Ranges from 0 to 255 (Satriation is defined as a byte)
#define MINVAL 60                 // Any analog input below this value is background noise


//LH LED Strip Variables
#define LH_LEDs_NUM 13            // # of LH LEDs
#define LH_LEDs_PIN 2             // Sets LH LED pin    
CRGB ledsLH[LH_LEDs_NUM];         // Creates an array of CRGB objects to set/clear LED data
byte brightnessLH[LH_LEDs_NUM];   // Creates an array of bytes to set/clear brightness data

//Centre LED Strip Variables
#define C_LEDs_NUM 40             // # of C LEDs
#define C_LEDs_PIN 3              // Sets C LED pin 
CRGB ledsC[C_LEDs_NUM];           // Creates an array of CRGB objects to set/clear LED data
byte brightnessC[C_LEDs_NUM];     // Creates an array of bytes to set/clear brightness data


//RH LED Strip Variables
#define RH_LEDs_NUM 13            // # of RH LEDs
#define RH_LEDs_PIN 4             // Sets RH LED pin 
CRGB ledsRH[RH_LEDs_NUM];         // Creates an array of CRGB objects to set/clear LED data
byte brightnessRH[RH_LEDs_NUM];   // Creates an array of bytes to set/clear brightness data

//Define Input Integers
int microphoneVal;
int dialVal;
int buttonState;
int buttonVal = 1;                // 1 is the initial state of the button --> There are 5 states in total  
int ledColour;
int tunedData;                    // Tuned microphone data based on sensitivity

void setup() {
  Serial.begin(9600);               // Opens serial monitor

  // Define I/O PINS:
  pinMode(MIC_PIN, INPUT);
  pinMode(DIAL_PIN, INPUT);
  pinMode(BUTTON_PIN, INPUT);
  
  // Defines LED Pins
  FastLED.addLeds<WS2812, LH_LEDs_PIN>(ledsLH, LH_LEDs_NUM);
  FastLED.addLeds<WS2812, C_LEDs_PIN>(ledsC, C_LEDs_NUM);
  FastLED.addLeds<WS2812, RH_LEDs_PIN>(ledsRH, RH_LEDs_NUM);

  //Clears all LED Strips
  ClearLEDs();
  FastLED.show(); 
}

//-------------------------------------------------------------------------------------------------------
// MAIN CODE
void loop() {
  GetLEDColour();

  CheckMicVal();
  GetButtonState();
  tunedData = buttonVal;

  // Cues Static LEDs
  while (tunedData = 1){
    GetLEDColour();
    CheckMicVal();

    StaticLEDs();
    FastLED.show();

    GetButtonState();
    if (buttonVal != 1){
      break; 
    }
  }
  // Cues Sparkle LEDs
  while (tunedData = 2){
    GetLEDColour();
    CheckMicVal();

    AmbreLEDs();
    FastLED.show();

    GetButtonState();
    if (buttonVal != 2){
      break; 
    }
  }
  // Cues Dance LEDs
  while (tunedData = 3){
    GetLEDColour();
    CheckMicVal();

    DanceLEDs_C(); 
    DanceLEDs_LH(); 
    DanceLEDs_RH(); 
    FastLED.show();

    GetButtonState();
    if (buttonVal !=3){
      break; 
    }
    delay(10);
  }
  // Cues Pulse LEDs
  while (tunedData = 4){
    GetLEDColour();
    CheckMicVal();

    PulseLEDs();
    FastLED.show();

    GetButtonState();
    if (buttonVal != 4){
      break; 
    }
    delay(10);
  }
  // Cues Radiate LEDs
  while (tunedData = 5){
    GetLEDColour();
    CheckMicVal();


    RadiateLEDs_C();
    RadiateLEDs_LH();
    RadiateLEDs_RH();
    FastLED.show();

    GetButtonState();
    Serial.println(buttonVal);
    if (buttonVal != 5){
      break; 
    }
    delay(10);
  }

}
//--------------------------------------------------------------------------------------------------------


// FUNCTIONS

void ClearLEDs(){
// ClearLEDs takes the # of LEDs and the LED array as input to turn off all the LEDs instantly
  //CRGB leds[NUM_LEDs];
  for(int i=0; i <= LH_LEDs_NUM ; i++){
    ledsLH[i].nscale8(10);
    ledsRH[i].nscale8(10);
  }
  for(int i=0; i <= C_LEDs_NUM ; i++){
    ledsC[i].nscale8(10);
  }
}


void GetLEDColour(){
// GetLEDColour converts the analog input from the dial and scales it to the range of the hue data byte
  dialVal = analogRead(DIAL_PIN);
  dialVal = map(dialVal, 0, 1023, 0, 255);

}


void CheckMicVal(){
// Tunes the microphone input to be align w/ the sensitivity parameter
  microphoneVal = analogRead(MIC_PIN);

  if(microphoneVal > SENSITIVITY)
  microphoneVal = SENSITIVITY; 

  if(microphoneVal < MINVAL)
  microphoneVal = 0;
  
}


void GetButtonState(){
// Returns the state of the button based on how many times its been pushed since the system turned on
// There are five LED states:
//       - Static -->  buttonVal = 1
//       - Sparkle --> buttonVal = 2
//       - Dance -->   buttonVal = 3
//       - Pulse -->   buttonVal = 4
//       - Radiate --> buttonVal = 5
buttonState = analogRead(BUTTON_PIN);
//Serial.println(buttonState);
  if (buttonState > 1015){
    delay(350);
    if (buttonVal == 5) {
      buttonVal = 1;
    }
    else {
      buttonVal = buttonVal + 1;
    }
  }
}
// LED Mode Functions

void StaticLEDs(){
  for(int i=0; i <= LH_LEDs_NUM ; i++){
    ledsLH[i] = CHSV(dialVal, SATURATION, MAX_BRIGHTNESS);
    ledsRH[i] = CHSV(dialVal, SATURATION, MAX_BRIGHTNESS);
  }
  for(int i=0; i <= C_LEDs_NUM ; i++){
    ledsC[i] = CHSV(dialVal, SATURATION, MAX_BRIGHTNESS);
  }
}

void AmbreLEDs(){
  for(int i=0; i <= LH_LEDs_NUM ; i++){
    ledsLH[i] = CHSV(dialVal - i*5, SATURATION, MAX_BRIGHTNESS);
    ledsRH[i] = CHSV(dialVal - i*5, SATURATION, MAX_BRIGHTNESS);
  }
  for(int i = 0; i <= C_LEDs_NUM/2; i++){
    ledsC[(C_LEDs_NUM/2)+i] = CHSV(dialVal - 3*i, SATURATION, MAX_BRIGHTNESS);
    ledsC[(C_LEDs_NUM/2)-i] = CHSV(dialVal - 3*i, SATURATION, MAX_BRIGHTNESS);
  }
}


void DanceLEDs_C(){
  byte micVolume = map(microphoneVal, 0, SENSITIVITY, 0, C_LEDs_NUM/2);
  for(int i = 0; i <= micVolume; i++){
    ledsC[(C_LEDs_NUM/2)+i] = CHSV(dialVal - 3*i, SATURATION, MAX_BRIGHTNESS);
    ledsC[(C_LEDs_NUM/2)-i] = CHSV(dialVal - 3*i, SATURATION, MAX_BRIGHTNESS);
  }
  for(int i = micVolume + 1; i <= (C_LEDs_NUM/2); i++){
    ledsC[(C_LEDs_NUM/2)+i].nscale8(10);
    ledsC[(C_LEDs_NUM/2)-i].nscale8(10);
  }
}


void DanceLEDs_LH(){
  byte micVolume = map(microphoneVal, 0, SENSITIVITY+1, 0, LH_LEDs_NUM);
  for(int i = 0; i <= micVolume; i++){
    ledsLH[i] = CHSV(dialVal - 3*i, SATURATION, MAX_BRIGHTNESS);
  }
  for(int i = micVolume + 1; i <= LH_LEDs_NUM; i++){
    ledsLH[i].nscale8(10);
  }
}

void DanceLEDs_RH(){
  byte micVolume = map(microphoneVal, 0, SENSITIVITY+1, 0, RH_LEDs_NUM);
  for(int i = 0; i <= micVolume; i++){
    ledsRH[i] = CHSV(dialVal - 3*i, SATURATION, MAX_BRIGHTNESS);
  }
  for(int i = micVolume + 1; i <= RH_LEDs_NUM; i++){
    ledsRH[i].nscale8(10);
  }
}

void PulseLEDs(){
  byte micVolume = map(microphoneVal, 0, SENSITIVITY+1, 0, MAX_BRIGHTNESS);
  for(int i = 0; i <= C_LEDs_NUM; i++){
    ledsC[i] = CHSV(dialVal, SATURATION, micVolume);
  }
  for(int i = 0; i <= LH_LEDs_NUM; i++){
    ledsLH[i] = CHSV(dialVal, SATURATION, micVolume);
    ledsRH[i] = CHSV(dialVal, SATURATION, micVolume);
  }
}

void RadiateLEDs_C(){
  byte micVolume = map(microphoneVal, 0, SENSITIVITY, 0, C_LEDs_NUM/2);

  if(micVolume >= C_LEDs_NUM/2){
      ledsC[C_LEDs_NUM/2 - 1] = CHSV(dialVal, SATURATION, MAX_BRIGHTNESS);
      ledsC[C_LEDs_NUM/2] = CHSV(dialVal, SATURATION, MAX_BRIGHTNESS);
    }
    else if(micVolume >= C_LEDs_NUM/4){
      ledsC[C_LEDs_NUM/2 - 1] = CHSV(dialVal - 25, SATURATION, MAX_BRIGHTNESS);
      ledsC[C_LEDs_NUM/2] = CHSV(dialVal - 25, SATURATION, MAX_BRIGHTNESS);
    }
    else if(micVolume >= C_LEDs_NUM/5){
      ledsC[C_LEDs_NUM/2 - 1] = CHSV(dialVal - 50, SATURATION, MAX_BRIGHTNESS);
      ledsC[C_LEDs_NUM/2] = CHSV(dialVal - 50, SATURATION, MAX_BRIGHTNESS);
    }
    else{
      ledsC[C_LEDs_NUM/2 - 1] = CHSV(0, 0, 0);
      ledsC[C_LEDs_NUM/2] = CHSV(0, 0, 0);
    }
      for (int i = 0; i <= C_LEDs_NUM/2 - 2; i++){
      ledsC[i] = ledsC[i+1];
      ledsC[(C_LEDs_NUM - 1) - i] = ledsC[(C_LEDs_NUM - 2) - i];
    }
}

void RadiateLEDs_LH(){
  byte micVolume = map(microphoneVal, 0, SENSITIVITY, 0, LH_LEDs_NUM);
  //Serial.println(micVolume);
  if(micVolume >= LH_LEDs_NUM/1.2){
      ledsLH[LH_LEDs_NUM-1] = CHSV(dialVal, SATURATION, MAX_BRIGHTNESS);
    }
    else if(micVolume >= LH_LEDs_NUM/2){
      ledsLH[LH_LEDs_NUM-1] = CHSV(dialVal - 25, SATURATION, MAX_BRIGHTNESS);
    }
    else if(micVolume >= LH_LEDs_NUM/3){
      ledsLH[LH_LEDs_NUM-1] = CHSV(dialVal - 50, SATURATION, MAX_BRIGHTNESS);
    }
    else{
      ledsLH[LH_LEDs_NUM-1] = CHSV(0, 0, 0);
    }
      for (int i = 0; i <= LH_LEDs_NUM-2; i++){
      ledsLH[i] = ledsLH[i+1];
    }
}

void RadiateLEDs_RH(){
  byte micVolume = map(microphoneVal, 0, SENSITIVITY, 0, RH_LEDs_NUM);
  Serial.println(micVolume);
  if(micVolume >= LH_LEDs_NUM/1.2){
      ledsRH[RH_LEDs_NUM-1] = CHSV(dialVal, SATURATION, MAX_BRIGHTNESS);
    }
    else if(micVolume >= LH_LEDs_NUM/2){
      ledsRH[RH_LEDs_NUM-1] = CHSV(dialVal - 25, SATURATION, MAX_BRIGHTNESS);
    }
    else if(micVolume >= RH_LEDs_NUM/3){
      ledsRH[RH_LEDs_NUM-1] = CHSV(dialVal - 50, SATURATION, MAX_BRIGHTNESS);
    }
    else{
      ledsRH[RH_LEDs_NUM-1] = CHSV(0, 0, 0);
    }
      for (int i = 0; i <= RH_LEDs_NUM-2; i++){
      ledsRH[i] = ledsRH[i+1];
    }
}


