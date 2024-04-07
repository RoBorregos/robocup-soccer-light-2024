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
int kFrequency = 51; 
double ballDistance = 0; 
double ballAngle = 0; 

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

    Serial.print("ball angle:  "); 
    Serial.print(ballAngle);
    Serial.print("\tball distance: "); 
    Serial.println(ballDistance);   

    if (ballDistance != 0) { 
      
      Serial.print("yaw: ");  
      double yaw = orientation_sensor.getYaw();
      Serial.print(yaw); 

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
    /*if (ball_distance < 65) {
        robot_drive.linealMovementError(ball_angle, speed, error);  
        Serial.print("ball far");
    } else {
        robot_drive.circularMovement(ball_angle, speed, error);  
        Serial.print("ball close"); 
    } */
    robot_drive.linealMovementError(ball_angle, speed, error);  
} 


