#ifndef Color_h
  #define Color_h
  
  class Color {
  
    private:
      const int s0 = 36; 
      const int s1 = 37; 
      const int s2 = 38;
      const int sig = A8;  

      int directPins[8] = {A0, A1, A4, A5, A13, A14, A9, A10}; 
 
      int thresholdMux[6] = {500, 100, 500, 100, 500, 500};   
      int thresholdDirect[8] = {700, 700, 700, 40, 200, 250, 250, 210}; 
      int anglesMux[6] = {165, 180, 150, 105, 75, 90};   
      int anglesDirect[8] = {285, 240, 180, 180, 0, 0, 0, 0};   
 
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