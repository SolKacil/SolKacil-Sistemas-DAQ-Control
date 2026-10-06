# DS18B20_1 — Lectura básica de temperatura

Primer proyecto de la serie: lectura de un sensor de temperatura digital **DS18B20** con una
**ESP32** y visualización en el **Monitor Serial** del Arduino IDE.

## ¿Qué se aprende?
- Uso del bus **1-Wire** con las librerías `OneWire` y `DallasTemperature`.
- Estructura básica de un sketch: `setup()` y `loop()`.
- Envío de datos a la PC por puerto serie.

---

## ¿Cómo funciona el sensor DS18B20?

El **DS18B20** es un termómetro **digital**: la medición y la conversión a número se hacen
dentro del propio sensor, y este entrega directamente la temperatura en grados Celsius. A
diferencia de un sensor analógico (como el LM35), no depende del ADC del microcontrolador ni
le afectan el ruido o la caída de tensión en cables largos.

Internamente:

1. Un **sensor de temperatura de silicio** genera una señal proporcional a la temperatura.
2. Un **convertidor analógico-digital** la digitaliza con una resolución configurable de
   **9 a 12 bits**.
3. El resultado se guarda en una pequeña memoria interna (*scratchpad*), junto con un
   **CRC** que permite comprobar que el dato llegó sin errores.

### Características principales

| Parámetro | Valor |
|---|---|
| Rango de medición | −55 °C a +125 °C |
| Exactitud | ±0.5 °C (entre −10 °C y +85 °C) |
| Alimentación | 3.0 V a 5.5 V |
| Interfaz | 1-Wire (un solo pin de datos) |
| Identificación | Código único de 64 bits grabado de fábrica |

### Resolución y tiempo de conversión

A mayor resolución, más fino es el dato pero más tarda el sensor en medir:

| Resolución | Paso | Tiempo máximo de conversión |
|:-:|:-:|:-:|
| 9 bits | 0.5 °C | 93.75 ms |
| 10 bits | 0.25 °C | 187.5 ms |
| 11 bits | 0.125 °C | 375 ms |
| 12 bits (de fábrica) | 0.0625 °C | 750 ms |

### El bus 1-Wire

La comunicación usa **un solo cable de datos** (además de alimentación y tierra):

- La línea es de **drenaje abierto**: el sensor y la ESP32 solo pueden ponerla en bajo. La
  resistencia **pull-up de 4.7 kΩ** la regresa a alto; sin ella no hay comunicación.
- La ESP32 (maestro) inicia cada intercambio con un **pulso de reset**, y el sensor contesta
  con un **pulso de presencia**. Después se envían comandos, por ejemplo *Convert T* (iniciar
  medición) y *Read Scratchpad* (leer el resultado).
- Cada DS18B20 tiene un **código de 64 bits único**, así que se pueden conectar **varios
  sensores en el mismo pin** y consultar cada uno por separado.

Las librerías `OneWire` y `DallasTemperature` se encargan de todo este protocolo, por eso el
código del proyecto queda tan corto.

> El sensor también puede alimentarse desde la línea de datos (**modo parásito**, con solo dos
> cables). En este proyecto se usa la alimentación normal con VDD, que es más confiable.

---

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
1. `requestTemperatures()` envía el comando *Convert T* y **espera** a que el sensor termine
   la conversión (hasta 750 ms a 12 bits).
2. `getTempCByIndex(0)` lee el *scratchpad* del primer sensor del bus y devuelve la
   temperatura en °C.
3. Se imprime en el Monitor Serial y se espera 1 s con `delay(1000)`.

Por la espera de la conversión, cada ciclo dura en realidad alrededor de 1.75 s, no 1 s.

`delay()` detiene por completo el programa. Es suficiente aquí, pero en el siguiente
proyecto con este sensor ([`DS18B20_2_WiFi_LabVIEW`](../DS18B20_2_WiFi_LabVIEW)) se reemplaza por `millis()`
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
| `-127.00` | La librería no encontró el sensor: revisar conexiones y la resistencia pull-up. |
| `85.00` constante | Es el valor de encendido del sensor: se leyó antes de terminar la conversión o la alimentación es inestable. |
