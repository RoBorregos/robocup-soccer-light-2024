#ifndef Color_h
  #define Color_h
  
  class Color {
  
    private:
      const int s0 = 36; 
      const int s1 = 37; 
      const int s2 = 38;
      const int sig = A8;  

      int directPins[8] = {A0, A1, A4, A5, A13, A14, A9, A10}; 
 
      int thresholdMux[8] = {900, 900, 900, 900, 900, 900, 900, 900};   
      int thresholdDirect[8] = {900, 900, 900, 900, 150, 150, 150, 150}; 
      int anglesMux[8] = {140, 60, 135, 120, 180, 105, 120, 140};   
      int anglesDirect[8] = {300, 300, 180, 180, 0, 0, 0, 0};    
 
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