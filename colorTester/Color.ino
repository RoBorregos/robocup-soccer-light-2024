#include "Color.h"

Color colorSensor; 

void setup() {
  Serial.begin(9600);
  colorSensor.initiate();  
  colorSensor.calibrate(); 
}

void loop() {
  double lineAngle = colorSensor.recoveryAngle();

  if (lineAngle >= 0) {
    Serial.print("angle of the line detected: ");
    Serial.println(lineAngle); 
    Serial.print("angle where it should move: ");
    Serial.println(lineAngle + 180) % 360;
    
  } else {
    Serial.println("no line detected");
  }

  delay(1000);   

}  