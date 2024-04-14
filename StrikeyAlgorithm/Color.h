#ifndef Color_h
  #define Color_h
  
  class Color {
  
    private:
      // First PCB (left)
      const int s0_1 = 32; 
      const int s1_1 = 33; 
      const int s2_1 = 34;
      const int muxSignal_1 = A12; 

      // Second PCB (right)
      const int s0_2 = 36; 
      const int s1_2 = 37;   
      const int s2_2 = 38;  
      const int muxSignal_1 = A8; 

      // Pins for sensors front 
      int directPins[4] = {A0, A1, A2, A3};    

      // These arrays need to be changed 
      int lineSensorThreshold[8] = {700, 700, 700, 300, 600, 400, 400, 600};  
      int sensorAngles[8] = {300, 285, 270, 255, 240, 225, 210, 195};  
      int lastDirection = -1; 
    
    public:
  
      Color(); 
      void initiate();
      void selectChannel(int chnl, int mux);  
      void readSensors();  
      void calculateDirection();  
      int getDirection(); 
    
  };

#endif