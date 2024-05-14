#ifndef Color_h
  #define Color_h
  
  class Color {
  
    private:
      int directPins[12] = {A6, A7, A11, A12, A0, A1, A4, A5, A13, A14, A9, A10}; 
      int thresholdDirect[12] = {900, 900, 900, 100, 900, 900, 900, 900, 150, 150, 150, 150}; 
      int anglesDirect[12] = {300, 255, 240, 180, 180, 105, 120, 90, 0, 0, 0, 0};    
 
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