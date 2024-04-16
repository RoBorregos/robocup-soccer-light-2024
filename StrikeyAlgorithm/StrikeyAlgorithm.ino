//Strikey Algorithm Soccer LightWeight Roborregos 2024

//Calibration needed before match 
/*Camera
Line Detection, determine wich searchBall function will be used 
DISTANCE OF BALL!!
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
PID pid(3.9, 0.4, 0.09);   
IR ring_IR; 
Color color_sensor;    
Goals goals; 
unsigned long current_time = 0;  

enum States {
    line, 
    lineDetected, 
    hasBall, 
    noBall,
    searchGoal, 
    searchBall
} state; 

enum GoalColor {
    Blue, 
    Yellow
};  

const GoalColor attack = Yellow;

void setup() { 
    Serial.begin(9600);  
    Serial1.begin(115200); // ARO IR 
    Serial3.begin(9600);  // PIXY
    
    // Initialize Objects
    initializeObjects();  
    
    //Turn the robot if its facing backwards 
    //robotTurn(); 
}

void loop() {
    current_time = millis();  
    color_sensor.calculateDirection();
    int angleLine = color_sensor.getDirection();
    ring_IR.updateData();  
    double ballDistance = ring_IR.getStrength();  
    double ballAngle = ring_IR.getAngle();   
    goals.updateData(); 

    // Algorithm for TMR 
    state = line; 
    if (state == line) {
      state = (angleLine != -1) ? lineDetected : hasBall; 
    } 

    if (state == lineDetected) {
        exitLine(); 
    } 

    if (state == hasBall) {  
        ballAngle = (ballAngle < 0 ? 360 + ballAngle : ballAngle);   
        ballAngle = 360 - ballAngle;  
        ballAngle = ring_IR.mapAngleWithOffset(ballAngle);  
        if ((ballAngle >= 355 && ballAngle <= 360) || (ballAngle >= 0 && ballAngle <= 25)) {
          ballAngle = 0; 
        } 
        state = (ballDistance != 0) ? searchBall : noBall;  
    }   

    if (state == searchBall) {   
        if (ballDistance > 60 && ballAngle == 0) {
            state = searchGoal; 
        } else {
          searchBallWithDistance();   
        }
        /*
        Serial.print("Search Ball"); 
        Serial.print(ballDistance); 
        Serial.print(ballAngle);  */
    }
    
    if (state == noBall) {
      robot_drive.driveOff(); 
    }

    if (state == searchGoal) {
        approachGoal();  
        Serial.print("approach goal");
    }
  
 
}
