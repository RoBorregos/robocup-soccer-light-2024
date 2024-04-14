#include "Arduino.h"
#include "Motor.h"

Motor::Motor() {}

// set motor
void Motor::set(int speed, int pin1, int pin2) {
  this->speed_ = speed;
  this->pin1_ = pin1;
  this->pin2_ = pin2;
}

// functions for motor movement
void Motor::startMotor() {
  pinMode(speed_, OUTPUT);
  pinMode(pin1_, OUTPUT);
  pinMode(pin2_, OUTPUT);
}

void Motor::motorFrontward() {
  digitalWrite(pin1_, HIGH);
  digitalWrite(pin2_, LOW);
}

void Motor::motorBackward() {
  digitalWrite(pin1_, LOW);
  digitalWrite(pin2_, HIGH);
}

void Motor::stop() {
  digitalWrite(pin1_, HIGH);
  digitalWrite(pin2_, HIGH); 
  analogWrite(speed_, 255); 
}

// getters
int Motor::getMotorSpeed() {
  return speed_;
}

int Motor::getPin1() {
  return pin1_;
}

int Motor::getPin2() {
  return pin2_;
}

void Motor::setSpeed(int speed){
  int absSpeed = abs(speed); 
  analogWrite(getMotorSpeed(), absSpeed); 

  if (speed <= 0) { 
      motorFrontward();
  } else {
    motorBackward();
  }

}