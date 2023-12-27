#include "AroIR.h"
#include "Motores.h"
#include "PID.h"
#include "SingleEMAFilterLib.h"
#include "BNO.h"
#include "Constantes.h"

#include <Servo.h>
Servo esc;


Motores motoresRobot(5, 28, 27, 6, 25, 26, 4, 30, 29);  
BNO gyro;
AroIR aroIR;
PID pid;

unsigned long current_time = 0;

// setup
void setup() {
  Serial.begin(115200);
  Serial.setTimeout(100);
  pid.setKP(Constantes::kP);
  pid.setMinToMove(60);
  gyro.iniciar();
  aroIR.iniciar(&current_time);
  aroIR.setOffset(0.0); 
  motoresRobot.iniciar();
  gyro.readValues();
}

// loop
void loop() {
  // valores del IR
  aroIR.actualizarDatos(); // actualiza los datos del aro IR
  double angulo = aroIR.getAngulo();
  double str = aroIR.getStrength(); 

  // uso del bno
  current_time = millis();
  gyro.readValues();
  double change = pid.calcularError(0, gyro.getYaw(), Constantes::velocidades);
  
  int result = -1000;

  //condicionales del movimiento
  if (str < 40 && abs(angulo) <= 90) {
        result = angulo;
    } else {

    if (abs(angulo <= 100 && abs(angulo) >= 80 && str < 65))
      result = (angulo > 0) ? 45 : -45;
    else if (abs(angulo) <= 30) {
      result = 0;
    } else if (abs(angulo) <= 50) {
      result = (angulo > 0) ? 90 : -90;
    } else if (abs(angulo) <= 75) {
      result = (angulo > 0) ? 120 : -120;
    } else if (abs(angulo) <= 90) {
      result = (angulo > 0) ? 135 : -135;
    } else if (abs(angulo) <= 140) {
      result = 180;
    } else {
      result = (angulo > 0) ? -140 : 140;
    }

    if (str < 30) {
    if (abs(result) <= 135)
      result = result * 0.7;
 
  } else if (str < 50) {
    if (abs(result) <= 135)
      result = result * 0.8;
    
  } 


    } 

  //Regular velocidad
  double distancia = str*0.1;
  double val = 1.087 + 1/((distancia-11.5));
  int velNuevas = Constantes::velocidades * val;
  velNuevas = max(Constantes::velMin, velNuevas);
  
  // Verificar y mover motores
  if (result == -1000) 
    motoresRobot.apagarMotores();
  else 
    motoresRobot.movimientoLineal(result - gyro.getYaw(), velNuevas, change, gyro.isRight());
}