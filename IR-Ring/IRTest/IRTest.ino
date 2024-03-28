 #include "Arduino.h"

void setup() {
  Serial.begin(115200); 
  Serial1.begin(115200); 
}

void loop() {
  if (Serial1.available()) {
    String input = Serial1.readStringUntil('\n'); 
    Serial.println("Received Data: " + input);
  } else {
    Serial.println("No data received"); 
  }
  delay(100); 
}
