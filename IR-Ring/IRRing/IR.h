#ifndef IR_h
#define IR_h 
#include "Arduino.h"

class IR {
    private: 
    double angle = 1.0; 
    double strength = 1.0;  
    double offset = 0.0;
    unsigned long* current_time;
    unsigned long last_time = 0; 

    public: 
    IR(); 
    void initiate(unsigned long* current_time); 
    void updateData(); 
    void setOffset(double off_set);
    double getAngle(); 
    double getStrength();  
};

#endif