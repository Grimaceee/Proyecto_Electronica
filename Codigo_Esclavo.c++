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

void receiveEvent(int howMany) {
  char buffer[32];
  int i = 0;

  // Leer datos del bus I2C
  while (Wire.available()) {
    char c = Wire.read(); // Leer un carácter
    buffer[i++] = c;
  }

  buffer[i] = '\0'; // Terminar la cadena con un carácter nulo

  // Dividir el mensaje en línea y contenido
  if (strncmp(buffer, "MSG0", 4) == 0) {
    lcd.clear(); // Limpiar la pantalla LCD
    lcd.setCursor(0, 0); // Establecer el cursor en la primera línea
    lcd.print(buffer + 4); // Imprimir el contenido del mensaje en la primera línea
  } else if (strncmp(buffer, "MSG1", 4) == 0) {
    lcd.setCursor(0, 1); // Establecer el cursor en la segunda línea
    lcd.print(buffer + 4); // Imprimir el contenido del mensaje en la segunda línea
  }
}

