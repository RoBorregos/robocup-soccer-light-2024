// lineal movement with PID and BNO orientation

#include "Arduino.h"
#include "BNO.h"
#include "Drive.h" 
#include "PID.h"

Drive robot_drive (6, 26, 27, 5, 24, 25, 4, 23, 22); 
BNO orientation_sensor;  
PID pid(0.7, 0, 0);  
int angle_tester = 60;  
int speed_tester = 80; 

void setup (){ 
    Serial.begin(9600); 
    orientation_sensor.initialize(); 
    robot_drive.initialize(); 
}

void loop() { 
    orientation_sensor.readValues(); 
    double yaw = orientation_sensor.getYaw(); 
    Serial.print("yaw: "); 
    Serial.print(yaw); 

    double control = pid.calculateError(yaw, 0); 
    robot_drive.linealMovementError(angle_tester, speed_tester, control, orientation_sensor.isRight());   
    delay(20);  
  

}