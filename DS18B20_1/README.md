# DS18B20_1 — Lectura básica de temperatura

Primer proyecto de la serie: lectura de un sensor de temperatura digital **DS18B20** con una
**ESP32** y visualización en el **Monitor Serial** del Arduino IDE.

## ¿Qué se aprende?
- Uso del bus **1-Wire** con las librerías `OneWire` y `DallasTemperature`.
- Estructura básica de un sketch: `setup()` y `loop()`.
- Envío de datos a la PC por puerto serie.

## Material
- ESP32
- Sensor DS18B20 (encapsulado TO-92 o versión sumergible)
- Resistencia de 4.7 kΩ

## Conexiones
| DS18B20 | ESP32 |
|---|---|
| VDD | 3.3 V |
| GND | GND |
| DATA | GPIO 4 |

La resistencia de **4.7 kΩ va entre DATA y 3.3 V** (pull-up). Sin ella el bus 1-Wire no
funciona y la lectura será `-127.00`.

## Cómo funciona el código
```cpp
sensor.requestTemperatures();            // pide la medicion al sensor
float temp = sensor.getTempCByIndex(0);  // lee el primer sensor del bus
```
1. `requestTemperatures()` ordena al sensor que convierta la temperatura.
2. `getTempCByIndex(0)` lee el resultado en °C del primer sensor del bus.
3. Se imprime en el Monitor Serial y se espera 1 s con `delay(1000)`.

`delay()` detiene por completo el programa. Es suficiente aquí, pero en el siguiente
proyecto ([`DS18B20_2_WiFi_LabVIEW`](../DS18B20_2_WiFi_LabVIEW)) se reemplaza por `millis()`
para que la ESP32 pueda atender la comunicación WiFi mientras tanto.

## Uso
1. Instalar las librerías **OneWire** y **DallasTemperature** desde el Gestor de Librerías.
2. Abrir `DS18B20_1.ino`, seleccionar la placa ESP32 y el puerto COM.
3. Subir el programa y abrir el Monitor Serial a **115200 baudios**.

Salida esperada:
```
Midiendo temperatura...
Temperatura:24.56
Temperatura:24.62
```

| Lectura | Significado |
|---|---|
| `-127.00` | El sensor no responde: revisar conexiones y la resistencia pull-up. |
| `85.00` constante | Lectura antes de terminar la conversión o alimentación inestable. |
