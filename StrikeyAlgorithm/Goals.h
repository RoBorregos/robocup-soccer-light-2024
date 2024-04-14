#ifndef Goals_h
  #define Goals_h

class Goals {
  private:
    Pixy2 pixy;
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