# Nes-Label-Slider-GPT
Nes Label Slider using ESP32 and ChatGPT for Coding it

La idea principal es crear un Nes Label Slider desde 0, enfocado en el Rendimiento bajo una Esp32 y sin conocimientos previos de programación en C, y que incorpore todas las Funciones que deseemos tener en nuestro querido Nes Label Slider

Cualquier Persona es Libre de Participar y dar ideas ! Chat GPT las hará realidad para Nosotros !

--------------------------------

The main idea is to create a NES Label Slider from scratch, focused on performance under an ESP32 and without prior C programming knowledge, and incorporating all the features we want in our beloved NES Label Slider. Anyone is free to participate and share ideas! GPT Chat will make them a reality for us. !

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

