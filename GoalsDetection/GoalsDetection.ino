#include "Arduino.h"
#include "Goals.h"

Goals goal;

void setup() {
  Serial.begin(9600);
  Serial1.begin(9600); //chang serial
  Serial1.setTimeout(100);
}

void loop() {
  if (Serial1.available() > 0) {
    String data = Serial1.readStringUntil('\n');
    Serial.println(data);

    // Update goal data
    goal.updateData(data);

    // Print goal data
    Serial.print("Tag: ");
    Serial.println(goal.getTag());
    Serial.print("X: ");
    Serial.println(goal.getX());
    Serial.print("Y: ");
    Serial.println(goal.getY());
    Serial.print("Width: ");
    Serial.println(goal.getWidth());
    Serial.print("Height: ");
    Serial.println(goal.getHeight());
    Serial.print("Area: ");
    Serial.println(goal.getArea());
  } 
  //Serial.print("arduino"); 
}
