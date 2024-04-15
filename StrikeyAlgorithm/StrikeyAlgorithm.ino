//Strikey Algorithm Soccer LightWeight Roborregos 2024

//Calibration needed before match 
/*Camera
Line Detection, determine wich searchBall function will be used
Bno Orientation
IR Ring, angle and distance 
Direction of Motors 
Change color and attacking side 
State = line */ 

/*PENDING CALIBRATIONS OF: 
ballDetector: ir sensor in the front 
ballAngle for checking the posession 
calibration of values for pixy x, y, width, height
*/

//Libs for Robot Functioning 
#include "Arduino.h"
#include "BNO.h"
#include "Drive.h" 
#include "PID.h" 
#include "IR.h"
#include "Color.h"
#include "Goals.h" 
#include "Constants.h"  

//Setup of objects 
Drive robot_drive(4, 23, 22, 5, 25, 24, 6, 27, 26); 
BNO orientation_sensor;  
PID pid(3.9, 0, 0.9);   
IR ring_IR; 
Color color_sensor;  
Goals yellowGoal;  
Goals blueGoal; 
unsigned long current_time = 0;  

enum States {
    line, 
    lineDetected, 
    hasBall, 
    searchGoal, 
    searchBall
} state; 


enum Sides { 
    yellow = 0;  // why do they have values? 
    blue = 1; 
};

Sides attack = yellow; 

void setup() { 
    Serial.begin(9600);  
    Serial1.begin(115200); // ARO IR 
    Serial3.begin(9600);  // PIXY
    
    // Initialize Objects
    initializeObjects();  
    
    //Turn the robot if its facing backwards 
    robotTurn(); 
}

void loop() {
    current_time = millis();   

    // Algorithm for TMR
   
    // Initial state 
    state = line; 

    // Verify if robot is in line  
    if (state == line) {
        state = (inline()) ? lineDetected : hasBall; 
    } 

    if (state == lineDetected) {
        exitLine(); 
    }

    ring_IR.updateData();   
    double ballAngle = ring_IR.getAngle();  
    ballAngle = (ballAngle < 0 ? 360 + ballAngle : ballAngle);   
    ballAngle = 360 - ballAngle;  
    ballAngle = ring_IR.mapAngleWithOffset(ballAngle);   
    
    if ((ballAngle >= 355 && ballAngle <= 360) || (ballAngle >= 0 && ballAngle <= 25)) {
      ballAngle = 0; 
    }
    // Check if robot has ball  
    if (state == hasBall) {  
        // here the angle of the ball is taken raw, with no modifications 
        // here the IR sensor from the front sensor is missing, replace for get strength 
        state = ((ring_IR.getStrength()) > 60 && ballAngle == 0) ? searchGoal : searchBall;
    }
    
    // Search ball 
    if (state == searchBall) {   
        searchBallWithDistance(); 
    }

    // Go towards goal with ball 
    if (state == searchGoal) {
        approachGoal(); 
    } 

 
}
