#include "Arduino.h"
#include "Motores.h"

Motores::Motores (int m1Speed, int m1P1, int m1P2, int m2Speed, int m2P1, int m2P2, int m3Speed, int m3P1, int m3P2) {
  motor1.set(m1Speed, m1P1, m1P2);
  motor2.set(m2Speed, m2P1, m2P2);
  motor3.set(m3Speed, m3P1, m3P2);
}

void Motores::iniciar() {
  motor1.iniciarMotor();
  motor2.iniciarMotor();
  motor3.iniciarMotor();
}


void Motores::movimientoLineal(int degree, int velocidad, int error, bool isRight) {
  //En base a los grados se definen las velocidades de cada motor
  float m1 = cos(((150 - degree) * PI / 180));
  float m2 = cos(((30 - degree) * PI / 180));;
  float m3 = cos(((270 - degree) * PI / 180));

  int speedA = (int(m1 * velocidad));
  int speedB = (int(m2 * velocidad));
  int speedC = (int(m3 * velocidad));

  if (isRight) {
    speedA += error;
    speedB += error;
    speedC += error;
  } else {
    speedA -= error;
    speedB -= error;
    speedC -= error;
  }

  int abSpeedA = abs(speedA);
  int abSpeedB = abs(speedB);
  int abSpeedC = abs(speedC);


  int maxSpeed = max(abSpeedA, max(abSpeedB, abSpeedC));

  if (maxSpeed > 100) {
    abSpeedA = map(abSpeedA, 0, maxSpeed, 0, 100);
    abSpeedB = map(abSpeedB, 0, maxSpeed, 0, 100);
    abSpeedC = map(abSpeedC, 0, maxSpeed, 0, 100);
  }


  //Definir la velocidad de cada motor
  analogWrite(motor1.getMotorSpeed(), abSpeedA);
  analogWrite(motor2.getMotorSpeed(), abSpeedB);
  analogWrite(motor3.getMotorSpeed(), abSpeedC);

  //Mover motores según la velocidad (positiva o negativa)
  if (speedA >= 0) {
    motor1.motorAdelante();
  } else {
    motor1.motorAtras();
  }

  if (speedB >= 0) {
    motor2.motorAdelante();
  } else {
    motor2.motorAtras();
  }

  if (speedC >= 0) {
    motor3.motorAdelante();
  } else {
    motor3.motorAtras();
  }

}

void Motores::setAllMotorSpeed(int allSpeed) {
  analogWrite(motor1.getMotorSpeed(), allSpeed);
  analogWrite(motor2.getMotorSpeed(), allSpeed);
  analogWrite(motor3.getMotorSpeed(), allSpeed);
}

void Motores::apagarMotores() {
  motor1.apagar();
  motor2.apagar();
  motor3.apagar();
}

void Motores::adelante() {
  apagarMotores();
  motor1.motorAtras();
  motor2.motorAdelante();
}

void Motores::atras() {
  motor1.motorAdelante();
  motor2.motorAtras();
}

void Motores::giroH() {
  motor1.motorAdelante();
  motor2.motorAdelante();
  motor3.motorAdelante();

}

void Motores::giro(int velocidad, bool right) {
  setAllMotorSpeed(abs(velocidad));
  if (velocidad != 0) {
    if (right) {
      motor1.motorAdelante();
      motor2.motorAdelante();
      motor3.motorAdelante();

    } else {
      motor1.motorAtras();
      motor2.motorAtras();
      motor3.motorAtras();
    }
  } else {
    apagarMotores();
  }

}

//Rotación antihoraria
void Motores::giroAH() {
  motor1.motorAtras();
  motor2.motorAtras();
  motor3.motorAtras();

}

void Motores::pruebaMovimiento(int velocidades) {
  movimientoLineal(0, velocidades);
  delay(1000);

  movimientoLineal(180, velocidades);
  delay(1000);

  movimientoLineal(90, velocidades);
  delay(1000);

  movimientoLineal(-90, velocidades);
  delay(1000);

  movimientoLineal(45, velocidades);
  delay(1000);

  movimientoLineal(-135, velocidades);
  delay(1000);

  movimientoLineal(-45, velocidades);
  delay(1000);

  movimientoLineal(135, velocidades);
  delay(1000);
}

void Motores::mover1() {
  motor1.motorAdelante();
}
void Motores::mover2() {
  motor2.motorAdelante();
}
void Motores::mover3() {
  motor3.motorAdelante();
}