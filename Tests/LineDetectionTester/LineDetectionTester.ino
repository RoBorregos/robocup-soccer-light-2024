// PCB pins
const int s0 = 32;
const int s1 = 33;
const int s2 = 34;
const int sig = A15;

void setup() {
  Serial.begin(9600);

  pinMode(s0, OUTPUT);
  pinMode(s1, OUTPUT);
  pinMode(s2, OUTPUT);
  pinMode(sig, INPUT);
  
}

void loop() {
  MuxSensor(); 
}

void selectChannel(int chnl) {
  //select channel for reading   
  int A = bitRead(chnl, 0);
  int B = bitRead(chnl, 1);
  int C = bitRead(chnl, 2);
  digitalWrite(s0, A);
  digitalWrite(s1, B);
  digitalWrite(s2, C);
}

void MuxSensor() { 
  int line_sensor_threshold[8] = {700, 700, 700, 300, 600, 400, 400, 600}; 
  for (int i = 0; i < 8; i++) {
    selectChannel(i);
    int value = analogRead(sig); // Leer valor analógico  
    Serial.print(value);
    Serial.print(value > line_sensor_threshold[i] ? "White" : "Green"); 
    Serial.print(" ");
    //delay(50); 
  }  
  Serial.println();  
  delay(50);
}