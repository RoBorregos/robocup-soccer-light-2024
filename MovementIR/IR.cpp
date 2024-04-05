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

double IR::calculateMovAngle (double ball_angle, double ball_distance) {  
  //do something if ball distance is less or equal than offset 
  //the offset is where the robot should start turning around the ball  
  int offset = 40; //calibrate offset   
  double target_angle = 0;    
  // 0
  if (ball_angle >= 20 && ball_angle <= 50) { // 60
    target_angle = 120;  
  } else if (ball_angle > 50 && ball_angle <= 138) { //120
    target_angle = 180; 
  } else if (ball_angle > 138 && ball_angle <= 190) { //180
    target_angle = 120;
  } else if (ball_angle > 190 && ball_angle <= 230) { //240
    target_angle = 180; 
  } else if (ball_angle > 230 && ball_angle <= 300)  { //300
    target_angle = 240;   
  } else {//0 
    target_angle = 0; 
  }

  return target_angle; 
}     

