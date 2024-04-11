#include "Arduino.h"
#include "Color.h"


Color::Color() {}; 

void Color::initiate() {
    pinMode(s0, OUTPUT);
    pinMode(s1, OUTPUT);
    pinMode(s2, OUTPUT);
    pinMode(A15, INPUT);
}

void Color::selectChannel(int chnl) {
  int A = bitRead(chnl, 0);
  int B = bitRead(chnl, 1);
  int C = bitRead(chnl, 2);
  digitalWrite(s0, A);
  digitalWrite(s1, B);
  digitalWrite(s2, C);
}

void Color::muxSensor() { 
  for (int i = 0; i < 8; i++) {
    selectChannel(i);
    int value = analogRead(A15);  
    Serial.print(value); 
    Serial.print(value > lineSensorThreshold[i] ? "Blanco" : "Verde"); 
    Serial.print(" ");
  }  
  Serial.println(); 
} 

void Color::calculateDirection () { 
  lastDirection = -1; 
  for (int i = 0; i < 8; i++) {
    selectChannel(i);
    int value = analogRead(A15); 
    if (value > lineSensorThreshold[i]) { 
      lastDirection = (sensorAngles[i] + 180) % 360;
      break;
    } 
  } 
}

int Color::getDirection(){
  return lastDirection; 
}