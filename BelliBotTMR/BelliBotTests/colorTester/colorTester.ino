#include "Color.h"

Color colorSensor; 

void setup() {
  Serial.begin(9600);
  colorSensor.initiate();  
}

void loop() {  
  colorSensor.calculateDirection();
  int line = colorSensor.getDirection();
  //colorSensor.muxSensor(); 
  Serial.println(line);
  delay(50);  
}