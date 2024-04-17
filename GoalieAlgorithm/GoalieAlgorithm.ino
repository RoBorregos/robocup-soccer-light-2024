// Algorithm for Goalie TMR 
#include "BNO.h"
#include "Drive.h" 
#include "PID.h" 
#include "IR.h"
#include "Color.h"

Drive robot_drive(4, 23, 22, 5, 25, 24, 6, 27, 26); // change in pins
BNO orientation_sensor;  
PID pid(3.9, 0.4, 0.09);   // change in PID
IR ringIR; 
Color colorSensor;

int speed_tester = 210;   
unsigned long previous_time = 0;  
int kFrequency = 10; 
double ballDistance = 0; 
double ballAngle = 0;   
int angleLine = 0; 

void setup (){ 
    Serial.begin(9600);  
    Serial1.begin(115200);
    unsigned long currentTime = millis();
    orientation_sensor.initialize(); 
    robot_drive.initialize();
    ringIR.initiate(&currentTime);
    ringIR.setOffset(0.0); 
    colorSensor.initiate(); 
}
 
void loop() {
  unsigned long time = millis();
  ringIR.updateData();
  ballDistance = ringIR.getStrength();
  ballAngle = ringIR.getAngle();
  colorSensor.calculateDirection();
  angleLine = colorSensor.getDirection();

  if ((time - previous_time) > kFrequency) {
      if (angleLine != -1) {
          double yaw = orientation_sensor.getYaw();
          double control = pid.calculateError(yaw, 0);
          exitLine(angleLine, control);
      } else {
          orientation_sensor.readValues();

          ballAngle = (ballAngle < 0 ? 360 + ballAngle : ballAngle);
          ballAngle = 360 - ballAngle;
          ballAngle = ringIR.mapAngleWithOffset(ballAngle);

          if (ballDistance != 0) { // if ball strenght is close and you are in the beyond middle line, defend, if ball strenght is not close, return to initial position. 
              double yaw = orientation_sensor.getYaw();
              double control = pid.calculateError(yaw, 0);
              defendGoal(ballAngle, ballDistance, control);

          } else {
              Serial.println("no ball detected");
              returnToInitialPosition();
          }
          previous_time = time;
      }
  }
}

void defendGoal(double ball_angle, double ball_distance, double error) {
    // Check if the ball is too close to the goal
    if (ball_distance < /*distance threshold for the small area*/) {
        // Stop the robot from entering the small area
        robot_drive.driveOff();
        return;
    }

    // Check if the ball is in front of the goal
    if (/*condition to check the ball is in front of the goal*/) {
        // Adjust the robot's position based on the ball's angle
        robot_drive.linealMovementError(ball_angle, speed_tester, error);
    }

    // Check if the ball is too far (past the middle line)
    if (ball_distance > /*distance threshold for the middle line*/) {
        // Stop the robot from passing the middle line
        robot_drive.driveOff();
    } 

    // if 
}

void returnToInitialPosition() {
    // For returning to initial position, search goal you are defending an go back 
    // until you are close to the the goal. 
}

void exitLine(int angleLine, double error) {
    unsigned long time = millis();

    while ((millis() - time) < 350) {
        robot_drive.linealMovementError(angleLine, 255, error);
    }
}
