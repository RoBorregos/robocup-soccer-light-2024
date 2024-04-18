//tester for one channel in the mux 
//define pins for pcb
const int s0 = 17; 
const int s1 = 18; 
const int s2 = 19; 
const int sig = A8;  

void setup() {

  pinMode(s0, OUTPUT);
  pinMode(s1, OUTPUT);
  pinMode(s2, OUTPUT);
  pinMode(sig, INPUT);
  
  Serial.begin(9600);
}

void loop() {
  // select the channel in binary 
  digitalWrite(s0, HIGH); // s0
  digitalWrite(s1, LOW); // s1
  digitalWrite(s2, LOW); // s2 
  
  //read value in the channel
  int value = analogRead(sig);
 
  Serial.print("value ");
  Serial.println(value); 

  delay(500);
}