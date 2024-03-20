// mux pins for pcbA
const int s0 = 32; 
const int s1 = 33; 
const int s2 = 34; 
const int sig = A12; 

void setup() {
  //pinConfiguration
  pinMode(s0, OUTPUT);
  pinMode(s1, OUTPUT);
  pinMode(s2, OUTPUT);
  pinMode(sig, INPUT);

  Serial.begin(9600);
}

void loop() { 
  // iterate through each channel
  for (int channel = 0; channel < 8; ++channel) {
    // set the control pins based on the channel
    digitalWrite(s0, (channel & 0x01) ? 1 : 0);
    digitalWrite(s1, (channel & 0x02) ? 1 : 0);
    digitalWrite(s2, (channel & 0x04) ? 1 : 0);
    
    // read the value of the phototransistor on the selected channel
    int value = analogRead(sig);
    
    // print the value to the serial console 
    Serial.print(value); 
    Serial.print("  ");
  }
  Serial.println();
  delay(50);
}
