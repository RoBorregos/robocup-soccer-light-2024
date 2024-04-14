// this is for reading pcb with analogs (right) 
// Definimos las constantes para los pines A0 y A1
const int pinFototransistor1 = A13;
const int pinFototransistor2 = A14;
const int pinFototransistor4 = A9;
const int pinFototransistor5 = A10;


void setup() {
  // Inicializamos la comunicación serial a 9600 baudios
  Serial.begin(9600);
}

void loop() {
  // Leemos el valor analógico del fototransistor en el pin A0
  int valorFototransistor1 = analogRead(pinFototransistor1);

  // Leemos el valor analógico del fototransistor en el pin A1
  int valorFototransistor2 = analogRead(pinFototransistor2);

    // Leemos el valor analógico del fototransistor en el pin A0
  int valorFototransistor4 = analogRead(pinFototransistor4);

  // Leemos el valor analógico del fototransistor en el pin A1
  int valorFototransistor5 = analogRead(pinFototransistor5);

  // Enviamos los valores leídos por el puerto serial
  Serial.print("Valor Fototransistor 1: ");
  Serial.println(valorFototransistor1);

  Serial.print("Valor Fototransistor 2: ");
  Serial.println(valorFototransistor2);

    // Enviamos los valores leídos por el puerto serial
  Serial.print("Valor Fototransistor 4: ");
  Serial.println(valorFototransistor4);

  Serial.print("Valor Fototransistor 5: ");
  Serial.println(valorFototransistor5);


  // Esperamos 500 milisegundos antes de repetir el bucle
  delay(500);
}
/*
// this is for reading pvb eith mux (left)
// Constantes y parámetros
#define numero_de_mux 1
#define numPinesMux numero_de_mux * 8
#define enPin 2
#define canalA 36
#define canalB 37
#define canalC 38

// Parámetros
const int pinCom = A8;

void setup() {
  // Inicialización del puerto serie
  Serial.begin(9600);
  Serial.println(F("Inicializando el sistema"));

  // Inicialización del CD4051B
  pinMode(canalA, OUTPUT);
  pinMode(canalB, OUTPUT);
  pinMode(canalC, OUTPUT);
  pinMode(enPin, OUTPUT);
  digitalWrite(canalA, LOW);
  digitalWrite(canalB, LOW);
  digitalWrite(canalC, LOW);
  digitalWrite(enPin, LOW);
}

void loop() {
  MuxFototransistor();
}

void seleccionarCanal(int chnl) {
  // Seleccionar el canal del multiplexor
  int A = bitRead(chnl, 0);
  int B = bitRead(chnl, 1);
  int C = bitRead(chnl, 2);
  digitalWrite(canalA, A);
  digitalWrite(canalB, B);
  digitalWrite(canalC, C);

  //Serial.print(F("Canal ")); Serial.print(chnl); Serial.print(F(" : "));
  //Serial.print(C);
  //Serial.print(F(", "));
  //Serial.print(B);
  //Serial.print(F(", "));
  //Serial.print(A);
  //Serial.println();
}

void MuxFototransistor() {
  // Leer los fototransistores
  int max = 8;
  for (int i = 0; i < max; i++) {
    if(i == 2 || i == 3){}
    else{
      seleccionarCanal(i);
      String nombre = " Valor_" + String(i) + ":";
      int valorAnalogico = analogRead(pinCom); // Leer valor analógico
      //Serial.print(F("Fototransistor ")); Serial.print(i);
      //Serial.print(F(" Valor: ")); 
      Serial.print(nombre + valorAnalogico);
      if(i + 1 != max){
        Serial.print(",");
      }
      delay(50);
    }
  }
  Serial.println();
}
*/
