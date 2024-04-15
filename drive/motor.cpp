#include "Arduino.h"
#include "drive.h"

motor::motor() {};

//Set motor
void motor::set(int motorSpeed, int pin1, int pin2) {
  this-> motorSpeed = motorSpeed;
  this-> pin1 = pin1;
  this-> pin2 = pin2;
}

//functions for movement
void motor::startMotor() {
  pinMode(motorSpeed, OUTPUT);
  pinMode(pin1, OUTPUT);
  pinMode(pin2, OUTPUT);
}

void motor::motorFrontward() {
  digitalWrite(pin1, HIGH);
  digitalWrite(pin2, LOW);
}

void motor::motorBackward() {
  digitalWrite(pin1, LOW);
  digitalWrite(pin2, HIGH);
}

void motor::stopMotor() {
  digitalWrite(pin1, LOW);
  digitalWrite(pin2, LOW);
}

//Getters
int motor::getMotorSpeed() {
  return motorSpeed;
}

int motor::getPin1() {
  return pin1;
}

int motor::getPin2() {
  return pin2;
} 

