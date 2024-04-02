 #include "Arduino.h"

void setup() {
  Serial.begin(115200); 
  Serial3.begin(115200); 
}

void loop() {
  if (Serial3.available()) {
    String input = Serial3.readStringUntil('\n'); 
    Serial.println("Received Data: " + input);
  } else {
    Serial.println("No data received"); 
  }
  delay(100); 
}
