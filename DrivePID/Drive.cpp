#include "Arduino.h"
#include "Drive.h"

Drive::Drive(int m1_speed, int m1_p1, int m1_p2,
             int m2_speed, int m2_p1, int m2_p2,
             int m3_speed, int m3_p1, int m3_p2) {
  // parameters for each motor
  motor_1.set(m1_speed, m1_p1, m1_p2);
  motor_2.set(m2_speed, m2_p1, m2_p2);
  motor_3.set(m3_speed, m3_p1, m3_p2);
}

void Drive::initialize() {
  motor_1.startMotor();
  motor_2.startMotor();
  motor_3.startMotor();
}

// kinematic equations for lineal movement with error 
void Drive::linealMovementError(int degree, int speed, int error) {
  float m1 = sin(((60 - degree) * PI / 180));
  float m2 = sin(((180 - degree) * PI / 180));
  float m3 = sin(((300 - degree) * PI / 180)); 

  int speedA = (m1*speed);
  int speedB = (m2*speed);
  int speedC = (m3*speed);

  speedA -= error;
  speedB -= error;
  speedC -= error; 

  motor_1.setSpeed(speedA); 
  motor_2.setSpeed(speedB); 
  motor_3.setSpeed(speedC); 
} 


// set speed for motors
void Drive::setAllMotorSpeed(int all_speed) {
  analogWrite(motor_1.getMotorSpeed(), all_speed);
  analogWrite(motor_2.getMotorSpeed(), all_speed);
  analogWrite(motor_3.getMotorSpeed(), all_speed);
}

// turn off motors
void Drive::driveOff() {
  motor_1.stop();
  motor_2.stop();
  motor_3.stop();
}

void Drive::driveFrontward() {
  driveOff();
  motor_1.motorBackward(); 
  motor_2.motorFrontward(); 
}

void Drive::driveBackward() {
  motor_1.motorFrontward(); 
  motor_2.motorBackward(); 
}

// functions for rotation
void Drive::rotateH() {
  motor_1.motorFrontward();
  motor_2.motorFrontward();
  motor_3.motorFrontward();
}

void Drive::rotateAH() {
  motor_1.motorBackward();
  motor_2.motorBackward();
  motor_3.motorBackward(); 
}
