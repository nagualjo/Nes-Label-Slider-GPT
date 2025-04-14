
# NES Label GPT - PNG V1

**Donde los sueños se encuentran con la nostalgia**

Este es el proyecto NES Label GPT en su versión con soporte para imágenes .PNG, música .mp3, control por pantalla táctil y un completo menú de configuración. ¡Ideal para disfrutar carátulas de juegos retro con un toque moderno y práctico (Modo Neo incluido)!

## Características
- Muestra imágenes PNG de carátulas de juegos NES desde la tarjeta SD.
- Reproduce archivos .mp3 con el módulo DFPlayer Mini.
- Modo automático con cambio de imagen y música cada 30 segundos.
- Modo Neo: animación tipo "Matrix" activable por menú o alarma de hora de dormir.
- Menú de configuración accesible al iniciar o con toque largo en pantalla.
- Control de brillo mediante PWM en GPIO 32.
- Control de volumen desde el menú.
- Configuraciones guardadas en la EEPROM (simulada en SPIFFS).
- Compatible con pantallas TFT de 4" con controlador ST7796.
- Librerías necesarias incluidas.

## Conexiones del ESP32
(Ver archivo conexiones.txt incluido)

## Uso
1. Copia tus imágenes PNG y archivos MP3 en la microSD (nombrados igual, ej: `zelda.png`, `zelda.mp3`).
2. Carga el código en el ESP32 con PlatformIO o Arduino IDE.
3. Disfruta la experiencia NES Label GPT.

---
Creado por [nagualjo](https://github.com/nagualjo) & ChatGPT





# Nes-Label-Slider-GPT
Nes Label Slider using ESP32 microcontroller and ChatGPT for Coding it

La idea principal es crear un Nes Label Slider desde 0, enfocado en el Rendimiento bajo una Esp32 y sin conocimientos previos de programación en C, y que incorpore todas las Funciones que deseemos tener en nuestro querido Nes Label Slider

Cualquier Persona es Libre de Participar y dar ideas ! Chat GPT las hará realidad para Nosotros !

--------------------------------

The main idea is to create a NES Label Slider from scratch, focused on performance under an ESP32 and without prior C programming knowledge, and incorporating all the features we want in our beloved NES Label Slider. Anyone is free to participate and share ideas! GPT Chat will make them a reality for us. !

-------------------------------

https://youtu.be/czclHcFPeU8?si=UfPwboKNSJtbgNhW

https://youtube.com/playlist?list=PLmfMWYH7Nj0FwavMzZCVX6lTx4F0mGqpq&si=qJpPpOD8D36XHy6z

-------------------------------

Algunas de las Funciones serán las Siguientes:

Some of the Functions will be the following:

-------------------------------

1. Componentes:

ESP32

Pantalla táctil de 4 pulgadas

Lector SD integrado en la pantalla

Módulo MP3-TF-16P

Altavoz conectado al MP3-TF-16P

3231 RTC ( reloj de tiempo real )

Imágenes + MP3s en SD/microSD


2. Funcionamiento básico:

Reproduce una imagen desde la SD (pantalla) y suena una canción desde la microSD (módulo MP3).

A los 30 segundos, cambia a la siguiente imagen y canción.

Si se toca la pantalla antes de los 30s, salta inmediatamente a la siguiente.



Vamos a incluir mas opciones como parte de una futura "pantalla de configuración" dentro del sistema.

Funciones futuras que agregaremos:

1. Tiempo de espera entre imágenes configurable:

Tendremos un valor por defecto (30 segundos), pero el usuario podrá ajustarlo desde el menú (por ejemplo, 10, 20, 60 segundos, etc.).

Se puede guardar en la memoria EEPROM (o en un archivo .cfg en la SD) para que se mantenga entre reinicios.



2. Mostrar imágenes aleatoriamente (shuffle):

Usaremos un algoritmo de mezcla (como Fisher-Yates) para desordenar la lista de archivos.

Esta opción se podrá activar/desactivar desde el menú.

También se puede guardar en la configuración para recordar la preferencia.



Algunas ideas adicionales que podríamos implementar:

Modo demo o presentación automática para expos o vitrinas retro.

Favoritos: que el usuario marque juegos como favoritos para que aparezcan más seguido.

Temas visuales: cambiar colores o fondos de la interfaz.

Volumen ajustable (el MP3-TF-16P permite controlarlo por comandos).

Soporte para múltiples colecciones: por ejemplo, cambiar entre NES, SNES, Sega, etc.

---

 Modo Neo - un toque artístico, funcional y totalmente inesperado al NES Label GPT. Y usarlo como herramienta para mejorar el sueño lo hace aún más especial y personal.

 Es un modo que se activa a la hora de Dormir y de Desactiva automáticamente a la hora de Despertar (back to the matrix) Durante este modo Se paraliza la representación de labels de Juegos y se sustituirá por un Gif animado de Matrix , estableciendo un periodo de Gestión del Sueño o Descanso

Así lo podemos implementar:

1. Modo Neo Manual

Activable desde el menú de configuración.

Reproduce un gif o animación personalizada tipo "código Matrix" (letras verdes en cascada).

Música ambiental suave, ruido blanco, frecuencia de activación REM o silencio total (a elección).


2. Modo Neo Automático

Añadimos un módulo RTC (reloj en tiempo real) como el DS3231 o usamos el reloj interno del ESP32 con WiFi/NTP para sincronizar la hora. para disminuir carga de ram Usaremos un conomico módulo rtc de preferencia 3231

Desde el menú se puede configurar:

Hora para empezar el Modo Neo (por ejemplo, 23:00)

Hora para salir del Modo Neo (por ejemplo, 07:00)


A esas horas, el sistema cambia automáticamente de modo.



---




----------------------------

1. Components:

ESP32

4-inch touchscreen

SD card reader integrated into the screen

MP3-TF-16P module

Speaker connected to the MP3-TF-16P module

3231 RTC (Real Time Clock)

Images + MP3s on SD/microSD

2. Basic Operation:

Plays an image from the SD card (screen) and plays a song from the microSD card (MP3 module).

After 30 seconds, it switches to the next image and song.

If the screen is touched before the 30-second mark is reached, it immediately skips to the next one.

We will include more options as part of a future "configuration screen" within the system.

Future features we'll be adding:

1. Configurable timeout between images:

We'll have a default value (30 seconds), but the user can adjust it from the menu (for example, 10, 20, 60 seconds, etc.).

This can be saved in the EEPROM (or a .cfg file on the SD card) so it persists between reboots.

2. Display images randomly (shuffle):

We'll use a shuffling algorithm (like Fisher-Yates) to unscramble the file list.

This option can be enabled/disabled from the menu.

It can also be saved in the settings to remember the preference.

Some additional ideas we could implement:

Demo mode or automatic presentation for exhibitions or retro showcases.

Favorites: Allow the user to mark games as favorites so they appear more often.

Visual themes: Change interface colors or backgrounds.

Adjustable volume (the MP3-TF-16P allows for command control).

Support for multiple collections: for example, switching between NES, SNES, Sega, etc.

----

Neo Mode - an artistic, functional, and totally unexpected touch to the NES Label GPT. And using it as a tool to improve sleep makes it even more special and personal.

It's a mode that activates at bedtime and automatically deactivates at wake-up time (back to the matrix). During this mode, the display of game labels is paralyzed and replaced by an animated Matrix GIF, establishing a Sleep Management or Rest period.

This is how we can implement it:

1. Manual Neo Mode

Activated from the configuration menu.

Plays a custom GIF or animation like "Matrix code" (cascading green letters).

Soft ambient music, white noise, REM wake-up frequency, or total silence (your choice).

2. Automatic Neo Mode

Add an RTC (real-time clock) module like the DS3231 or use the ESP32's internal clock with WiFi/NTP to synchronize the time. To reduce RAM load, we'll use an economical RTC module, preferably 3231.

From the menu, you can configure:

Time to start Neo Mode (for example, 11:00 PM)

Time to exit Neo Mode (for example, 7:00 AM)

At these times, the system automatically switches modes.

