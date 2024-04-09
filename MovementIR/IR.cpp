#include "Arduino.h"
#include "IR.h"
#include "SingleEMAFilterLib.h"

SingleEMAFilter<double> filterAngle(0.6); 
SingleEMAFilter<double> filterStr(0.6); 

IR::IR(){
}

void IR::initiate(unsigned long* current_time) {
    this -> current_time = current_time; 
    Serial3.begin(115200); 
    Serial3.setTimeout(100); 
}

void IR::updateData(){
    if (Serial3.available()) {
    String input = Serial3.readStringUntil('\n');

    if (input[0] == 'a') {
      angle = input.substring(2, input.length()).toDouble();
      angle += offset;
      filterAngle.AddValue(angle);
    }
    else if (input[0] == 'r'){
      strength = input.substring(2, input.length()).toDouble();
      filterStr.AddValue(strength);
    }
  }
  last_time = *current_time;

} 

void IR::setOffset(double offset) {
  this->offset = offset;
} 

double IR::getAngle() {
  return angle;
} 

double IR::getStrength() {
  return filterStr.GetLowPass();
}
   

double IR::mapAngleWithOffset(double angle) {
    angle += 7;
    if (angle >= 360) {
        angle -= 360;
    }
    return angle;
}
