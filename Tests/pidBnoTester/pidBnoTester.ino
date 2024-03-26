//control robot orientation using BNO and PID 
#include "Arduino.h"
#include "BNO.h"
#include "Drive.h"
#include "Motor.h"

Drive robot_drive(4, 23, 22, 5, 24, 25, 6, 26, 27);

Motor motor_1;
Motor motor_2;
Motor motor_3;

BNO orientation_sensor;
double control_error = 0;
double previous_error = 0;
unsigned long previous_time = 0;
double sum_error = 0;
double kP = 0.9;  // proportional gain
double kI = 0.7;  // integral gain
double kD = 0;    // derivative gain
int max_error = 180;

void setup() {
  Serial.begin(9600); 
  //initialize bno and motors
  orientation_sensor.initialize();  
  robot_drive.initialize(); 
}

void loop() {
  // get yaw from BNO
  orientation_sensor.readValues();
  double yaw = orientation_sensor.getYaw();
  Serial.print("yaw: ");
  Serial.println(yaw);

  // get error
  double control = calculateError(yaw, 0);
  
  // give error (PWM) to the motors
  robot_drive.setAllMotorSpeed(abs(control));
  
  if (control != 0) {
    // rotate the angle depending on the yaw
    if (yaw > 0) {
      robot_drive.rotateH();
      Serial.print("moving forward");
    } else {
      robot_drive.rotateAH();
      Serial.print("moving backward");
    }
  }
  
  delay(50);
}

// function for calculating the error based on the current angle
double calculateError(int angle, int set_point) {
  // get current time in milliseconds
  unsigned long time = millis(); 
  
  // time difference since last calculation
  double delta_time = (time - previous_time)/1000;
  
  control_error = set_point - angle;
  double delta_error = (control_error - previous_error) / delta_time;
  sum_error += control_error * delta_time;
  
  // Calculate the control signal using PID
  double control = (kP * control_error) + (kI * sum_error) + (kD * delta_error);
  
  // Update previous error and time
  previous_error = control_error;
  previous_time = time;
  
  Serial.print("Error: ");
  Serial.println(control);
  
  return control;
}
