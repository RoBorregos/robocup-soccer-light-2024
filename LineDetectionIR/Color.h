#ifndef Color_h
  #define Color_h
  
  class Color {
  
    private:
      const int s0 = 32; 
      const int s1 = 33; 
      const int s2 = 34;
      //const int sig = A15; 
 
      int lineSensorThreshold[8] = {700, 700, 700, 300, 600, 400, 400, 600};   
      int sensorAngles[8] = {300, 285, 270, 255, 240, 225, 210, 195};  
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