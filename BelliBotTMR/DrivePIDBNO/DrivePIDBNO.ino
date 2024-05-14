// lineal movement with PID and BNO orientation

#include "Arduino.h"
#include "BNO.h"
#include "Drive.h" 
#include "PID.h"

Drive robot_drive(4, 23, 22, 5, 25, 24, 6, 27, 26); 
BNO orientation_sensor;  
PID pid(1.2, 0, 0.09);  
int angle_tester = 0;  
int speed_tester = 120; 


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
    //robot_drive.circularMovement(angle_tester, speed_tester, control);   
    robot_drive.linealMovementError(angle_tester, speed_tester, control);    
    delay(50);  
  

} 