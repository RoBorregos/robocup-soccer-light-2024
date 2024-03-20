#include "Arduino.h"
#include "Color.h"


Color::Color() {}; 

//read the sensors in the channels 
int Color::readLineSensor(int ft, int placa) {
  // Iterate through each channel
  for (int channel = 0; channel < 8; ++channel) {
    // Set the control pins based on the channel
    digitalWrite(s0, (channel & 0x01) ? 1 : 0);
    digitalWrite(s1, (channel & 0x02) ? 1 : 0);
    digitalWrite(s2, (channel & 0x04) ? 1 : 0);
    
    // Read the value of the phototransistor on the selected channel
    int valor = analogRead(sig); 
    return valor; 
  }
}

// initiate the pins of the mux
void Color::initiate() {
  for (int i = 0; i < 2; i++) {
    pinMode(s0[i], OUTPUT);
    pinMode(s1[i], OUTPUT);
    pinMode(s2[i], OUTPUT);
  }
  pinMode(sig, INPUT);
}

//calibrate the robot by taking the average green
void Color::calibrate() {

  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 8; j++) {
      int suma = 0;
      for (int k = 0; k < 100; k++) {
        suma += readLineSensor(j, i);
      }
      foto[i][j] = suma / 100;
    }
  }
  Serial.println("calibration ready");

}

//get the degree that the sensor is detecting 
double Color::recoveryAngle() {
  double degree = 0;
  double count = 0;
  bool check = false;
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 8; j++) {
      int lec = readLineSensor(j, i);
      if (lec - foto[i][j] >= 25) {
        if (i == 2 && j == 0 && check == true) {
          return 0;
        }
        else if (i == 0 && j == 7) {
          check = true;
        }
        degree += angle[i][j];
        count++;
      }
    }
  }
  if (count > 1) {
    return degree / count;
  }
  else {
    return -1;
  }
}

//getter recovery angle 
int Color::getRecoveryAngle() {
    return recoveryAngle();
}