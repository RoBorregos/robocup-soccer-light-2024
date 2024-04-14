#include "Arduino.h"
#include "Color.h"


Color::Color() {}; 

void Color::initiate() {
    pinMode(s0_1, OUTPUT);
    pinMode(s1_1, OUTPUT);
    pinMode(s2_1, OUTPUT);
    pinMode(muxSignal_1, INPUT);

    pinMode(s0_2, OUTPUT);
    pinMode(s1_2, OUTPUT);
    pinMode(s2_2, OUTPUT);
    pinMode(muxSignal_2, INPUT);

    for (int i = 0; i < 4; i++) {
        pinMode(directPins[i], INPUT);
    }
}

void Color::selectChannel(int chnl, int mux) {
  int A = bitRead(chnl, 0);
  int B = bitRead(chnl, 1);
  int C = bitRead(chnl, 2);
  if (mux == 1) {
      digitalWrite(s0_1, A);
      digitalWrite(s1_1, B);
      digitalWrite(s2_1, C);
  } else if (mux == 2) {
      digitalWrite(s0_2, A);
      digitalWrite(s1_2, B);
      digitalWrite(s2_2, C);
  }
}

void Color::readSensors() { 
    // Read from both multiplexers
    for (int mux = 1; mux <= 2; mux++) {
        for (int i = 0; i < 8; i++) {
            selectChannel(i, mux);
            int value = analogRead(mux == 1 ? muxSignal_1 : muxSignal_2);  
            Serial.print(value); 
            Serial.print(value > lineSensorThreshold[(mux - 1) * 8 + i] ? "Blanco" : "Verde"); 
            Serial.print(" ");
        }
    }

    // Read from direct sensors
    for (int i = 0; i < 4; i++) {
        int value = analogRead(directPins[i]);
        Serial.print(value); 
        Serial.print(value > lineSensorThreshold[16 + i] ? "Blanco" : "Verde"); 
        Serial.print(" ");
    }
    Serial.println(); 
} 


void Color::calculateDirection () { 
  lastDirection = -1;
    // Check all sensors
    for (int mux = 1; mux <= 2; mux++) {
        for (int i = 0; i < 8; i++) {
            selectChannel(i, mux);
            int value = analogRead(mux == 1 ? muxSignal_1 : muxSignal_2);
            if (value > lineSensorThreshold[(mux - 1) * 8 + i]) { 
                lastDirection = (sensorAngles[(mux - 1) * 8 + i] + 180) % 360;
                return; // Exit as soon as a line is detected
            }
        }
    }

    for (int i = 0; i < 4; i++) {
        int value = analogRead(directPins[i]);
        if (value > lineSensorThreshold[16 + i]) { 
            lastDirection = (sensorAngles[16 + i] + 180) % 360;
            return;
        }
    }
}

int Color::getDirection(){
  return lastDirection; 
}