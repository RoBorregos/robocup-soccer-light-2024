#include "Arduino.h"
#include "drive.h"

// pin configuration
const int m1Speed = 4; 
const int m1P1 = 23;
const int m1P2 = 22;
const int m2Speed = 5;
const int m2P1 = 24;
const int m2P2 = 25;
const int m3Speed = 6;
const int m3P1 = 26;
const int m3P2 = 27;

// speed for testing and angle
const int testSpeed = 100;

// initialize drive system
drive robotDrive(m1Speed, m1P1, m1P2, m2Speed, m2P1, m2P2, m3Speed, m3P1, m3P2);
robotDrive.initialize(); 

void setup() { 
  Serial.begin(9600);
}

void loop() {
  robotDrive.linealMovement(60, testSpeed);
    delay(1000);
  robotDrive.linealMovement(180, testSpeed);
    delay(1000);
  robotDrive.linealMovement(300, testSpeed);
    delay(1000);
  robotDrive.driveOff(); 
  delay(1000);
  
}

/*pins for motors: 

M1: 4
in1= 22
in2 = 23

M2: 5
in1= 25
in2 = 24

M3: 6
in1= 27
in2 = 26

*/  