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

// kinematic equations for robot movement
void Drive::linealMovement(int degree, int speed) {
  float m1 = sin(((60 - degree) * PI / 180));
  float m2 = sin(((180 - degree) * PI / 180));
  float m3 = sin(((300 - degree) * PI / 180));
  int speedA = abs(int(m1 * speed));
  int speedB = abs(int(m2 * speed));
  int speedC = abs(int(m3 * speed));

  // set motor speeds
  analogWrite(motor_1.getMotorSpeed(), speedA);
  analogWrite(motor_2.getMotorSpeed(), speedB);
  analogWrite(motor_3.getMotorSpeed(), speedC);

  // rotate motors based on the angles
  if (m1 <= 0) {
    motor_1.motorFrontward();
  } else {
    motor_1.motorBackward();
  }

  if (m2 <= 0) {
    motor_2.motorFrontward();
  } else {
    motor_2.motorBackward();
  }

  if (m3 <= 0) {
    motor_3.motorFrontward();
  } else {
    motor_3.motorBackward();
  }

}

// kinematic equations for lineal movement with error 
void Drive::linealMovementError(int degree, int speed, int error, bool is_right) {
  float m1 = sin(((60 - degree) * PI / 180));
  float m2 = sin(((180 - degree) * PI / 180));
  float m3 = sin(((300 - degree) * PI / 180)); 

  int speedA = (m1*speed);
  int speedB = (m2*speed);
  int speedC = (m3*speed);

  speedA -= error;
  speedB -= error;
  speedC -= error;

 /*
  Serial.print("Motor A Speed: ");
  Serial.println(speedA);
  Serial.print("Motor B Speed: ");
  Serial.println(speedB);
  Serial.print("Motor C Speed: ");
  Serial.println(speedC); 

  int maxSpeed = max(speedA, max(speedB, speedC));
  if (maxSpeed > 255) {
    speedA = map(speedA, 0, maxSpeed, 0, 255);
    speedB = map(speedB, 0, maxSpeed, 0, 255);
    speedC = map(speedC, 0, maxSpeed, 0, 255);
  }
*/ 

  int absSpeedA = abs(speedA);
  int absSpeedB = abs(speedB);
  int absSpeedC = abs(speedC);

  analogWrite(motor_1.getMotorSpeed(), absSpeedA);
  analogWrite(motor_2.getMotorSpeed(), absSpeedB);
  analogWrite(motor_3.getMotorSpeed(), absSpeedC);

 if (speedA <= 0) {
    motor_1.motorFrontward();
  } else {
    motor_1.motorBackward();
  }

  if (speedB <= 0) {
    motor_2.motorFrontward();
  } else {
    motor_2.motorBackward();
  }

  if (speedC <= 0) {
    motor_3.motorFrontward();
  } else {
    motor_3.motorBackward();
  }
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
