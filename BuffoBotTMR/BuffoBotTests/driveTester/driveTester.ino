#include "Arduino.h"

// pin configuration
const int motor_1_PWM = 4;  
const int motor_1_dir1 = 23; 
const int motor_1_dir2 = 22; 

const int motor_2_PWM = 5;  
const int motor_2_dir1 = 25;  
const int motor_2_dir2 = 24;  

const int motor_3_PWM = 6; 
const int motor_3_dir1 = 27;  
const int motor_3_dir2 = 26;  

// speed for testing and angle
const int kSpeed = 150;

void setup() {
  Serial.begin(9600);

  pinMode(motor_1_PWM, OUTPUT);
  pinMode(motor_1_dir1, OUTPUT);
  pinMode(motor_1_dir2, OUTPUT);

  pinMode(motor_2_PWM, OUTPUT);
  pinMode(motor_2_dir1, OUTPUT);
  pinMode(motor_2_dir2, OUTPUT);

  pinMode(motor_3_PWM, OUTPUT);
  pinMode(motor_3_dir1, OUTPUT);
  pinMode(motor_3_dir2, OUTPUT);
  
}

void loop() {
  //tests for motor 1
  digitalWrite(motor_1_dir1, LOW);
  digitalWrite(motor_1_dir2, HIGH);
  analogWrite(motor_1_PWM, kSpeed); 
  //delay(2000); 

  //tests for motor 2
  digitalWrite(motor_2_dir1, LOW);
  digitalWrite(motor_2_dir2, HIGH);
  analogWrite(motor_2_PWM, kSpeed); 
  //delay(2000); 

  //tests for motor 3
  digitalWrite(motor_3_dir1, LOW);
  digitalWrite(motor_3_dir2, HIGH);
  analogWrite(motor_3_PWM, kSpeed); 
  //delay(2000); 

} 

/*pins for motors: 

M1: 4      M2: 5     M3: 6
in1= 23    in1= 24   in1= 26
in2 = 22   in2 = 25  in2 = 27


*/  