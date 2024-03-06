#include "Arduino.h"
#include "Color.h"
#include "EEPROM.h"

//constructor
Color::Color(int _nSensor, int _pin[]) {
    nSensor = _nSensor;
    angleDiference = 360 / nSensor;

    for (int i = 0; i < nSensor; i++) {
        pin[i] = _pin[i];
        lineOffset[i] = EEPROM.read(i) * 4;
    }
}

bool Color::read_line_sensor(int id) {
    // Set the sensor id in binary
    digitalWrite(kLineSensorS0, id & 1);
    digitalWrite(kLineSensorS1, id & 2);
    digitalWrite(kLineSensorS2, id & 4);
    digitalWrite(kLineSensorS3, id & 8);
    return analogRead(kLineSensorSignal) > kLineSensorThreshold;
}

//calibration
void Color::calibrate() {
    if (digitalRead(calibratePin) && !flag)
        flag = true;

    if (!digitalRead(calibratePin) && flag) {
        ++calibrationState %= 3;
        flag = false;
        clearLineOffset();
    }

    if (calibrationState == 1)
        getLineOffset();

    if (calibrationState == 2)
        saveLineOffset();
}

void Color::clearLineOffset(){
    for(int i=0; i<nSensor; i++) lineOffset[i]= 0;
}
void Color::getLineOffset(){
    for(int i=0; i<nSensor; i++){
        lineOffset[i]= max((read_line_sensor(i)+60), lineOffset[i]);
    }
}
void Color::saveLineOffset(){
    for(int i=0; i<nSensor; i++){
        EEPROM.write(i, (lineOffset[i]/4));
    }
    calibrationState= 0;
}

//line detection
bool Color::lineDetected() {
    if (calibrationState != 0)
        return false;

    sensorsDetected = recoveryAngle = 0;

    for (int i = 0; i < nSensor; i++) {
        if (read_line_sensor(i)) {
            sensorsDetected++;
            recoveryAngle += i * angleDiference;
        }
    }

    if (sensorsDetected)
        return true;

    return false;
}

int Color::calculate_recovery_angle() {
    int angle_sum = 0;
    int sensors_detected = 0;

    for (int i = 0; i < nSensor; i++) {
        if (read_line_sensor(i)) {
            int sensor_angle = i * (360 / nSensor);
            angle_sum += sensor_angle;
            sensors_detected++;
        }
    }

    int average_angle = (sensors_detected > 0) ? angle_sum / sensors_detected : 0;
    return (average_angle + 180) % 360;
}

//recovery angle 
int Color::getRecoveryAngle() {
    return calculate_recovery_angle();
}