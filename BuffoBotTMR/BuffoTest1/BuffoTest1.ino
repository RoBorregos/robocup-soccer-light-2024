// FINAL BUFFO BOT 

#include "BNO.h"
#include "Arduino.h"
#include "Drive.h" 
#include "PID.h" 
#include "IR.h"
#include "Color.h"


Drive robot_drive(4, 23, 22, 5, 25, 24, 6, 27, 26);   
PID pid(0.9, 0, 0.09);   
IR ringIR; 
BNO orientation_sensor; 
Color colorSensor;

int speed_tester = 100;  // maybe change to 120 
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
    robot_drive.initialize();
    ringIR.initiate(&currentTime);
    ringIR.setOffset(0.0); 
    colorSensor.initiate();  
    orientation_sensor.initialize(); 
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
      //double control = pid.calculateError(yaw, 0); 
      Serial.print("exiting line"); 
      Serial.print(angleLine); 
      exitLine(angleLine); 
    } else { // SECOND STATE: SEARCH BALL 
      orientation_sensor.readValues();
    
      ballAngle = (ballAngle < 0 ? 360 + ballAngle : ballAngle);   
      ballAngle = 360 - ballAngle;  
      //ballAngle = ringIR.mapAngleWithOffset(ballAngle);

      Serial.print("\tball distance: "); 
      Serial.println(ballDistance);   

      if (ballDistance != 0) {   
        double yaw = orientation_sensor.getYaw();
        double control = pid.calculateError(yaw, 0);  
        //this function will be used depending if the distance given by the IR Ring works well
        // THIRD STATE: APPROACH GOAL
        searchBallWithDistance(ballAngle, ballDistance, speed_tester, control);  
        Serial.print("searching ball"); 

      } else {
        Serial.print("no ball detected"); 
        robot_drive.driveOff();  
      }
      previous_time = time; 

    }  
  }  
}

//function of ball_distcance working 
void searchBallWithDistance(double ball_angle, double ball_distance, int speed, double error) {
    // First scenario: ball_distance < 50
    if (ball_distance > 50) {
        if ((ball_angle >= 330 && ball_angle <= 360) || (ball_angle >= 0 && ball_angle <= 5)) {
            robot_drive.linealMovementError(0, 130, error);
        } else {
            if (ball_angle > 5 && ball_angle <= 175) {
                ball_angle += 5; // Increase the angle adjustment to 40
            } else if (ball_angle >= 185 && ball_angle < 330) {
                ball_angle -= 5; // Decrease the angle adjustment to 40
            }
            robot_drive.linealMovementError(ball_angle, speed, error);
        }
    }
    else if (ball_distance < 50) {
        if ((ball_angle >= 330 && ball_angle <= 360) || (ball_angle >= 0 && ball_angle <= 5)) {
            robot_drive.linealMovementError(0, 130, error);
        } else {
            if (ball_angle > 5 && ball_angle <= 175) {
                ball_angle += 5; // Adjust the angle addition to 25
            } else if (ball_angle >= 185 && ball_angle < 330) {
                ball_angle -= 5; // Adjust the angle subtraction to 25
            }
            robot_drive.linealMovementError(ball_angle, speed, error);
        }
    }
} 

void exitLine (int angleLine) {
  unsigned long time = millis();

  while ((millis() - time) < 400) {  
    //int newAngleLine = colorSensor.getDirection();
    orientation_sensor.readValues();
    double yaw = orientation_sensor.getYaw();
    double error = pid.calculateError(yaw, 0);

    // Check for new line detection within the while loop
    /*if (newAngleLine != -1) {
       angleLine = newAngleLine;
    }*/
    robot_drive.linealMovementError(angleLine, 100, error);
  }
} 

//(ball_angle >= 340 && ball_angle <= 360) || (ball_angle >= 0 && ball_angle <= 10)


