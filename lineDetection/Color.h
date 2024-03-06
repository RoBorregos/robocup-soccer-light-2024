#ifndef Color_h
  #define Color_h

#include "Arduino.h"
#include "EEPROM.h"

#define MAX 60

class Color {
public:
    Color(int _nSensor, int _pin[]);
    void calibrate();
    void clearLineOffset();
    void getLineOffset();
    void saveLineOffset();
    bool lineDetected();
    int getRecoveryAngle();

private:
    int nSensor;
    int pin[MAX];
    int angleDiference;
    int lineOffset[MAX];

    int calibratePin = 20;
    bool flag = false;
    int calibrationState = 0;

    int sensorsDetected = 0;
    int recoveryAngle = 0;

    //line sensor parameters
    const int kLineSensorS0 = 1;
    const int kLineSensorS1 = 2;
    const int kLineSensorS2 = 4;
    const int kLineSensorS3 = 8;
    const int kLineSensorSignal = 20;
    const int kLineSensorThreshold = 150;

    bool read_line_sensor(int id);
    int calculate_recovery_angle();
};

#endif
