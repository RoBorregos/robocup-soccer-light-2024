#include "Arduino.h"
#include "drive.h"

drive::drive (int m1Speed, int m1P1, int m1P2, int m2Speed, int m2P1, int m2P2, int m3Speed, int m3P1, int m3P2) {
  //parameters for each motor
  motor1.set(m1Speed, m1P1, m1P2);
  motor2.set(m2Speed, m2P1, m2P2);
  motor3.set(m3Speed, m3P1, m3P2);
}

void drive::initialize() {
  motor1.startMotor();
  motor2.startMotor();
  motor3.startMotor();
}

//kinematic equations for robot movement
void drive::linealMovement(int degree, int speed) {

  float m1 = sin(((60 - degree) * PI / 180));
  float m2 = sin(((180 - degree) * PI / 180));;
  float m3 = sin(((300 - degree) * PI / 180));
  int speedA = abs(int(m1 * speed));
  int speedB = abs(int(m2 * speed));
  int speedC = abs(int(m3 * speed));

  //set motor speeds
  analogWrite(motor1.getMotorSpeed(), speedA);
  analogWrite(motor2.getMotorSpeed(), speedB);
  analogWrite(motor3.getMotorSpeed(), speedC);

  //rotate motors based on the angles
  if (m1 >= 0) {
    motor1.motorFrontward();
  } else {
    motor1.motorBackward();
  }

  if (m2 >= 0) {
    motor2.motorFrontward();
  } else {
    motor2.motorBackward();
  }

  if (m3 >= 0) {
    motor3.motorFrontward();
  } else {
    motor3.motorBackward();
  }

}

//set speed for motors
void drive::setAllMotorSpeed(int allSpeed) {
  analogWrite(motor1.getMotorSpeed(), allSpeed);
  analogWrite(motor2.getMotorSpeed(), allSpeed);
  analogWrite(motor3.getMotorSpeed(), allSpeed);
}

//turn off motors
void drive::driveOff() {
  motor1.stopMotor();
  motor2.stopMotor();
  motor3.stopMotor();
}

void drive::driveFrontward() {
  driveOff();
  motor1.motorBackward();
  motor2.motorFrontward();
}

void drive::driveBackward() {
  motor1.motorFrontward();
  motor2.motorBackward();
}

//tests for various angles
void drive::movementTester(int speeds) {
  linealMovement(0, speeds);
  delay(1000);

  linealMovement(60, speeds);
  delay(1000);

  linealMovement(180, speeds);
  delay(1000);

  linealMovement(300, speeds);
  delay(1000);

  linealMovement(45, speeds);
  delay(1000);

  linealMovement(90, speeds);
  delay(1000);

  linealMovement(135, speeds);
  delay(1000);
}

//functions for moving each motor 
void drive::move1() {
  motor1.motorFrontward();
}
void drive::move2() {
  motor2.motorFrontward();
}
void drive::move3() {
  motor3.motorFrontward();
}