#include <DHT.h>   // libreria "DHT sensor library" de Adafruit
#include <WiFi.h>

#define PIN_SENSOR 4
#define TIPO_SENSOR DHT22

// Datos de la red que crea la ESP32 (punto de acceso)
const char* SSID     = "ESP32_DAQ";
const char* PASSWORD = "12345678";   // minimo 8 caracteres
const uint16_t PUERTO = 5000;        // puerto TCP al que se conecta LabVIEW

// El DHT22 necesita al menos 2 s entre lecturas
const unsigned long PERIODO = 2000;  // ms

DHT sensor(PIN_SENSOR, TIPO_SENSOR);

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

    float temp = sensor.readTemperature();  // grados Celsius
    float hum  = sensor.readHumidity();     // % de humedad relativa

    // Si la lectura falla la libreria devuelve NaN.
    // No se envia nada para que LabVIEW no grafique un dato invalido.
    if (isnan(temp) || isnan(hum)) {
      Serial.println("Error: el DHT22 no responde");
      return;
    }

    // Formato para el Serial Plotter: "Etiqueta:valor" separados por coma
    Serial.printf("Temperatura:%.2f,Humedad:%.2f\n", temp, hum);

    // Envia ambos valores en una sola linea, separados por coma,
    // ej. "24.56,55.30\r\n". Asi LabVIEW recibe siempre la pareja completa.
    if (cliente && cliente.connected()) {
      cliente.printf("%.2f,%.2f\r\n", temp, hum);
    }
  }
}
