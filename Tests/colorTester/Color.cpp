#include "Arduino.h"
#include "Color.h"


Color::Color() {}; 

void Color::initiate() {
    pinMode(s0, OUTPUT);
    pinMode(s1, OUTPUT);
    pinMode(s2, OUTPUT);
    pinMode(sig, INPUT);
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
      int value = analogRead(sig); 
      Serial.print(value > thresholdMux[i] ? "White" : "Green"); 
      Serial.print(" ");
  }

  for (int i = 0; i < 8; i++) {
    int value = analogRead(directPins[i]);
    Serial.print(value > thresholdDirect[i] ? "White" : "Green"); 
    Serial.print(" ");
  }
  Serial.println(); 

} 

void Color::calculateDirection () { 
  lastDirection = -1; 

  for (int i = 0; i < 8; i++) {
      selectChannel(i);
      int value = analogRead(sig); 
      if (value > thresholdMux[i]) { 
        lastDirection = (anglesMux[i] + 180) % 360;
        /*
        Serial.print("Sensor mux: "); 
        Serial.print(anglesMux[i]); 
        Serial.print(i); 
        Serial.println(lastDirection);  
        */
      break;
      }
  }
  
  for (int i = 0; i < 8; i++) {
    int value = analogRead(directPins[i]);
    if (value > thresholdDirect[i]) { 
        lastDirection = (anglesDirect[i] + 180) % 360;
        /*
        Serial.print("Sensor direct: "); 
        Serial.print(i); 
        Serial.println(lastDirection); 
        */
      break;
    }
  }
  Serial.println(); 
}

int Color::getDirection(){
  return lastDirection; 
}