#include "Arduino.h"
#include "IR.h"

IR ringIR;

void setup() {
  Serial.begin(115200);
  unsigned long currentTime = millis();
  ringIR.initiate(&currentTime);
  ringIR.setOffset(0.0);
}

void loop() {
  ringIR.updateData(); 

  double angle = ringIR.getAngle();
  double strength = ringIR.getStrength();
  
  Serial.print("angle: ");
  Serial.print(angle);
  Serial.print("\tradio: ");
  Serial.println(strength);

  delay(50); 
} 