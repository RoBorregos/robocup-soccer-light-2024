#include "Arduino.h"
#include "Color.h"


Color::Color() {}; 

void Color::initiate() {
  for (int i = 0; i < 12; i++) {
    pinMode(directPins[i], INPUT);
  } 
}


void Color::muxSensor() { 
  for (int i = 0; i < 12; i++) {
    int value = analogRead(directPins[i]);
    Serial.print(value > thresholdDirect[i] ? "White" : "Green"); 
    Serial.print(" ");
  }
  Serial.println(); 

} 

void Color::calculateDirection () { 
  lastDirection = -1; 
  
  for (int i = 0; i < 12; i++) {
    int value = analogRead(directPins[i]);
    if (value > thresholdDirect[i]) { 
        lastDirection = (anglesDirect[i] + 180) % 360;
      break;
    }
  }
  Serial.println(); 
}

int Color::getDirection(){
  return lastDirection; 
}