#include "Arduino.h"
#include "IR.h"

IR ringIR;

void setup() {
  Serial.begin(9600);
  unsigned long currentTime = millis();
  ringIR.initiate(&currentTime);
  ringIR.setOffset(0.0);
}

void loop() {
  ringIR.updateData(); 

  double angle = ringIR.getAngle(); 
  double newAngle = (angle < 0 ? 360 + angle : angle); 
  newAngle = 360 - newAngle; 
  double strength = ringIR.getStrength();
  
  Serial.print("angle: "); 
  Serial.print(newAngle);
  Serial.print("\tradio: ");
  Serial.println(strength);

  delay(50); 
} 