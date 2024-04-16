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
int speed_tester = 210;    
unsigned long current_time = 0;  

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

  if (angleLine != -1) {
    Serial.println("line");
    exitLine();  
  } else {
    Serial.println("no line");
    robot_drive.driveOff();
  }
  
}  
void exitLine () {
  colorSensor.calculateDirection();  
  int angle_line = colorSensor.getDirection();     
  unsigned long time = millis(); 

  while((millis() - time) < 150) {
      // in calculate error you already take this value orientation_sensor.readValues();  
      orientation_sensor.readValues();
      double yaw = orientation_sensor.getYaw(); 
      double control = pid.calculateError(yaw, 0); 
      robot_drive.linealMovementError(angle_line, 240, control); 
  }
}


