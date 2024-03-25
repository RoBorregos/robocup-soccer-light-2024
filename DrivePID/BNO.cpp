#include "Arduino.h"
#include "BNO.h"

BNO::BNO() {
}

void BNO::initialize() {
  if (!bno.begin(OPERATION_MODE_IMUPLUS)) {
    /* There was a problem detecting the BNO055 ... check your connections */
    Serial.print("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!");
    while (1);
  }
  bno.setExtCrystalUse(true);
}

void BNO::readValues() {
  
  sensors_event_t orientationData;
  bno.getEvent(&orientationData, Adafruit_BNO055::VECTOR_EULER);
  yaw = (double)orientationData.orientation.x;
  // convert yaw angle to range -180 to 180
  yaw = (yaw > 0) ? (360 - yaw) : yaw;
  yaw = (yaw > 180) ? (yaw - 360) : yaw;

  if (offset > 0) {
    yaw = (yaw > 0) ? (-180 + yaw) : (180 + yaw);
  }
  // determine the direction 
  right = (yaw >= 0) ? false : true;
}


void BNO::displayCalStatus()
{
  /* Get the four calibration values (0..3) */
  /* Any sensor data reporting 0 should be ignored, */
  /* 3 means 'fully calibrated" */
  uint8_t system, gyro, accel, mag;
  system = gyro = accel = mag = 0;
  bno.getCalibration(&system, &gyro, &accel, &mag);

  /* The data should be ignored until the system calibration is > 0 */
   Serial.print("\t");

  /* Display the individual values */
  Serial.print("Sys:");
  Serial.print(system, DEC);
  Serial.print(" G:");
  Serial.print(gyro, DEC);
  Serial.print(" A:");
  Serial.print(accel, DEC);
  Serial.print(" M:");
  Serial.println(mag, DEC);
}


double BNO::getYaw() {
  return yaw;
}

double BNO::getMag() {
  return mag;
}

void BNO::setOffset(double off) {
  offset = off;
}

bool BNO::isRight() {
  return right;
}