#ifndef motor_h
  #define motor_h
  #pragma once
  
  class motor {
    private:
      int motorSpeed;
      int pin1;
      int pin2;
  
    public:

      motor();
      void set(int motorSpeed, int pin1, int pin2);
      void startMotor();
      void motorFrontward ();
      void motorBackward();
      void stopMotor();
      int getMotorSpeed();
      int getPin1();
      int getPin2();
          
  };

#endif