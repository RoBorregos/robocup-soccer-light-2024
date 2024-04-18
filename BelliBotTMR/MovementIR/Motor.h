#ifndef Motor_h_
#define Motor_h_

#include "Arduino.h" 
#pragma once

class Motor {
 public:
  Motor();

  void set(int speed, int pin1, int pin2); 
  void startMotor();
  void stop();
  void motorFrontward();
  void motorBackward(); 
  void setSpeed(int speed); 
  int getMotorSpeed();
  int getPin1();
  int getPin2(); 

 private:
  int speed_;
  int pin1_; 
  int pin2_; 
};

#endif  
