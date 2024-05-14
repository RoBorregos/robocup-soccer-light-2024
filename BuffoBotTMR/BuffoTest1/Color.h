#ifndef Color_h
  #define Color_h
  
  class Color {
  
    private:
      int directPins[12] = {A6, A7, A11, A12, A0, A1, A4, A5, A13, A14, A9, A10}; 
      int thresholdDirect[12] = {250, 900, 200, 350, 900, 900, 200, 900, 150, 150, 150, 100};  
      //int thresholdYellow[12] = {250, 900, 200, 350, 900, 900, 200, 900, 150, 150, 150, 150};  
      int anglesDirect[12] = {300, 255, 240, 180, 180, 120, 105, 90, 0, 0, 0, 0};   
 
      int lastDirection = -1; 
    
    public:
  
      Color(); 
      void initiate();
      void selectChannel(int chnl);  
      void muxSensor();  
      void calculateDirection();  
      int getDirection(); 
    
  };
#endif

/* FRONT: 
GREEN: 75, 80, 80, 38
BLACK : 50, 63, 55, 38 ignorar ultimo
YELLOW: 200, 200, 180, 80  

LATERAL: 
GREEN: 75, 80, 80, 38
BLACK : 50, 63, 55, 38 ignorar ultimo
YELLOW: 200, 200, 180, 80  

*/ 
