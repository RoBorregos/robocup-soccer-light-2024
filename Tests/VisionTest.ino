void setup() {
  Serial.begin(9600);
  Serial1.begin(9600);  //camera is connected to serial 2
  Serial1.setTimeout(100);  
}

void loop() {
  if (Serial1.available() > 0) {  
    String data = Serial1.readStringUntil('\n');  
    Serial.println(data);  
    
    /
    int pos1 = data.indexOf(',');
    int pos2 = data.indexOf(',', pos1 + 1);
    int pos3 = data.indexOf(',', pos2 + 1);
    int pos4 = data.indexOf(',', pos3 + 1);
    
    String tag = data.substring(0, pos1);
    String x = data.substring(pos1 + 1, pos2);
    String y = data.substring(pos2 + 1, pos3);
    String w = data.substring(pos3 + 1, pos4);
    String h = data.substring(pos4 + 1);
    
    Serial.print("Tag: ");
    Serial.println(tag);
    Serial.print("X: ");
    Serial.println(x);
    Serial.print("Y: ");
    Serial.println(y);
    Serial.print("Width: ");
    Serial.println(w);
    Serial.print("Height: ");
    Serial.println(h);
    
  }
} 