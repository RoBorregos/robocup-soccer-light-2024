#include "Arduino.h"
#include "Goals.h"

Goals::Goals() {
    numGoals = 0;
}

void Goals::initiate() {
    pixy.init();
}

void Goals::updateData() {
    pixy.ccc.getBlocks();
    numGoals = pixy.ccc.numBlocks > 2 ? 2 : pixy.ccc.numBlocks;
    for (uint8_t i = 0; i < numGoals; i++) {
        goals[i].x = pixy.ccc.blocks[i].m_x;
        goals[i].y = pixy.ccc.blocks[i].m_y;
        goals[i].width = pixy.ccc.blocks[i].m_width;
        goals[i].height = pixy.ccc.blocks[i].m_height;
        goals[i].color = pixy.ccc.blocks[i].m_signature;
    }
}

bool Goals::detected(uint8_t color) {
    for (uint8_t i = 0; i < numGoals; i++) {
        if (goals[i].color == color) {
            return true;
        }
    }
    return false;
}

uint16_t Goals::getX(uint8_t index) {
    return goals[index].x;
}

uint16_t Goals::getY(uint8_t index) {
    return goals[index].y;
}

uint16_t Goals::getWidth(uint8_t index) {
    return goals[index].width;
}

uint16_t Goals::getHeight(uint8_t index) {
    return goals[index].height;
}

uint8_t Goals::getColor(uint8_t index) {
    return goals[index].color;
}

uint8_t Goals::getNumGoals() {
    return numGoals;
}