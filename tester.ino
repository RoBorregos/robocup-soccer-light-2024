#include "Arduino.h"
#include "Motores.h"

// definicion pines y velocidades motor
const int motor1SpeedPin = 5;
const int motor1Pin1 = 28;
const int motor1Pin2 = 27;
const int motor2SpeedPin = 6;
const int motor2Pin1 = 25;
const int motor2Pin2 = 26;
const int motor3SpeedPin = 4;
const int motor3Pin1 = 30;
const int motor3Pin2 = 29;

const int velocidadPrueba = 50; 

void setup() {
  Serial.begin(9600);
  
  // Instanciar la clase Motores con los pines y velocidades de los motores
  Motores robotMotores(motor1SpeedPin, motor1Pin1, motor1Pin2,
                       motor2SpeedPin, motor2Pin1, motor2Pin2,
                       motor3SpeedPin, motor3Pin1, motor3Pin2);

  // Iniciar los motores
  robotMotores.iniciar();

  // Realizar pruebas de movimiento
  robotMotores.pruebaMovimiento(velocidadPrueba);

  // Apagar los motores al finalizar las pruebas
  robotMotores.apagarMotores();
}

void loop() {
  
}



