/*Movement adjusting based on distance and angle, creating a 
curved approach*/

#include "Arduino.h"
#include "BNO.h"
#include "Drive.h" 
#include "PID.h" 
#include "IR.h"  
#include "Goals.h" 

Drive robot_drive(4, 23, 22, 5, 25, 24, 6, 27, 26); 
BNO orientation_sensor;  
PID pid(3.9, 0, 0.09);   
IR ringIR; 
Goals blueGoal; 
int speed_tester = 210;   
unsigned long previous_time = 0;  
int kFrequency = 50; 
double ballDistance = 0; 
double ballAngle = 0;  

void setup (){ 
    Serial.begin(9600);  
    Serial1.begin(115200); // IR RING 
    unsigned long currentTime = millis();
    orientation_sensor.initialize(); 
    robot_drive.initialize();
    ringIR.initiate(&currentTime);
    ringIR.setOffset(0.0);  
    blueGoal.initiate(); 
}

void loop() {   
  unsigned long time = millis(); 
  ringIR.updateData();  
  blueGoal.updateData();
  ballDistance = ringIR.getStrength();  
  ballAngle = ringIR.getAngle(); 
  int goalY = blueGoal.getY();   
  int goalHeight = blueGoal.getHeight(); 

  if ((time - previous_time) > kFrequency) {
    orientation_sensor.readValues();  
    
    ballAngle = (ballAngle < 0 ? 360 + ballAngle : ballAngle);   
    ballAngle = 360 - ballAngle;  
    ballAngle = ringIR.mapAngleWithOffset(ballAngle);  
    Serial.print(ballAngle);  

    //Serial.print("y= ");   
    //Serial.println(goalY);   

    Serial.print("\tball distance: "); 
    Serial.println(ballDistance);   

    if (ballDistance != 0) {    
        double yaw = orientation_sensor.getYaw();
        double control = pid.calculateError(yaw, 0);   
        //Calculate distance from goal  
        //int distanceGoal = calculateDistanceGoal(goalY, goalX); 
        Serial.print("distance goal: "); 
        Serial.println(goalY); 
        //this function will be used depending if the distance given by the IR Ring works well
        searchBallWithDistance(ballAngle, ballDistance, speed_tester, control, goalY); 
      
    } else {
      Serial.print("no ball detected"); 
      robot_drive.driveOff();  
   }
    previous_time = time; 
  }  
}  

//function of ball_distcance working 
void searchBallWithDistance(double ball_angle, double ball_distance, int speed, double error, int goalDistance) {
    // First scenario: ball_distance > 60 (BALL CLOSE)
    if (ball_distance > 60) {
        if ((ball_angle >= 355 && ball_angle <= 360) || (ball_angle >= 0 && ball_angle <= 25)) { 
            if (goalDistance < 110 ) { 
              robot_drive.linealMovementError(0, 220, error); 
             } else {  //goal is close  
             robot_drive.linealMovementError(180, 180, error); 
         }
        } else {
            if (ball_angle > 10 && ball_angle <= 175) {
                ball_angle += 70; // Increase the angle adjustment to 40
            } else if (ball_angle >= 185 && ball_angle < 355) {
                ball_angle -= 70; // Decrease the angle adjustment to 40
            }
            robot_drive.linealMovementError(ball_angle, speed, error);
        }
    } else if (ball_distance < 60) { // Second scenario: ball distance < 60 (BALL FAR)
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

