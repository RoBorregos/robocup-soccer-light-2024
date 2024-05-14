// lineal movement with PID and BNO orientation

#include "Arduino.h"
//#include "BNO.h"
#include "Drive.h" 
#include "PID.h" 

#include <Simple_MPU6050.h>
#include <Wire.h>

Drive robot_drive(4, 23, 22, 5, 25, 24, 6, 27, 26); 
//BNO orientation_sensor;  
PID pid(1.5, 0, 0.09);  
int angle_tester = 90;  
int speed_tester = 200; 


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
    //orientation_sensor.initialize(); 
    robot_drive.initialize(); 
    Wire.begin();
    mpu.begin();
    mpu.Set_DMP_Output_Rate_Hz(10);
    mpu.CalibrateMPU();
    mpu.load_DMP_Image();
    mpu.on_FIFO(gyroValues);
}


void loop() { 
    actualizeMPU();
    Serial.print("yaw: ");
    Serial.print(yaw);
    double control = pid.calculateError(yaw, 0);  
    robot_drive.linealMovementError(angle_tester, speed_tester, control);    
    delay(50);  

}

