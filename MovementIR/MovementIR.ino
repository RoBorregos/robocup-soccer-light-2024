/*Movement adjusting based on distance and angle, creating a 
curved approach*/

#include "Arduino.h"
#include "BNO.h"
#include "Drive.h" 
#include "PID.h" 
#include "IR.h"

Drive robot_drive(6, 27, 26, 5, 25, 24, 4, 22, 23); 
BNO orientation_sensor;  
PID pid(0.9, 0, 0.09);   
IR ringIR;
//int angle_tester = 0;  
int speed_tester = 60;   
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
    //ringIR.updateData(); 

    //double ballAngle = ringIR.getAngle(); // change to int? 
    ballAngle = (ballAngle < 0 ? 360 + ballAngle : ballAngle);   
    ballAngle = 360 - ballAngle; 
    //double ballDistance = ringIR.getStrength(); 

    Serial.print("ball angle:  "); 
    Serial.print(ballAngle);
    Serial.print("\tball distance: "); 
    Serial.println(ballDistance);   

    if (ballDistance != 0) { 
      //function calculate targetAngle  
      double targetAngle = ringIR.calculateMovAngle(ballAngle, ballDistance); 
      Serial.print("Angle where the robot should moving: "); 
      Serial.println(targetAngle);  
      Serial.println("--------------");  
      //delay(100); 
      
      Serial.print("yaw: ");  
      double yaw = orientation_sensor.getYaw();
      Serial.print(yaw); 

      double control = pid.calculateError(yaw, 0); 
      robot_drive.linealMovementError(targetAngle, speed_tester, control);      
      

    } else {
      Serial.print("no ball detected"); 
      robot_drive.driveOff();  
    }
      previous_time = time; 
  }  

} 

