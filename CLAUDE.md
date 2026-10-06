# Sistemas DAQ y Control

Colección de proyectos de adquisición de datos y control con microcontroladores. Publicada en GitHub (repositorio `Sistemas-DAQ-Control`, público, licencia MIT) como portafolio profesional. Es un solo repositorio con una carpeta por proyecto.

## Objetivo
- Proyectos **didácticos pero aplicables a entornos reales**: código claro y explicado, sin sacrificar robustez.
- Progresión de dificultad en **aplicación, hardware y software**: cada proyecto parte del anterior y agrega una sola idea nueva importante (comunicación, más sensores, almacenamiento, protocolo industrial, etc.).
- Calidad presentable: debe dar buena impresión a quien revise el repositorio.

## Proyectos
| Carpeta | Contenido |
|---|---|
| `DS18B20_1` | Lectura básica de un DS18B20 con ESP32 por monitor serie (usa `delay`) |
| `MAX6675_1` | Termopar tipo K con MAX6675 (SPI por software) por Monitor y Serial Plotter (usa `delay`) |
| `DS18B20_2_WiFi_LabVIEW` | ESP32 como punto de acceso WiFi + servidor TCP; LabVIEW como cliente grafica la temperatura |

Actualizar esta tabla y la del `README.md` de la raíz al agregar proyectos.

## Convenciones
- **Plataforma:** ESP32 con Arduino IDE (archivos `.ino`; la carpeta y el `.ino` llevan el mismo nombre).
- **Nombres de carpeta:** `<SENSOR>_<n>_<Tema>`; `<n>` cuenta los proyectos de ese sensor. El orden de la ruta de aprendizaje lo marca la tabla del README raíz.
- **Idioma:** comentarios, nombres de variables y documentación en español.
- **Estilo de código:** sencillo y legible, comentarios breves que expliquen el *porqué*. Partir del código del proyecto anterior para que se note la evolución.
- **Temporización:** los proyectos básicos de lectura por serie pueden usar `delay()`; desde que hay comunicación (WiFi, etc.) usar `millis()`.
- **Cada proyecto lleva su `README.md`** con: descripción, material, conexiones (pines), formato de datos/protocolo, instrucciones de uso y qué se aprende o qué cambia respecto al proyecto anterior.
- **LabVIEW:** versión 2025 (indicarlo en cada README). Los `.vi` son binarios y Claude no puede generarlos. Se documenta en el README cómo construirlos paso a paso; el usuario los crea y los guarda en la carpeta del proyecto.

## GitHub
- La raíz tiene `README.md` (índice y ruta de aprendizaje), `LICENSE` (MIT) y `.gitignore`. Fotos o capturas de cada proyecto (VI, diagrama de conexión, sistema real) van en su carpeta y se enlazan desde su README.
- Imágenes de terceros: citar la fuente en el README.
- No subir credenciales reales de redes WiFi. Las contraseñas del punto de acceso de la ESP32 son de ejemplo.
