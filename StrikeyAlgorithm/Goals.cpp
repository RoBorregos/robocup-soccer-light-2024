#include "Arduino.h"
#include "Goals.h" 

Goals::Goals() {

}

void Goals::initiate() {
    pixy.init();
}

void Goals::updateData() {
    pixy.ccc.getBlocks();  
    if (pixy.ccc.numBlocks) {
        x = pixy.ccc.blocks[0].m_x;
        y = pixy.ccc.blocks[0].m_y;
        width = pixy.ccc.blocks[0].m_width;
        height = pixy.ccc.blocks[0].m_height;
        color = pixy.ccc.blocks[0].m_signature;
    }
}

bool Goals::detected() {
    return pixy.ccc.numBlocks > 0;
}

uint16_t Goals::getX() {
    return x;
}

uint16_t Goals::getY() {
    return y;
}

uint16_t Goals::getWidth() {
    return width;
}

uint16_t Goals::getHeight() {
    return height;
}

uint8_t Goals::getColor() {
    return color;
}
