#include <Adafruit_BNO055.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
#include "Arduino.h"

// initialize BNO sensor
Adafruit_BNO055 bno = Adafruit_BNO055(55, 0x28, &Wire);
unsigned long previous_millis = 0;  
const long interval = 100;       

void setup() {
  Serial.begin(9600);

  // check if BNO055 is detected
  if (!bno.begin()) {
    Serial.print("No BNO055 detected");
    while (1); 
  }
  delay(100);

  // use external crystal for better accuracy
  bno.setExtCrystalUse(true);
}

void loop() {
  unsigned long current_millis = millis();  

  // check if it's time to read the sensor data
  if (current_millis - previous_millis >= interval) {
    previous_millis = current_millis; 

    sensors_event_t event;
    bno.getEvent(&event);  // get sensor event data

    // print orientation data
    Serial.print("Orientation: ");
    Serial.print(event.orientation.x);
    Serial.print(",");
    Serial.print(event.orientation.y);
    Serial.print(",");
    Serial.println(event.orientation.z);

    double yaw = event.orientation.x;

    // adjust yaw value if it's positive
    yaw = (yaw > 0) ? (360 - yaw) : yaw;
    Serial.print("Yaw: ");
    Serial.println(yaw);
  }
}