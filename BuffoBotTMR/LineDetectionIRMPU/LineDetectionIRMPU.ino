#include "Arduino.h"
#include "Drive.h" 
#include "PID.h" 
#include "IR.h"
#include "Color.h"

#include <Simple_MPU6050.h>
#include <Wire.h>

Drive robot_drive(4, 23, 22, 5, 25, 24, 6, 27, 26);   
PID pid(0.9, 0, 0.09);   
IR ringIR; 
Color colorSensor;

int speed_tester = 100;  // maybe change to 120 
unsigned long previous_time = 0;
int lastPosition = 0; 
int kFrequency = 10; 
double ballDistance = 0; 
double ballAngle = 0;   
int angleLine = 0; 

Simple_MPU6050 mpu;
double offset = 0;

int yaw = 0.0; 

const int numSamples = 10; 
int samples[numSamples]; 
int sampleIndex = 0; 

const float b0 = 0.000395;
const float b1 = 0.000791;
const float b2 = 0.000395;
const float a1 = -1.972186;
const float a2 = 0.972613;


void setup (){ 
    Serial.begin(9600);  
    Serial1.begin(115200);
    unsigned long currentTime = millis();
    robot_drive.initialize();
    ringIR.initiate(&currentTime);
    ringIR.setOffset(0.0); 
    colorSensor.initiate();  

    Wire.begin();
    mpu.begin();
    mpu.Set_DMP_Output_Rate_Hz(10);
    mpu.CalibrateMPU();
    mpu.load_DMP_Image();
    mpu.on_FIFO(gyroValues);
}

void loop() {   
  unsigned long time = millis(); 
  ringIR.updateData();  
  ballDistance = ringIR.getStrength();  
  ballAngle = ringIR.getAngle();  
  colorSensor.calculateDirection();  
  angleLine = colorSensor.getDirection(); 

  if ((time - previous_time) > kFrequency) { 
    actualizeMPU(); 
    // FIRST STATE: EXIT LINE
    if (angleLine != -1) {
      double control = pid.calculateError(yaw, 0);
      exitLine(angleLine, control); 

    } else { // SECOND STATE: SEARCH BALL 
      actualizeMPU();   
    
      ballAngle = (ballAngle < 0 ? 360 + ballAngle : ballAngle);   
      ballAngle = 360 - ballAngle;  
      //ballAngle = ringIR.mapAngleWithOffset(ballAngle);

      Serial.print("\tball distance: "); 
      Serial.println(ballDistance);   

      if (ballDistance != 0) {   
        double control = pid.calculateError(yaw, 0);  
        //this function will be used depending if the distance given by the IR Ring works well
        // THIRD STATE: APPROACH GOAL
        searchBallWithDistance(ballAngle, ballDistance, speed_tester, control); 

      } else {
        Serial.print("no ball detected"); 
        robot_drive.driveOff();  
      }
      previous_time = time; 

    }  
  }  
}

//function of ball_distcance working 
void searchBallWithDistance(double ball_angle, double ball_distance, int speed, double error) {
    // First scenario: ball_distance < 50
    if (ball_distance > 60) {
        if ((ball_angle >= 335 && ball_angle <= 360) || (ball_angle >= 0 && ball_angle <= 5)) {
            robot_drive.linealMovementError(0, 150, error);
        } else {
            if (ball_angle > 5 && ball_angle <= 175) {
                ball_angle += 70; // Increase the angle adjustment to 40
            } else if (ball_angle >= 185 && ball_angle < 335) {
                ball_angle -= 70; // Decrease the angle adjustment to 40
            }
            robot_drive.linealMovementError(ball_angle, speed, error);
        }
    }
    else if (ball_distance < 60) {
        if ((ball_angle >= 335 && ball_angle <= 360) || (ball_angle >= 0 && ball_angle <= 5)) {
            robot_drive.linealMovementError(0, 150, error);
        } else {
            if (ball_angle > 5 && ball_angle <= 175) {
                ball_angle += 25; // Adjust the angle addition to 25
            } else if (ball_angle >= 185 && ball_angle < 335) {
                ball_angle -= 25; // Adjust the angle subtraction to 25
            }
            robot_drive.linealMovementError(ball_angle, speed, error);
        }
    }
} 

void exitLine (int angleLine, double error) {
  unsigned long time = millis();

  while ((millis() - time) < 350) {  
    int newAngleLine = colorSensor.getDirection();

    // Check for new line detection within the while loop
    if (newAngleLine != -1) {
       angleLine = newAngleLine;
    }
    robot_drive.linealMovementError(angleLine, 150, error);
  }
} 



