// PINS SENSORS 

// Left Pins (mux) 
const int s0 = 36; 
const int s1 = 37; 
const int s2 = 38;
const int sig = A8; 

// Direct Pins (analogs) 
int directPins[8] = {A0, A1, A4, A5, A13, A14, A9, A10};  


void setup() {
  Serial.begin(9600);   
  pinMode(s0, OUTPUT);
  pinMode(s1, OUTPUT);
  pinMode(s2, OUTPUT);
  pinMode(sig, INPUT);

  for (int i = 0; i < 8; i++) {
      pinMode(directPins[i], INPUT);
  } 
}

void loop() {
  readSensors(); 
} 

void selectChannel(int chnl) {
  int A = bitRead(chnl, 0);
  int B = bitRead(chnl, 1);
  int C = bitRead(chnl, 2);
  digitalWrite(s0, A);
  digitalWrite(s1, B);
  digitalWrite(s2, C); 
}

void readSensors() { 
    // Read from mux
    for (int i = 0; i < 8; i++) {
       if(i == 2 || i == 3){}
    else {
      selectChannel(i);
      int value = analogRead(sig); // Leer valor analógico 
      Serial.print(value); 
      Serial.print(" ");
    }
  }

  // Read from direct sensors
  for (int i = 0; i < 8; i++) {
    int value = analogRead(directPins[i]);
    Serial.print(value); 
    //Serial.print(value > lineSensorThreshold[16 + i] ? "White" : "Green"); 
    Serial.print(" ");
    }
    delay(50);
    Serial.println(); 
} 
