#ifndef Goals_h
  #define Goals_h  

#include <Pixy2UART.h>

class Goals {
  private:
    Pixy2UART pixy;
    uint16_t x, y, width, height;
    uint8_t color; 

  public:

    Goals(); 
    void initiate(); 
    void updateData(); 
    bool detected(); 
    uint16_t getX();
    uint16_t getY();
    uint16_t getWidth();
    uint16_t getHeight(); 
    uint8_t getColor(); 
};

#endif