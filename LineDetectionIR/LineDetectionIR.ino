/*Movement adjusting based on distance and angle, creating a 
curved approach*/

#include "Arduino.h"
#include "BNO.h"
#include "Drive.h" 
#include "PID.h" 
#include "IR.h"
#include "Color.h"

Drive robot_drive(4, 23, 22, 5, 25, 24, 6, 27, 26); 
BNO orientation_sensor;  
PID pid(3.9, 0.4, 0.09);   
IR ringIR; 
Color colorSensor;
int speed_tester = 220;   
unsigned long current_time = 0;  

double ballDistance = 0; 
double ballAngle = 0;  

void setup (){ 
    Serial.begin(9600);  
    Serial1.begin(115200);
    unsigned long currentTime = millis();
    //BNO
    orientation_sensor.initialize(); 
    //MOTORS
    robot_drive.initialize(); 
    //IR RING
    ringIR.initiate(&currentTime);
    ringIR.setOffset(0.0); 
    //COLOR SENSORS 
    colorSensor.initiate();  
}

void loop() {   
  current_time = millis();  
  colorSensor.calculateDirection();
  int angleLine = colorSensor.getDirection();
  ringIR.updateData();  
  ballDistance = ringIR.getStrength();  
  ballAngle = ringIR.getAngle();  

  if (angleLine != -1) {
    exitLine();  
  } else {
    ballAngle = (ballAngle < 0 ? 360 + ballAngle : ballAngle);   
    ballAngle = 360 - ballAngle;  
    ballAngle = ringIR.mapAngleWithOffset(ballAngle);  

    if (ballDistance != 0) { 
      //this function will be used depending if the distance given by the IR Ring works well
      searchBallWithDistance(ballAngle, ballDistance, speed_tester); 
    } else {
      Serial.print("no ball detected"); 
      robot_drive.driveOff();  
    }
  }
  
}   

void exitLine () {
  colorSensor.calculateDirection();  
  int angle_line = colorSensor.getDirection();     
  unsigned long time = millis(); 

  while((millis() - time) < 350) {
      // in calculate error you already take this value orientation_sensor.readValues();  
      orientation_sensor.readValues();
      double yaw = orientation_sensor.getYaw(); 
      double control = pid.calculateError(yaw, 0); 
      robot_drive.linealMovementError(angle_line, 240, control); 
  }
}


//function of ball_distcance working 
void searchBallWithDistance(double ball_angle, double ball_distance, int speed) {
    orientation_sensor.readValues(); 
    double yaw = orientation_sensor.getYaw(); 
    double error = pid.calculateError(yaw, 0);
    // First scenario: ball_distance < 50
    if (ball_distance > 60) {
        if ((ball_angle >= 355 && ball_angle <= 360) || (ball_angle >= 0 && ball_angle <= 25)) {
            robot_drive.linealMovementError(0, 240, error);
        } else {
            if (ball_angle > 10 && ball_angle <= 175) {
                ball_angle += 70; // Increase the angle adjustment to 40
            } else if (ball_angle >= 185 && ball_angle < 355) {
                ball_angle -= 70; // Decrease the angle adjustment to 40
            }
            robot_drive.linealMovementError(ball_angle, speed, error);
        }
    }
    else if (ball_distance < 60) {
        if ((ball_angle >= 355 && ball_angle <= 360) || (ball_angle >= 0 && ball_angle <= 25)) {
            robot_drive.linealMovementError(0, 240, error);
        } else {
            if (ball_angle > 10 && ball_angle <= 175) {
                ball_angle += 25; // Adjust the angle addition to 25
            } else if (ball_angle >= 185 && ball_angle < 355) {
                ball_angle -= 25; // Adjust the angle subtraction to 25
            }
            robot_drive.linealMovementError(ball_angle, speed, error);
        }
    }
}


//function of ball_distance not working
void searchBall(int ball_angle, int ball_distance, int speed, int error) {
    if ((ball_angle >= 355 && ball_angle <= 360) || (ball_angle >= 0 && ball_angle <= 25 )) {
        robot_drive.linealMovementError(0, 240, error);  
    } else { 
        if (ball_angle > 10 && ball_angle <= 175) {
            ball_angle += 25;      
        } else if (ball_angle >= 185 && ball_angle < 355) {
            ball_angle -= 25;
        }     
        Serial.print("ball angle:  "); 
        Serial.print(ball_angle);
        robot_drive.linealMovementError(ball_angle, speed, error);
    }
}