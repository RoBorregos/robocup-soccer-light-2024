#include "Color.h"

const int numSensorsP1 = 7;
const int numSensorsP2 = 7;

//pins for the 2 pcbs
int sensorPinsP1[numSensorsP1] = {  };
int sensorPinsP2[numSensorsP2] = {  };

Color ColorP1(numSensorsP1, sensorPinsP1);
Color ColorP2(numSensorsP2, sensorPinsP2);

void setup() {
  Serial.begin(9600);
}

void loop() {
  // calibration for PCB1
  ColorP1.calibrate();

  // check line for PCB1
  if (ColorP1.lineDetected()) {
    int recoveryAngle = ColorP1.getRecoveryAngle();
    Serial.print("PCB1 line detected, recovery angle: ");
    Serial.println(recoveryAngle);
  }

  // check line for PCB2
  ColorP2.calibrate();

  // check line for PCB2
  if (ColorP2.lineDetected()) {
    int recoveryAngle = ColorP2.getRecoveryAngle();
    Serial.print("PCB2 line detected, recovery angle: ");
    Serial.println(recoveryAngle);
  }

}
