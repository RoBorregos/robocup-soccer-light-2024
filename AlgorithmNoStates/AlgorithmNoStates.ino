#include "Arduino.h"
#include "BNO.h"
#include "Drive.h" 
#include "PID.h" 
#include "IR.h"
#include "Color.h"
#include "Goals.h"

Drive robot_drive(4, 23, 22, 5, 25, 24, 6, 27, 26); 
BNO orientation_sensor;  
PID pid(3.9, 0.4, 0.09);   
IR ringIR; 
Color colorSensor;
Goals goals; 

int speed_tester = 210;   
unsigned long previous_time = 0;
int lastPosition = 0; 
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
    goals.initiate();
}

void loop() {   
  unsigned long time = millis(); 
  ringIR.updateData();  
  ballDistance = ringIR.getStrength();  
  ballAngle = ringIR.getAngle();  
  colorSensor.calculateDirection();  
  angleLine = colorSensor.getDirection(); 

  if ((time - previous_time) > kFrequency) { 
    // FIRST STATE: EXIT LINE
    if (angleLine != -1) {
      double yaw = orientation_sensor.getYaw();
      double control = pid.calculateError(yaw, 0);
      exitLine(angleLine, control); 

    } else { // SECOND STATE: SEARCH BALL 
      orientation_sensor.readValues();  
    
      ballAngle = (ballAngle < 0 ? 360 + ballAngle : ballAngle);   
      ballAngle = 360 - ballAngle;  
      ballAngle = ringIR.mapAngleWithOffset(ballAngle);  

      if (ballDistance != 0) {   

        double yaw = orientation_sensor.getYaw();
        double control = pid.calculateError(yaw, 0);  
        searchBallWithDistance(ballAngle, ballDistance, speed_tester, control);  

      } else {
        robot_drive.driveOff();  
      } 

      if (ballDistance != 0) {  
        int goalX = getGoalsX(); 
        int goalY = getGoalsY();   

        if ((ballAngle >= 355 && ballAngle <= 360) || (ballAngle >= 0 && ballAngle <= 25)) {
            ballAngle = 0; 
        } 

        if (ballAngle == 0 && goalY > 50) {
          double yaw = orientation_sensor.getYaw();
          double control = pid.calculateError(yaw, 0);
          approachGoal(goalX, speed_tester, control);
        }
      } else {
        robot_drive.driveOff();  
      }
      previous_time = time; 

    }  
  }  
}

int detectedGoals(){
  goals.updateData();  
    int detectedColor = 0;  // Declare color variable outside the loop
    for (uint8_t i = 0; i < goals.getNumGoals(); i++) {
        int color = goals.getColor(i); 
        if (color == 1) {
            //Serial.print("blue"); 
            detectedColor = 1;
        } else if (color == 2) {
           // Serial.print("yellow");
            detectedColor = 2;
        }
    }
    return detectedColor;  // Return the detected color
}

int getGoalsX() {
  goals.updateData();  
  int x = 0;  // Declare x variable outside the loop
  for (uint8_t i = 0; i < goals.getNumGoals(); i++) {
      x = goals.getX(i);  
  }
  return x;  // Return the x coordinate
}

int getGoalsY() {
  goals.updateData();  
  int y = 0;  // Declare x variable outside the loop
  for (uint8_t i = 0; i < goals.getNumGoals(); i++) {
      y = goals.getY(i);  
  }
  return y;  // Return the x coordinate
}

void approachGoal(int x, int speed, double error) {

  if (x > 200) {
        // Goal is to the left 
        robot_drive.linealMovementError(300, speed, error);  
    } else if (x < 120) {
        // Goal is to the right 
        robot_drive.linealMovementError(60, speed, error);   
    } else {
        // Goal is centered 
        robot_drive.linealMovementError(0, speed, error);  
    }
}

void searchBallWithDistance(double ball_angle, double ball_distance, int speed, double error) {
    // First scenario: ball_distance < 50
    if (ball_distance > 50) {
        if ((ball_angle >= 355 && ball_angle <= 360) || (ball_angle >= 0 && ball_angle <= 25)) {
            robot_drive.linealMovementError(0, 220, error);
        } else {
            if (ball_angle > 10 && ball_angle <= 175) {
                ball_angle += 70; // Increase the angle adjustment to 40
            } else if (ball_angle >= 185 && ball_angle < 355) {
                ball_angle -= 70; // Decrease the angle adjustment to 40
            }
            robot_drive.linealMovementError(ball_angle, speed, error);
        }
    }
    else if (ball_distance < 50) {
        if ((ball_angle >= 355 && ball_angle <= 360) || (ball_angle >= 0 && ball_angle <= 25)) {
            robot_drive.linealMovementError(0, 220, error);
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

void exitLine (int angleLine, double error) {
  unsigned long time = millis();

  while ((millis() - time) < 350) {  
    int newAngleLine = colorSensor.getDirection();

    // Check for new line detection within the while loop
    if (newAngleLine != -1) {
       angleLine = newAngleLine;
    }
    robot_drive.linealMovementError(angleLine, 255, error);
  }
} 

/* goals.updateData(); 
        int goalY = getGoalsY();
        // THIRD STATE: APPROACH GOAL
        if ((ballAngle >= 355 && ballAngle <= 360) || (ballAngle >= 0 && ballAngle <= 25) && goalY > 50)  {
          double yaw = orientation_sensor.getYaw();
          double control = pid.calculateError(yaw, 0); 
          int goalX = getGoalsX(); 
          //Serial.print("approach goal");
          approachGoal(goalX, speed_tester, control); */ 

/* goals.updateData(); 
        int goalY = getGoalsY(); 
        if ((ballAngle >= 355 && ballAngle <= 360) || (ballAngle >= 0 && ballAngle <= 25) && goalY > 50)  {
          double yaw = orientation_sensor.getYaw();
          double control = pid.calculateError(yaw, 0); 
          int goalX = getGoalsX(); 
          Serial.print("approach goal");
          approachGoal(goalX, speed_tester, control); 
        } */



