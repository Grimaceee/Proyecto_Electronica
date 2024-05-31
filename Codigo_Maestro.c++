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
   while (true) {
    // Actualizar los valores de los potenciómetros y los servos
    dolorValue = map(analogRead(dolorPotPin), 0, 1023, 1, 10);
    dosisValue = map(analogRead(dosisPotPin), 0, 1023, 1, 3);
    int posDolor = map(dolorValue, 1, 10, 0, 180); // Mapeo del dolor a posición del servo
    int posDosis = map(dosisValue, 1, 3, 0, 180);  // Mapeo de la dosis a posición del servo
    servoDolor.write(posDolor);
    servoDosis.write(posDosis);

    switch (estado) {
      case 1:
      PULSO = map(analogRead(fotoresistorPin), 0, 1023, 54, 120);
      enviarDatosEsclavo("MSG0PULSO:" + String(PULSO) + " LATIDOS:");
      if (PULSO >= 61 && PULSO <= 89) {
        enviarDatosEsclavo("MSG1NORMALES");
      } else if (PULSO >= 54 && PULSO <= 60) {
        enviarDatosEsclavo("MSG1MUY BAJOS");
      } else if (PULSO >= 90 && PULSO <= 120){
        enviarDatosEsclavo("MSG1ANORMALES");
      }
      delay(3000);
      break;
     case 2:
      tempValue = map(analogRead(tempPotPin), 0, 1010, 361, 380) / 10.0;
      enviarDatosEsclavo("MSG0Temp: " + String(tempValue));
      if (tempValue == 36.1) {
        enviarDatosEsclavo("MSG1Temperatura normal");
      } else if (tempValue == 38.0) {
        enviarDatosEsclavo("MSG1Infeccion");
      } else if (tempValue > 36.1 && tempValue < 38.0) {
        enviarDatosEsclavo("MSG1Fiebre");
      }
      delay(3000);
      break;
    case 3:
        enviarDatosEsclavo("MSG0Dolor: " + String(dolorValue));
        enviarDatosEsclavo("MSG1Dosis: " + String(dosisValue));
        delay(3000);
        break;
    case 4:
        // Lógica para el estado 4: Dolor alto (8-10)
        if (dolorValue >= 8 && dolorValue <= 10) {
          enviarDatosEsclavo("MSG0Dolor: Alto");
          if (dosisValue == 1 || dosisValue == 2) {
            enviarDatosEsclavo("MSG1Dosis: Baja");
          } else if (dosisValue == 3) {
            enviarDatosEsclavo("MSG1Dosis: Adecuada");
          }
          delay(3000);
        } else {
          enviarDatosEsclavo("MSG0Tu dolor no esta");
          enviarDatosEsclavo("MSG1en el rango alto");
          delay(1000);
        }
        break;
    case 5:
      // Lógica para el estado 5: Dolor medio (5-7)
      if (dolorValue >= 5 && dolorValue <= 7) {
        enviarDatosEsclavo("MSG0Dolor: Medio");
        if (dosisValue == 1) {
          enviarDatosEsclavo("MSG1Dosis: Baja");
        } else if (dosisValue == 2) {
          enviarDatosEsclavo("MSG1Dosis: Adecuada");
        } else if (dosisValue == 3) {
          enviarDatosEsclavo("MSG1Dosis: Alta");
        }
        delay(3000);
      } else {
        enviarDatosEsclavo("MSG0Tu dolor no esta");
        enviarDatosEsclavo("MSG1en el rango medio");
        delay(1000);
      }
      break;
    case 6:
      // Lógica para el estado 6: Dolor bajo (1-4)
      if (dolorValue >= 1 && dolorValue <= 4) {
        enviarDatosEsclavo("MSG0Dolor: Bajo");
        if (dosisValue == 1) {
          enviarDatosEsclavo("MSG1Dosis: Adecuada");
        } else if (dosisValue == 2 || dosisValue == 3) {
          enviarDatosEsclavo("MSG1Dosis: Alta");
        }
        delay(3000);
      } else {
        enviarDatosEsclavo("MSG0Tu dolor no esta");
        enviarDatosEsclavo("MSG1en el rango bajo");
        delay(1000);
      }
      break;