/*#include "Color.h"
#include "BNO.h"
#include "Motores.h"

Color colorSensor;
BNO gyro;
Motores motoresRobot(5, 28, 27, 6, 25, 26, 4, 30, 29);

void setup() {
  Serial.begin(9600);
  colorSensor.iniciar();
  colorSensor.calibrar();
  gyro.iniciar();
  motoresRobot.iniciar();
}

void loop() {
  double anguloLinea = colorSensor.checkForLinea();

  if (anguloLinea >= 0) {
    moverEnDireccionContraria(anguloLinea);
  } else {
    motoresRobot.apagarMotores();
  }

  delay(100); 
}
*/

