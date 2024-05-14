// FINAL BELLIBOT MPU 

#include "Drive.h" 
#include "PID.h" 
#include "IR.h"
#include "Color.h"
#include "Goals.h"

#include <Simple_MPU6050.h>
#include <Wire.h>

Drive robot_drive(4, 23, 22, 5, 25, 24, 6, 27, 26);  
PID pid(1.5, 0, 0.09);   
IR ringIR; 
Color colorSensor;
Goals goals; 

int speed_tester = 180;   
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
    //orientation_sensor.initialize(); 
    robot_drive.initialize();
    ringIR.initiate(&currentTime);
    ringIR.setOffset(0.0); 
    colorSensor.initiate();   
    goals.initiate();

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
  goals.updateData();

  if ((time - previous_time) > kFrequency) { 
    // FIRST STATE: EXIT LINE
    /*if (angleLine != -1) { 
      double control = pid.calculateError(yaw, 0);
      exitLine(angleLine, control); 
    } else { // ELSE HERE
      // SECOND STATE: CHECK HOW FAR FROM GOAL YOU ARE, IF FAR GOBACK, IF NEAR 
      */actualizeMPU();  

      if (ballDistance != 0) {    

        double control = pid.calculateError(yaw, 0);  
        ballAngle = (ballAngle < 0 ? 360 + ballAngle : ballAngle);   
        ballAngle = 360 - ballAngle;  
        ballAngle = ringIR.mapAngleWithOffset(ballAngle);
        
        goals.updateData();
        int goalX = getGoalsX();
        int goalY = getGoalsY();
        Serial.print(goalY);

        if (goalY < 0) {
          robot_drive.linealMovementError(180, 180, control); 
          Serial.print("going back");
        } else { 
          searchBall(ballAngle, ballDistance, speed_tester, control);
          Serial.print("searching ball");
        }


      } else { // else of ball distance -1
        Serial.print("no ball detected"); 
        robot_drive.driveOff();  
      }
      
    previous_time = time; 
  }  
}  



int detectedGoals(){
  goals.updateData();  
    int detectedColor = 0;  // Declare color variable outside the loop
    for (uint8_t i = 0; i < goals.getNumGoals(); i++) {
        int color = goals.getColor(i); 
        if (color == 1) {
            //Serial.print("blue"); 
            detectedColor = 1;
        } else if (color == 2) {
           // Serial.print("yellow");
            detectedColor = 2;
        }
    }
    return detectedColor;  // Return the detected color
}

int getGoalsX() {
  goals.updateData();  
  int x = 0;  // Declare x variable outside the loop
  for (uint8_t i = 0; i < goals.getNumGoals(); i++) {
      x = goals.getX(i);  
  }
  return x;  // Return the x coordinate
}

int getGoalsY() {
  goals.updateData();  
  int y = 0;  // Declare x variable outside the loop
  for (uint8_t i = 0; i < goals.getNumGoals(); i++) {
      y = goals.getY(i);  
  }
  return y;  // Return the y coordinate
}

//function of ball_distcance working 
void searchBall(double ball_angle, double ball_distance, int speed, double error) {
  // First scenario: ball_distance < 50
    if (ball_distance > 50) {
        if ((ball_angle >= 350 && ball_angle <= 360) || (ball_angle >= 0 && ball_angle <= 25)) {
            robot_drive.linealMovementError(0, 240, error);
        } else {
            if (ball_angle > 10 && ball_angle <= 175) {
                ball_angle += 70; // Increase the angle adjustment to 40
            } else if (ball_angle >= 185 && ball_angle < 355) {
                ball_angle -= 70; // Decrease the angle adjustment to 40
            }
            robot_drive.linealMovementError(ball_angle, speed, error);
        }
    }
    else if (ball_distance < 50) {
        if ((ball_angle >= 350 && ball_angle <= 360) || (ball_angle >= 0 && ball_angle <= 25)) {
            robot_drive.linealMovementError(0, 220, error);
        } else {
            if (ball_angle > 10 && ball_angle <= 175) {
                ball_angle += 25; // Adjust the angle addition to 25
            } else if (ball_angle >= 185 && ball_angle < 355) {
                ball_angle -= 25; // Adjust the angle subtraction to 25
            }
            robot_drive.linealMovementError(ball_angle, speed, error);
        }
    } 
}


void ballZero(double error) {
  unsigned long time = millis();
  while ((millis() - time) < 400) {  
    robot_drive.linealMovementError(0, 240, error);
  }
}

void exitLine (int angleLine, double error) {
  unsigned long time = millis();

  while ((millis() - time) < 400) {  
    int newAngleLine = colorSensor.getDirection();
    robot_drive.linealMovementError(angleLine, 255, error);
  }
} 

