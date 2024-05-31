#include <Wire.h>
#include <LiquidCrystal.h>

// Configurar los pines para la pantalla LCD
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup() {
  Serial.begin(9600); // Inicializar la comunicación serial
  Wire.begin(8); // Unirse al bus I2C como esclavo con dirección 8
  Wire.onReceive(receiveEvent); // Registrar la función de evento para la recepción de datos

  // Inicializar la LCD con 16 columnas y 2 filas
  lcd.begin(16, 2);
}

void loop() {
  delay(100); // Agregar un pequeño retraso para evitar que el bucle se ejecute demasiado rápido
}