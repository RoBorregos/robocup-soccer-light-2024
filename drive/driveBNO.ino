#include "Arduino.h"
#include "BNO.h" 
#include "drive.h"

const int m1Speed = 4; 
const int m1P1 = 23;
const int m1P2 = 22;
const int m2Speed = 5;
const int m2P1 = 24;
const int m2P2 = 25;
const int m3Speed = 6;
const int m3P1 = 26;
const int m3P2 = 27;
const int testSpeed = 100;
drive robotDrive(m1Speed, m1P1, m1P2, m2Speed, m2P1, m2P2, m3Speed, m3P1, m3P2); 

BNO orientationSensor; // Create an instance of the BNO class

void setup() {
  Serial.begin(9600);
  orientationSensor.iniciar(); // Initialize the orientation sensor 
  robotDrive.initialize();  
}

void loop() {
  orientationSensor.readValues(); // Read orientation values

  double yaw = orientationSensor.getYaw(); // Get yaw angle
  double mag = orientationSensor.getMag(); // Get magnetometer data
  bool right = orientationSensor.isRight(); // Check if yaw angle is to the right

  // Display orientation data
  Serial.print("Yaw: ");
  Serial.println(yaw);
  Serial.print("Magnetometer: ");
  Serial.println(mag);
  Serial.print("Right: ");
  Serial.println(right ? "Yes" : "No");

  // Display calibration status
  Serial.println("Calibration Status:");
  orientationSensor.displayCalStatus();  

  robotDrive.giro(testSpeed, yaw);

  delay(1000); // Delay for stability
}
