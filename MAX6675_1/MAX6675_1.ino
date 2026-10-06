/*
 * MAX6675_1
 * ---------
 * Lee la temperatura desde un termopar tipo K usando el modulo MAX6675
 * y la muestra en el Monitor Serial en grados Celsius.
 *
 * Libreria necesaria (instalar desde el Gestor de Librerias del IDE):
 *   "MAX6675 library" by Adafruit
 *   (Tools -> Manage Libraries... -> buscar "MAX6675")
 *
 * Conexiones MAX6675 -> ESP32:
 *   VCC -> 3V3 (tambien funciona con 5V)
 *   GND -> GND
 *   SCK -> GPIO 18   (reloj SPI)
 *   CS  -> GPIO 5    (seleccion de chip)
 *   SO  -> GPIO 19   (salida de datos / MISO)
 *
 * Nota: el MAX6675 necesita ~220 ms entre lecturas. No leas mas rapido.
 */

#include "max6675.h"

// Pines de conexion al modulo
const int PIN_SCK = 18;   // Reloj
const int PIN_CS  = 5;    // Chip Select
const int PIN_SO  = 19;   // Salida de datos (MISO)

// Crea el objeto del sensor con los pines definidos
MAX6675 termopar(PIN_SCK, PIN_CS, PIN_SO);

void setup() {
  Serial.begin(115200);
  Serial.println("Sensor de temperatura MAX6675");
  Serial.println("-----------------------------");
  delay(500);   // Espera a que el modulo se estabilice
}

void loop() {
  // Lee la temperatura en grados Celsius
  float tempC = termopar.readCelsius();

  // Si el termopar esta desconectado, readCelsius() devuelve NAN
  if (isnan(tempC)) {
    Serial.println("Error: termopar desconectado o sin lectura.");
  } else {
    // Formato compatible con el Serial Plotter:
    // "Etiqueta:valor" y un salto de linea al final.
    // Solo Celsius para que la escala de la grafica se vea mejor.
    Serial.print("Celsius:");
    Serial.println(tempC);
  }

  delay(250);   // ~4 muestras por segundo (minimo recomendado: 220 ms)
}
