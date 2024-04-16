#ifndef Goals_h
#define Goals_h

#include <Pixy2UART.h>

class Goals {
  private:
    Pixy2UART pixy;
    struct GoalData {
        uint16_t x, y, width, height;
        uint8_t color;
    } goals[2];
    uint8_t numGoals;

  public:
    Goals(); 
    void initiate(); 
    void updateData(); 
    bool detected(uint8_t color); 
    uint16_t getX(uint8_t index);
    uint16_t getY(uint8_t index);
    uint16_t getWidth(uint8_t index);
    uint16_t getHeight(uint8_t index); 
    uint8_t getColor(uint8_t index); 
    uint8_t getNumGoals(); 
};

#endif