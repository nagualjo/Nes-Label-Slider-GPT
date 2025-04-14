# NES Label GPT - V1

**Where dreams meet nostalgia**

NES Label GPT is a project that blends retro charm with modern functionality, allowing you to enjoy NES game covers along with music in an interactive way. With support for .PNG images, .mp3 music playback, touchscreen control, and a full configuration menu, this project delivers a unique experience for fans of classic video games.

The main goal is to create a NES Label Slider completely from scratch, optimized for smooth performance on an ESP32—even without prior knowledge of C programming. All development has been guided and written alongside **ChatGPT**, with a strong focus on performance, stability, and ease of use.

This project is open to the community: anyone is welcome to join, share ideas, and collaborate. **ChatGPT will bring them to life together with us!**

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

## Future Features
1. **Configurable image timeout**: 
   Default is 30 seconds, but users will be able to set it in the menu (e.g., 10, 20, 60 seconds). This setting will be saved in EEPROM or in a `.cfg` file.

2. **Random image mode (shuffle)**:
   We'll use a shuffling algorithm like Fisher-Yates to randomize the image list. This option can be toggled from the menu and stored in the saved settings.

3. Favorite Group images
   
4. show other systems like megadrive genesis, snes, msx,, etc

6. help me Choosing and thinkinq another new
   
---

## Neo Mode
An artistic, functional, and unexpected twist to NES Label GPT—also used as a tool to improve sleep. 

During this mode, game cover playback stops and is replaced with a Matrix-style animation (green letters falling), establishing a visual resting period. You can activate it manually or set it to follow a sleep schedule.

### Manual Neo Mode
- Activated from the configuration menu.
- Displays a Matrix-like GIF or animation.
- Optionally plays ambient music, white noise, REM frequency tones, or complete silence.

### Automatic Neo Mode
- Uses a DS3231 RTC module (preferred for low RAM usage) or ESP32's internal clock with WiFi/NTP.
- Configurable sleep and wake hours (e.g., 23:00 to 07:00).
- System switches automatically at scheduled times.

---

## Components Used
- ESP32
- 4" touchscreen with integrated SD card reader
- MP3-TF-16P (DFPlayer Mini) module
- Speaker connected to DFPlayer Mini
- DS3231 RTC (Real-Time Clock)
- Images and MP3s stored on SD/microSD

---

Created by [nagualjo](https://github.com/nagualjo) & ChatGPT

[Watch the demo on YouTube](https://youtu.be/czclHcFPeU8?si=UfPwboKNSJtbgNhW)

[Project playlist](https://youtube.com/playlist?list=PLmfMWYH7Nj0FwavMzZCVX6lTx4F0mGqpq&si=qJpPpOD8D36XHy6z)

---

# NES Label GPT - V1 (Español)

**Donde los sueños se encuentran con la nostalgia**

NES Label GPT es un proyecto que combina el encanto retro con funcionalidades modernas, permitiéndote disfrutar de carátulas de juegos NES junto con música de manera interactiva. Con soporte para imágenes .PNG, reproducción de música .mp3, control táctil y un menú de configuración completo, este proyecto ofrece una experiencia única para los amantes de los videojuegos clásicos.

La idea principal es crear un NES Label Slider completamente desde cero, optimizado para un rendimiento fluido en un ESP32, ¡sin necesidad de conocimientos previos de programación en C! Todo el desarrollo ha sido guiado y escrito junto a **ChatGPT**, con enfoque en el rendimiento, estabilidad y facilidad de uso.

Este proyecto está abierto a la comunidad: cualquier persona puede participar, compartir ideas y colaborar. **¡ChatGPT las hará realidad junto a nosotros!**

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

## Funciones Futuras
1. **Tiempo configurable entre imágenes**:
   El valor por defecto es de 30 segundos, pero el usuario podrá ajustarlo desde el menú (por ejemplo, 10, 20, 60 segundos). Esta configuración se guardará en EEPROM o en un archivo `.cfg`.

2. **Mostrar imágenes aleatoriamente (shuffle)**:
   Usaremos un algoritmo como Fisher-Yates para mezclar la lista de imágenes. Esta opción se podrá activar/desactivar desde el menú y se almacenará en la configuración.

3. escoger imágenes favoritas para reproducir con mayor frecuencia

4. mostrar otros sistemas (genesis, snes, gameboy,,)

5. ayuda a escoger una nueva función! 


---

## Modo Neo
Un giro artístico, funcional y totalmente inesperado al NES Label GPT—también usado como herramienta para mejorar el sueño.

Durante este modo, se detiene la reproducción de carátulas y se reemplaza por una animación estilo Matrix (letras verdes en cascada), estableciendo un período visual de descanso. Puedes activarlo manualmente o establecer un horario de sueño.

### Modo Neo Manual
- Activado desde el menú de configuración.
- Muestra un GIF o animación estilo Matrix.
- Opcionalmente reproduce música ambiental, ruido blanco, tonos REM o silencio total.

### Modo Neo Automático
- Usa un módulo RTC DS3231 (preferido por bajo uso de RAM) o el reloj interno del ESP32 con WiFi/NTP.
- Horarios configurables para dormir y despertar (ej: 23:00 a 07:00).
- El sistema cambia automáticamente de modo en los horarios establecidos.

---

## Componentes Usados
- ESP32
- Pantalla táctil de 4" con lector SD integrado
- Módulo MP3-TF-16P (DFPlayer Mini)
- Altavoz conectado al MP3-TF-16P
- Reloj de tiempo real DS3231 (RTC)
- Imágenes y MP3s en tarjetas SD/microSD

---

Creado por [nagualjo](https://github.com/nagualjo) & ChatGPT

[Ver demo en YouTube](https://youtu.be/czclHcFPeU8?si=UfPwboKNSJtbgNhW)

[Lista de reproducción del proyecto](https://youtube.com/playlist?list=PLmfMWYH7Nj0FwavMzZCVX6lTx4F0mGqpq&si=qJpPpOD8D36XHy6z)

---


