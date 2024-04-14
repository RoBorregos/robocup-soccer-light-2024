 #include "Arduino.h"

void setup() {
  Serial.begin(115200); 
  //Serial1.begin(115200); 
  Serial1.begin(115200);  // Start serial communication at 9600 bps
  Serial1.setTimeout(100);  // Set timeout for reading serial data 
}

void loop() {
  if (Serial1.available()) {
    String input = Serial1.readStringUntil('\n'); 
    Serial.println("Received Data: " + input);
  } else {
    Serial.println("No data received"); 
  }
  if (Serial1.available() > 0) {  // Check if data is available to read
    String data = Serial1.readStringUntil('\n');  // Read data until newline character
    Serial.println(data);  // Print received data to serial monitor 
  }   
  delay(100); 
}
