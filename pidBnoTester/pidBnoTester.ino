//demo with motors, bno and PID 

#include "Arduino.h"
#include "BNO.h" 
#include "drive.h" 
#include "motor.h"

drive robotDrive(4, 23, 22, 5, 24, 25, 6, 26, 27);  

motor motor1;
motor motor2;
motor motor3; 

BNO orientationSensor; 
double ctrl_error = 0;
double previous_error = 0; 
unsigned long previous_time = 0; 
double sum_error = 0;
double kP = 1.2; // proportional gain
double kI = 0; // integral gain
double kD = 0; // derivative gain 
int max_error = 180; 

void setup() {
  Serial.begin(9600);
  orientationSensor.iniciar(); //initialize the orientation sensor 
  robotDrive.initialize();  //initialize the drive 

}

void loop() {
   //get yaw from BNO 
   orientationSensor.readValues();
   double yaw = orientationSensor.getYaw(); 
   Serial.print("Yaw: ");
   Serial.println(yaw);  

   //int change = calculateError(yaw, 0); 
   //robotDrive.linealMovementError(90, 200, change, orientationSensor.isRight());    
   double control = (calculateError(yaw, 0));  
   robotDrive.setAllMotorSpeed(abs(control)); 
   if (control != 0){
    if (yaw > 0) {
      robotDrive.rotateH();
      Serial.print("moving forward");
    } else {
      robotDrive.rotateAH(); 
     Serial.print("moving backward");
    }
  } 
  
  //robotDrive.giro(45, 90);  
  delay(50);


}

double calculateError(int angle, int setPoint) {
  unsigned long time = millis(); 
  unsigned long delta_time = time - previous_time; 
  ctrl_error = setPoint - angle; 
  double delta_error = (ctrl_error - previous_error)/ delta_time;  
  sum_error += ctrl_error * delta_time; 
  //sum_error = (sum_error > max_error) ? max_error : sum_error; 
  double control = (kP * ctrl_error) + (kI * sum_error) + (kD * delta_error);
  //sum_error += ctrl_error; 
  previous_error = ctrl_error;  
  previous_time = time; 
  Serial.print("Error: ");
  Serial.println(control);
  return control; 
}