class Constants {
   public:
       static constexpr int speed = 150;
       static constexpr int minSpeed = 50;
       static constexpr int sensorIR = A4;
       static constexpr double kP = 0.9;
       static constexpr double kI = 0;
       static constexpr double kD = 0.09; 
       unsigned long previous_time = 0;  
       static constexpr int kFrequency = 50; 
       static constexpr double ballDistance = 0; 
       static constexpr double ballAngle = 0; 
};