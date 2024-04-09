/*Movement adjusting based on distance and angle, creating a 
curved approach*/

#include "Arduino.h"
#include "BNO.h"
#include "Drive.h" 
#include "PID.h" 
#include "IR.h"

Drive robot_drive(4, 23, 22, 5, 25, 24, 6, 26, 27); 
BNO orientation_sensor;  
PID pid(0.9, 0, 0.09);   
IR ringIR;
int speed_tester = 120;   
unsigned long previous_time = 0;  
int kFrequency = 100; 
double ballDistance = 0; 
double ballAngle = 0;  

// Function to map the angle with offset
double mapAngleWithOffset(double angle) {
    angle += 7; // Add a 20-degree offset
    if (angle >= 360) {
        angle -= 360; // Wrap the angle back to the range of 0-359 degrees
    }
    return angle;
}


void setup (){ 
    Serial.begin(9600);  
    Serial3.begin(115200);
    unsigned long currentTime = millis();
    orientation_sensor.initialize(); 
    robot_drive.initialize();
    ringIR.initiate(&currentTime);
    ringIR.setOffset(0.0); 
}

void loop() {   
  unsigned long time = millis(); 
  ringIR.updateData();  
  ballDistance = ringIR.getStrength();  
  ballAngle = ringIR.getAngle();
  if ((time - previous_time) > kFrequency) {
    orientation_sensor.readValues();  
    
    ballAngle = (ballAngle < 0 ? 360 + ballAngle : ballAngle);   
    ballAngle = 360 - ballAngle;  
    ballAngle = mapAngleWithOffset(ballAngle);

    //Serial.print("ball angle:  "); 
    //Serial.print(ballAngle);
    Serial.print("\tball distance: "); 
    Serial.println(ballDistance);   

    if (ballDistance != 0) { 
      
      Serial.print("yaw: ");  
      double yaw = orientation_sensor.getYaw();
      //Serial.print(yaw); 

      double control = pid.calculateError(yaw, 0); 
      searchBall(ballAngle, ballDistance, speed_tester, control); 

    } else {
      Serial.print("no ball detected"); 
      robot_drive.driveOff();  
    }
      previous_time = time; 
  }  
}  

void searchBall(int ball_angle, int ball_distance, int speed, int error) {
    if ((ball_angle >= 355 && ball_angle <= 360) || (ball_angle >= 0 && ball_angle <= 25 )) {
        robot_drive.linealMovementError(0, 220, error);  
    } else { 
        if (ball_angle > 10 && ball_angle <= 175) {
            ball_angle += 20;      
        } else if (ball_angle >= 185 && ball_angle < 355) {
            ball_angle -= 20;
        }     
        Serial.print("ball angle:  "); 
        Serial.print(ball_angle);
        robot_drive.linealMovementError(ball_angle, speed, error);
    }
} 


