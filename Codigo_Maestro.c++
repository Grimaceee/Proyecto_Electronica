#include <Wire.h>
#include <Servo.h>

Servo servoDolor;  // Servo para el valor del dolor
Servo servoDosis;  // Servo para el valor de la dosis

int fotoresistorPin = A2;
int tempPotPin = A1;
int dolorPotPin = A3;
int dosisPotPin = A0;
int startButtonPin = 7;

int PULSO = 0;
float tempValue = 0;
int dolorValue = 0;
int dosisValue = 0;
int estado = 0;

//parte 2
void setup() {
  Serial.begin(9600); // Start serial for output
  Wire.begin(); // Join I2C bus as master

  // Inicializar los pines de entrada
  pinMode(fotoresistorPin, INPUT);
  pinMode(tempPotPin, INPUT);
  pinMode(dolorPotPin, INPUT);
  pinMode(dosisPotPin, INPUT);

  // Inicializar el pin del botón como entrada
  pinMode(startButtonPin, INPUT);

  servoDolor.attach(9);  // Conecta el servo del dolor al pin 9
  servoDosis.attach(10); // Conecta el servo de la dosis al pin 10

  // Mostrar mensaje inicial
  enviarDatosEsclavo("MSG0PRESIONA EL BOTON");
}

void loop() {
  while (digitalRead(startButtonPin) == LOW) {
    delay(100);
  }

  enviarDatosEsclavo("MSG0INICIANDO...");
  estado = 1;