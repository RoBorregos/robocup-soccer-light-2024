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
calibration of values for open mv x, y, width, height
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
Drive robot_drive(4, 23, 22, 5, 25, 24, 6, 26, 27); 
BNO orientation_sensor;  
PID pid(kP, kI, kD);   
IR ring_IR; 
Color color_sensor;  
Goals yellowGoal;  
Goals blueGoal; 

enum States {
    line, 
    lineDetected, 
    hasBall, 
    searchGoal, 
    searchBall
}; 

enum Sides { 
    yellow = 0; 
    blue = 1; 
};

unsigned long current_time = 0;  
Sides attack = yellow; 
States state; 

void setup() { 
    Serial.begin(9600);  
    Serial3.begin(115200); // ARO IR 
    Serial1.begin(9600);  // OPEN MV 
    
    // Initialize Objects
    initializeObjects();  
    
    //Turn the robot if its facing backwards 
    robotTurn(); 
}

void loop() {
    current_time = millis();    

    // Algorithm for Demo 11 April :) 

    // Initial State
    state = line;  

    // Verify if robot is in line  
    if (state == line) {
        state = (inline()) ? lineDetected : searchBall; 
    } 
    
    // Exit White Line
    if (state == lineDetected) {
        exitLine(); 
    } 
    
    // Search Ball
    if (state == searchBall) {
        ring_IR.updateData();    
        searchBallWithDistance(); 
    } 

    // Adjusting to Goal (maybe)
    
    // Algorithm for TMR
   
    // Initial state 
    /*
    state = line; 

    // Verify if robot is in line  
    if (state == line) {
        state = (inline()) ? lineDetected : hasBall; 
    } 

    if (state == lineDetected) {
        exitLine(); 
    }

    // Check if robot has ball  
    if (state == hasBall) {
        ring_IR.updateData();    
        // here the angle of the ball is taken raw, with no modifications
        state = (ballDetector() >= 5 && abs(ring_IR.getAngle() > 15)) ? searchGoal : searchBall;
    }
    
    // Search ball 
    if (state == searchBall) {   
        searchBallWithDistance(); 
    }

    // Go towards goal with ball 
    if (state == searchGoal) {
        approachGoal(); 
    } 

    */
 
}
