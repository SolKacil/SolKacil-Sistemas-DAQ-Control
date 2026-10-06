#include <OneWire.h> //libreria
#include <DallasTemperature.h>
#include <WiFi.h>

#define PIN_SENSOR 4

// Datos de la red que crea la ESP32 (punto de acceso)
const char* SSID     = "ESP32_DAQ";
const char* PASSWORD = "12345678";   // minimo 8 caracteres
const uint16_t PUERTO = 5000;        // puerto TCP al que se conecta LabVIEW

const unsigned long PERIODO = 1000;  // una lectura por segundo (ms)

OneWire oneWire(PIN_SENSOR);
DallasTemperature sensor(&oneWire);

WiFiServer servidor(PUERTO);
WiFiClient cliente;

unsigned long tAnterior = 0;

void setup() {
  Serial.begin(115200);
  sensor.begin();

  // Crea el punto de acceso. IP por defecto: 192.168.4.1
  WiFi.softAP(SSID, PASSWORD);
  Serial.print("Punto de acceso creado. IP: ");
  Serial.println(WiFi.softAPIP());

  servidor.begin();
  servidor.setNoDelay(true);
  Serial.println("Esperando a LabVIEW...");
}

void loop() {
  // Si no hay cliente conectado, revisa si llego uno nuevo
  if (!cliente || !cliente.connected()) {
    WiFiClient nuevo = servidor.available();
    if (nuevo) {
      cliente = nuevo;
      Serial.println("LabVIEW conectado");
    }
  }

  // Lectura periodica sin bloquear (millis en lugar de delay)
  if (millis() - tAnterior >= PERIODO) {
    tAnterior = millis();

    sensor.requestTemperatures();            // pide la medicion al sensor
    float temp = sensor.getTempCByIndex(0);  // lee el primer sensor del bus

    Serial.print("Temperatura:");
    Serial.println(temp);

    // Envia el dato como texto terminado en \r\n, ej. "24.56\r\n"
    if (cliente && cliente.connected()) {
      cliente.print(temp, 2);
      cliente.print("\r\n");
    }
  }
}
