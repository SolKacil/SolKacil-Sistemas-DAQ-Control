#include <OneWire.h> //libreria
#include <DallasTemperature.h>

#define PIN_SENSOR 4

OneWire oneWire(PIN_SENSOR);
DallasTemperature sensor(&oneWire);

void setup() {
  Serial.begin(115200);
  sensor.begin();
  Serial.println("Midiendo temperatura...");
}

void loop() {
  sensor.requestTemperatures();            // pide la medicion al sensor
  float temp = sensor.getTempCByIndex(0);  // lee el primer sensor del bus

  Serial.print("Temperatura:");
  Serial.println(temp);

  delay(1000);  // una lectura por segundo
}
