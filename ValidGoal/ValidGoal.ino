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
IR ring_IR; 
Goals blueGoal; 
int speed_tester = 210;   
unsigned long previous_time = 0;  
int kFrequency = 50; 
double ballAngle = 0;   

enum States {
    hasBall, 
    searchGoal, 
    searchBall
} state;    

void setup (){ 
    Serial.begin(9600);  
    Serial1.begin(115200); // IR RING 
    unsigned long currentTime = millis();
    orientation_sensor.initialize(); 
    robot_drive.initialize();
    ring_IR.initiate(&currentTime);
    ring_IR.setOffset(0.0);  
    blueGoal.initiate(); 
}

void loop() {   
  unsigned long time = millis();   

  if ((time - previous_time) > kFrequency){ 
    ring_IR.updateData();   
    ballAngle = ring_IR.getAngle();  
    ballAngle = (ballAngle < 0 ? 360 + ballAngle : ballAngle);   
    ballAngle = 360 - ballAngle;  
    ballAngle = ring_IR.mapAngleWithOffset(ballAngle);   
    
    if ((ballAngle >= 355 && ballAngle <= 360) || (ballAngle >= 0 && ballAngle <= 25)) {
      ballAngle = 0; 
    }
    
    state = hasBall; 

    if (state == hasBall) {
     state = ((ring_IR.getStrength()) > 60 && ballAngle == 0) ? searchGoal : searchBall; 
    } 

    if (state == searchBall) {
     searchBallWithDistance(); 
   } 

    if (state == searchGoal) {
     approachGoal(); 
   }
  }
}
  
