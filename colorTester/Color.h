#ifndef Color_h
  #define Color_h
  
  class Color {
  
    private:
      /*
      const int pinLED = 52;
      const int pinBoton = 7; 
      */
      int proportion = 2.5; //BNO
  
      //pines robot
      const int sig[2] = {A12, A8}; 
      const int s0[2] = {32, 17}; 
      const int s1[2] = {33, 18}; 
      const int s2[2] = {34, 19}; 
      
      // CALIBRATION PENDING 
      int foto[2][8] = {{0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0}};
      int fotoMinV[2][8] = {{2, 6, 7, 8, 3, 6, 5, 8}, {0, 1, 1, 3, 4, 0, 3, 8},};
      int fotoMaxV[2][8] = {{4, 8, 9, 10, 5, 8, 8, 10}, {1, 3, 4, 5, 5, 0, 5, 11},};
      int fotoMinB[2][8] = {{27, 50, 43, 35, 32, 41, 43, 47}, {19, 44, 35, 58, 56, 100, 52, 58}};
      int fotoMaxB[2][8] = {{30, 53, 46, 38, 35, 44, 46, 50}, {22, 47, 38, 62, 58, 100, 55, 60}};

      // 
      double angle[2][8] = {{73.1, 85.9, 98.8, 111.6, 124.5, 137.3, 150.2, 163}, {291.6, 278.8, 265.9, 253.1, 240.2, 227.4, 214.5, 201.7}};

    int readLineSensor(int ft, int placa);

  
    public:
      Color(); 
      void initiate();
      void calibrate();
      double recoveryAngle(); 
      int recoveryAngle(); 
  };

#endif
