# NES Label GPT - V2.1

**Where dreams meet pixels**

NES Label GPT is a project that blends retro charm with modern functionality, allowing you to enjoy NES game covers along with music in an interactive way. With support for .PNG images, .mp3 music playback, touchscreen control, and a full configuration menu, this project delivers a unique experience for fans of classic video games.

> The main goal is to create a NES Label Slider completely from scratch, optimized for smooth performance on an ESP32—even without prior knowledge of C programming.  
> All development has been guided and written alongside **ChatGPT**, with a strong focus on performance, stability, and ease of use.

This project is open to the community: anyone is welcome to join, share ideas, and collaborate.  
**ChatGPT will bring them to life together with us!**

---

![GitHub repo size](https://img.shields.io/github/repo-size/nagualjo/nes-label-gpt)
![GitHub stars](https://img.shields.io/github/stars/nagualjo/nes-label-gpt?style=social)

---

## Features
- Displays PNG images of NES game covers from the SD card.
- Plays .mp3 files using the DFPlayer Mini module.
- Automatic mode with image and music change every 30 seconds.
- Neo Mode: Matrix-style animation, manually or automatically triggered.
- Configuration menu accessible on boot or by long-pressing the screen.
- Brightness control via PWM on GPIO 32.
- Volume control from the menu.
- Settings saved in EEPROM (simulated using SPIFFS).
- Optional real-time clock (RTC) or NTP sync via WiFi.
- Show/Hide clock toggle (hidden in cover mode, visible in Neo mode).
- Compatible with 4" TFT screens using the ST7796 controller.
- Required libraries included.

## ESP32 Pinout
(See `conexiones.txt` file included in the repository)

---

## How to Use
1. Copy your PNG images and MP3 files to the microSD (with matching names, e.g., `zelda.png`, `zelda.mp3`).
2. Upload the code to your ESP32 using PlatformIO or the Arduino IDE.
3. Enjoy the NES Label GPT experience!

---

## Neo Mode
An artistic, functional, and unexpected twist to NES Label GPT—also used as a tool to improve sleep.  
During this mode, game cover playback stops and is replaced with a Matrix-style animation (green letters falling), establishing a visual resting period.

### Manual Neo Mode
- Activated from the configuration menu.
- Displays a Matrix-like animation or GIF.
- Optionally plays ambient music, white noise, REM frequency tones, or silence.

### Automatic Neo Mode
- Uses a DS3231 RTC module or ESP32's internal clock with WiFi/NTP.
- Configurable sleep/wake hours (e.g., 23:00 to 07:00).
- System switches automatically at scheduled times.

---

## Future Features

| Feature                             | Status     |
|-------------------------------------|------------|
| Configurable image timeout          | Planned    |
| Random/shuffle image mode           | Implemented    |
| Favorite group image playback       | Planned    |
| Support for other systems (e.g. SNES, Genesis) | Planned |
| Neo Mode auto/manual scheduling     | Implemented |
| Show/hide clock option              | Implemented |

---

## Screenshots

_future screenshots here for better project visualization._

![Cover Mode](docs/screenshot1.png)
![Neo Mode](docs/screenshot2.png)

---

## Components Used
- ESP32
- 4" touchscreen with integrated SD card reader
- MP3-TF-16P (DFPlayer Mini) module
- Speaker connected to DFPlayer Mini
- DS3231 RTC (Real-Time Clock)
- Images and MP3s stored on SD/microSD

---

## Acknowledgments
This project wouldn't be possible without:

- The **open-source** community
- **PlatformIO / Arduino IDE** developers
- **ChatGPT**, for the collaborative coding, optimization, and documentation process
- davidxgames y eolvera85 for their neslbel proyects and su calida atención personal 
- Everyone watching, sharing, and contributing ideas via GitHub and YouTube

---

Created by [nagualjo](https://github.com/nagualjo) & ChatGPT

[Watch the demo on YouTube](https://youtu.be/czclHcFPeU8?si=UfPwboKNSJtbgNhW)  
[Project playlist](https://youtube.com/playlist?list=PLmfMWYH7Nj0FwavMzZCVX6lTx4F0mGqpq&si=qJpPpOD8D36XHy6z)

---

# NES Label GPT - V1 (Español)

**Donde los sueños se encuentran con la nostalgia**

NES Label GPT es un proyecto que combina el encanto retro con funcionalidades modernas, permitiéndote disfrutar de carátulas de juegos NES junto con música de manera interactiva. Con soporte para imágenes .PNG, reproducción de música .mp3, control táctil y un menú de configuración completo, este proyecto ofrece una experiencia única para los amantes de los videojuegos clásicos.

> La idea principal es crear un NES Label Slider completamente desde cero, optimizado para un rendimiento fluido en un ESP32, ¡sin necesidad de conocimientos previos de programación en C!  
> Todo el desarrollo ha sido guiado y escrito junto a **ChatGPT**, con enfoque en el rendimiento, estabilidad y facilidad de uso.

Este proyecto está abierto a la comunidad: cualquier persona puede participar, compartir ideas y colaborar.  
**¡ChatGPT las hará realidad junto a nosotros!**

---

## Características
- Muestra imágenes PNG de carátulas de juegos NES desde la tarjeta SD.
- Reproduce archivos .mp3 con el módulo DFPlayer Mini.
- Modo automático con cambio de imagen y música cada 30 segundos.
- Modo Neo: animación estilo "Matrix" activable manualmente o por horario.
- Menú de configuración accesible al iniciar o con toque largo en pantalla.
- Control de brillo mediante PWM en GPIO 32.
- Control de volumen desde el menú.
- Configuraciones guardadas en la EEPROM (simulada en SPIFFS).
- Opción de sincronización de reloj con WiFi/NTP o módulo RTC.
- Opción de mostrar u ocultar el reloj (oculto en carátulas, visible en modo Neo).
- Compatible con pantallas TFT de 4" con controlador ST7796.
- Librerías necesarias incluidas.

## Conexiones del ESP32
(Ver archivo `conexiones.txt` incluido en el repositorio)

---

## Uso
1. Copia tus imágenes PNG y archivos MP3 en la microSD (con nombres coincidentes, ej: `zelda.png`, `zelda.mp3`).
2. Carga el código en el ESP32 usando PlatformIO o Arduino IDE.
3. Disfruta la experiencia NES Label GPT.

---

## Modo Neo
Un giro artístico, funcional y totalmente inesperado al NES Label GPT—también usado como herramienta para mejorar el sueño.

Durante este modo, se detiene la reproducción de carátulas y se reemplaza por una animación estilo Matrix (letras verdes en cascada), estableciendo un período visual de descanso.

### Modo Neo Manual
- Activado desde el menú de configuración.
- Muestra un GIF o animación estilo Matrix.
- Opcionalmente reproduce música ambiental, ruido blanco, tonos REM o silencio total.

### Modo Neo Automático
- Usa un módulo RTC DS3231 o el reloj interno del ESP32 con WiFi/NTP.
- Horarios configurables para dormir y despertar (ej: 23:00 a 07:00).
- El sistema cambia automáticamente de modo en los horarios establecidos.

---

## Funciones Futuras

| Función                               | Estado     |
|---------------------------------------|------------|
| Tiempo configurable entre imágenes    | Planeado   |
| Modo aleatorio para las carátulas     | Implemented   |
| Grupo de imágenes favoritas           | Planeado   |
| Mostrar otros sistemas retro          | Planeado   |
| Programación automática del Modo Neo  | Implementado |
| Mostrar/Ocultar reloj desde menú      | Implementado |

---

## Screenshots

![Cover Mode](docs/screenshot1.png)
![Neo Mode](docs/screenshot2.png)

---

## Componentes Usados
- ESP32
- Pantalla táctil de 4" con lector SD integrado
- Módulo MP3-TF-16P (DFPlayer Mini)
- Altavoz conectado al MP3-TF-16P
- Reloj de tiempo real DS3231 (RTC)
- Imágenes y MP3s en tarjetas SD/microSD

---



---

## Version History

---
## NES Label GPT - V1

Initial Public Release

- Muestra carátulas NES en formato PNG desde SD.

- Reproduce música .mp3 sincronizada desde DFPlayer Mini.

- Cambio automático cada 30 segundos.

- Modo Neo básico: animación estilo Matrix activable manualmente.

- Menú de configuración táctil.

- Brillo controlado por PWM (GPIO 32).

- Volumen ajustable desde el menú.

- Configuraciones guardadas en SPIFFS simulando EEPROM.

- Reloj RTC (DS3231) o sincronización por NTP.

- Código documentado y optimizado para ESP32.


> La primera versión estable y funcional que demuestra el concepto completo del proyecto.


---

# NES Label GPT - V2

First Major Upgrade

- Implementación del modo aleatorio (shuffle) con algoritmo Fisher-Yates para mezcla de imágenes.

- Nueva opción en el menú para activar o desactivar el modo aleatorio.

- Estructura reorganizada para una mayor eficiencia y legibilidad.

- Lógica de imagen y música totalmente sincronizada con reproducción ordenada o aleatoria.

- Preparado para nuevas expansiones: favoritos, multiconsolas, horarios dinámicos.

- Revisión profunda y validación del sistema general.


> Una evolución natural hacia un sistema más dinámico, personalizable y robusto. Listo para expandirse y adaptarse.



---


## Entorno recomendado: 

Visual Studio Code con extensión de Arduino instalada (o Arduino IDE)


---

Lista de librerías necesarias:

- 1. TFT_eSPI
Para el manejo de la pantalla. Configura correctamente el archivo User_Setup.h con tus pines y controlador.

Instalación: desde el Gestor de Librerías Arduino.

Repositorio: https://github.com/Bodmer/TFT_eSPI



- 2. SPIFFS o SD
Para acceder a los archivos en tarjeta SD o sistema de archivos.

Instalación: Incluido en el núcleo de ESP32.



- 3. TouchScreen / XPT2046_Touchscreen (según tu pantalla táctil)

Si tu pantalla usa XPT2046, te recomiendo:
XPT2046_Touchscreen
https://github.com/PaulStoffregen/XPT2046_Touchscreen



- 4. DFPlayer Mini Mp3 by Makuna
Para controlar el módulo MP3-TF-16P.

Instalación: desde el Gestor de Librerías Arduino.

Nombre en gestor: DFPlayer Mini Mp3 by Makuna



- 5. EEPROM (o preferentemente Preferences de ESP32)

Ya incluido en el core de ESP32 para guardar configuraciones.



- 6. Time / NTPClient / DS3231 (si usas reloj interno o externo, según el modo seleccionado)


- 7. Adafruit GFX (solo si alguna librería de pantalla la requiere como dependencia)




---

Configuraciones extra:

En el archivo User_Setup.h de TFT_eSPI, asegúrate de tener bien definidos:

Pines SPI

Controlador (por ejemplo, ILI9341 o ST7789)

Resolución (320x240, 480x320, etc.)


---



## Agradecimientos
Este proyecto no sería posible sin:

- La comunidad de **código abierto**
- Los desarrolladores de **PlatformIO / Arduino IDE**
- **ChatGPT**, por toda la codificación, optimización y documentación
- davidxgames y eolvera85 x sus respectivos proyectos nes label slider y su calida atención personal 
- Todos los que ven, comparten o aportan ideas vía GitHub o YouTube

---

Creado por [nagualjo](https://github.com/nagualjo) & ChatGPT

[Ver demo en YouTube](https://youtu.be/czclHcFPeU8?si=UfPwboKNSJtbgNhW)  
[Lista de reproducción del proyecto](https://youtube.com/playlist?list=PLmfMWYH7Nj0FwavMzZCVX6lTx4F0mGqpq&si=qJpPpOD8D36XHy6z)



---




