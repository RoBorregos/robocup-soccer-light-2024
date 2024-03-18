#ifndef drive_h
  #define drive_h
    
  #pragma once
  #include "motor.h"
  #include "Arduino.h"
  
  class drive {
    public:
      motor motor1;
      motor motor2;
      motor motor3;
  
      drive (int m1Speed, int m1P1, int m1P2, int m2Speed, int m2P1, int m2P2, int m3Speed, int m3P1, int m3P2);
      void initialize();
      void linealMovement(int degree, int velocidad);
      void setAllMotorSpeed(int allSpeed);
      void driveOff();
      void driveFrontward();
      void driveBackward();
      void movementTester(int velocidades);
      void move1();
      void move2();
      void move3();
  
  };

#endif