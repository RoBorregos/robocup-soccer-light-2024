// BuffoBot

// Direct Pins (analogs) 
int directPins[12] = {A6, A7, A11, A12, A0, A1, A4, A5, A13, A14, A9, A10};

// belli 
/*
A6 = 90 
A7 


A0= 300
A1 = 255
A4 = 240
A5 = 180
*/ 

// buffo
 /*A5 = 90 
 A4 = 105 
 A1 = 150 
 A0 = 180 

 A6 = 300 
 A7 
 A11
 A12*/
void setup() {
  Serial.begin(9600);
  for (int i = 0; i < 12; i++) {
      pinMode(directPins[i], INPUT);
  } 
}

void loop() {
  readSensors(); 
} 


void readSensors() { 

  // Read from direct sensors
  for (int i = 0; i < 12; i++) {
    int value = analogRead(directPins[i]);
    Serial.print(value); ; 
    Serial.print(" ");
    }
    delay(50);
    Serial.println(); 
} 

/*// BelliBot 

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
      int value = analogRead(sig);  
      Serial.print(value); 
      Serial.print(" ");
    }
  }

  // Read from direct sensors
  for (int i = 0; i < 8; i++) {
    int value = analogRead(directPins[i]);
    Serial.print(value); ; 
    Serial.print(" ");
    }
    delay(50);
    Serial.println(); 
} */