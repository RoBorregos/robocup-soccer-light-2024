/*#include "Color.h"

Color colorSensor; 

void setup() {
  Serial.begin(9600);
  colorSensor.iniciar();  
  colorSensor.calibrar(); 

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
*/