/*
#include "Color.h"
#include "BNO.h"
#include "Motores.h" 

Color colorSensor;
BNO gyro;
Motores motores(5, 28, 27, 6, 25, 26, 4, 30, 29);

void setup() {
  Serial.begin(9600);
  colorSensor.iniciar();
  colorSensor.calibrar();
  gyro.iniciar();
  motores.iniciar();
}

void loop() {
  double anguloLinea = colorSensor.checkForLinea();

  if (anguloLinea >= 0) {
    int anguloLineaNuevo = (anguloLinea + 180);
    int anguloLineaN = (anguloLineaNuevo%360); 
    motores.movimientoLineal(anguloLineaN, 50);
    Serial.print("angulo linea: ");  
    Serial.print(anguloLinea);  
    Serial.print("angulo a donde se mueve");  
    Serial.println(anguloLineaN);  
    delay(100); 
  } else {
    motores.apagarMotores();
    }
} 

*/
#include "Color.h"

Color colorSensor; 

void setup() {
  Serial.begin(9600);
  colorSensor.iniciar();  
  colorSensor.calibrar(); 
}

void loop() {
  double anguloLinea = colorSensor.checkForLinea();

  if (anguloLinea >= 0) {
    Serial.print("Angulo de la linea detectada: ");
    Serial.println(anguloLinea);
  } else {
    Serial.println("No se detecta la línea blanca.");
  }

  delay(1000);   

} 
