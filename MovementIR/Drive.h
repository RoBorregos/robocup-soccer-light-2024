#ifndef Drive_h
  #define Drive_h
    
  #pragma once
  #include "Motor.h"
  #include "Arduino.h"
  
  class Drive {
    public:
      Motor motor_1;
      Motor motor_2;
      Motor motor_3;
  
      Drive (int m1_speed, int m1_p1, int m1_p2, 
             int m2_speed, int m2_p1, int m2_p2, 
             int m3_speed, int m3_p1, int m3_p2);

      void initialize();
      void linealMovement(int degree, int speed);
      void linealMovementError(int degree, int speed, int error); 
      void setAllMotorSpeed(int all_speed);
      void driveOff();
      void driveFrontward();
      void driveBackward();
      void rotateH(); 
      void rotateAH();  
  };

#endif