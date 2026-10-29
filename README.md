# Sistemas DAQ y Control

Colección de proyectos de **adquisición de datos (DAQ) y control** con **ESP32**, organizados
como una ruta progresiva.

Cada proyecto es **didáctico pero aplicable a un entorno real**: código claro y comentado,
documentación completa, conexiones y solución de problemas.

## Proyectos

| # | Proyecto | Sensor | Comunicación / Interfaz | Conceptos nuevos |
|:-:|---|---|---|---|
| 1 | [DS18B20_1](DS18B20_1) | DS18B20 | Monitor Serial | Bus 1-Wire, estructura de un sketch |
| 2 | [MAX6675_1](MAX6675_1) | Termopar K + MAX6675 | Monitor y Serial Plotter | SPI, altas temperaturas, detección de fallas |
| 3 | [DS18B20_2_WiFi_LabVIEW](DS18B20_2_WiFi_LabVIEW) | DS18B20 | WiFi (TCP) → LabVIEW | ESP32 como punto de acceso, cliente TCP en LabVIEW, `millis()` |
| 4 | [DHT22_1_WiFi_LabVIEW](DHT22_1_WiFi_LabVIEW) | DHT22 | WiFi (TCP) → LabVIEW | Varias variables por trama (CSV), validación de lecturas |
| 5 | [Simulacion_1_CSV_LabVIEW](Simulacion_1_CSV_LabVIEW) | Simulado (sin hardware) | LabVIEW → archivo CSV | Registro de datos en archivo, marcas de tiempo |

## Herramientas
- **Hardware:** ESP32 (ESP-WROOM-32 DevKit)
- **Firmware:** Arduino IDE con el paquete de placas ESP32
- **Interfaz:** LabVIEW 2025 (en los proyectos que lo indican)

Cada carpeta contiene su propio `README.md` con material, conexiones, explicación del código
e instrucciones de uso.

## Estructura
```
├── DS18B20_1/                 Lectura básica por puerto serie
├── MAX6675_1/                 Termopar tipo K por SPI
├── DS18B20_2_WiFi_LabVIEW/    Envío por WiFi a LabVIEW
├── DHT22_1_WiFi_LabVIEW/      Temperatura y humedad por WiFi a LabVIEW
└── Simulacion_1_CSV_LabVIEW/  Sensor simulado con registro en CSV
```

## Licencia
Distribuido bajo la licencia [MIT](LICENSE).
