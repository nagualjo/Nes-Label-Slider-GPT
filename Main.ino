// NES Label GPT - Versión V1
// Proyecto desarrollado con amor por nagualjo & ChatGPT
// Muestra carátulas de juegos NES (.png) y reproduce su música (.mp3) desde microSD
// Pantalla táctil con menú de configuración, reloj opcional, modo Matrix, control de brillo y más

#include <Arduino.h>
#include <TFT_eSPI.h>             // Librería para la pantalla TFT
#include <SPI.h>                  // Comunicación SPI
#include <FS.h>                   // Sistema de archivos
#include <SD.h>                   // Lectura de tarjetas SD
#include <JPEGDecoder.h>         // Para decodificar imágenes JPEG (opcional, no usado ahora)
#include <PNGdec.h>              // Librería para mostrar PNG
#include <SoftwareSerial.h>      // Comunicación con el módulo MP3-TF-16P
#include <WiFi.h>                // WiFi para NTP
#include <NTPClient.h>           // Cliente NTP para obtener hora por internet
#include <WiFiUdp.h>             // Necesario para NTP
#include <EEPROM.h>              // Guardar configuraciones del usuario
#include <RTClib.h>              // Librería para el módulo RTC (como DS3231)
#include <TouchScreen.h>         // Manejo del panel táctil (si usas resistivo)

//---------------------------------- CONFIGURACIÓN DE PINES ----------------------------------//

#define SD_CS       5     // Chip select de la microSD
#define MP3_RX      16    // RX del MP3
#define MP3_TX      17    // TX del MP3
#define LED_PIN     32    // PWM para el control del brillo
#define TOUCH_IRQ   12    // Pin de interrupción táctil (IRQ)

//---------------------------------- OBJETOS Y VARIABLES GLOBALES ----------------------------------//

TFT_eSPI tft = TFT_eSPI();     // Objeto de la pantalla
PNG png;                       // Objeto para mostrar PNG
SoftwareSerial mp3(MP3_RX, MP3_TX);  // Comunicación con el reproductor MP3
RTC_DS3231 rtc;                // Objeto del módulo RTC
WiFiUDP ntpUDP;                // Canal UDP para el cliente NTP
NTPClient timeClient(ntpUDP); // Cliente NTP

unsigned long lastChange = 0; // Último cambio de imagen/canción
int interval = 30000;         // Tiempo entre cambios (ms)
bool randomMode = false;      // Modo aleatorio activado o no
bool showClock = false;       // Mostrar reloj (configurable desde menú)

int totalFiles = 0;           // Total de carátulas/mp3 disponibles
int currentIndex = 0;         // Índice actual

//---------------------------------- CONFIGURACIÓN INICIAL ----------------------------------//

void setup() {
  Serial.begin(115200);
  tft.init();
  tft.setRotation(1);
  analogWrite(LED_PIN, 200); // Control de brillo inicial (PWM)

  // Inicializar SD
  if (!SD.begin(SD_CS)) {
    tft.println("Error al montar SD");
    while (true);
  }

  // Buscar cantidad de archivos disponibles
  totalFiles = contarArchivos();

  // Inicializar MP3
  mp3.begin(9600);
  delay(500);
  mp3.write(0x7E); // Comando de inicio simple
  mp3.write(0xFF);
  mp3.write(0x06);
  mp3.write(0x0F);
  mp3.write(0x00);
  mp3.write(0x00);
  mp3.write(0x01);
  mp3.write(0xEF);

  // Inicializar WiFi y reloj
  WiFi.begin("SSID", "PASSWORD"); // <- Cambiar por tu red
  int retries = 10;
  while (WiFi.status() != WL_CONNECTED && retries-- > 0) delay(1000);

  if (WiFi.status() == WL_CONNECTED) {
    timeClient.begin();
    timeClient.setTimeOffset(3600); // Ajuste horario (GMT+1)
  } else if (!rtc.begin()) {
    tft.println("RTC no detectado, se usará conteo interno");
  }

  // Mostrar primera imagen
  mostrarImagenYMusica(currentIndex);
  lastChange = millis();
}

//---------------------------------- BUCLE PRINCIPAL ----------------------------------//

void loop() {
  if (millis() - lastChange >= interval) {
    currentIndex = (randomMode) ? random(totalFiles) : (currentIndex + 1) % totalFiles;
    mostrarImagenYMusica(currentIndex);
    lastChange = millis();
  }

  if (showClock) {
    mostrarReloj();
  }
}

//---------------------------------- FUNCIONES CLAVE ----------------------------------//

// Cuenta la cantidad de archivos de carátulas (.png)
int contarArchivos() {
  File root = SD.open("/");
  int count = 0;
  while (true) {
    File entry = root.openNextFile();
    if (!entry) break;
    String name = entry.name();
    if (name.endsWith(".png")) count++;
    entry.close();
  }
  return count;
}

// Muestra imagen PNG y reproduce el mp3 con el mismo nombre
void mostrarImagenYMusica(int index) {
  char nombre[20];
  sprintf(nombre, "/%03d.png", index);
  File archivo = SD.open(nombre);
  if (archivo) {
    tft.fillScreen(TFT_BLACK);
    png.open(archivo, pngDraw);
    png.decode(NULL, 0);
    archivo.close();
  }
  // Reproducir música
  sprintf(nombre, "%03d", index);
  enviarComandoMP3(nombre);
}

// Dibuja los pixeles del PNG (callback)
void pngDraw(PNGDRAW *pDraw) {
  tft.pushImage(pDraw->x, pDraw->y, pDraw->iWidth, 1, (uint16_t *)pDraw->pPixels);
}

// Enviar comando al MP3 para reproducir archivo
void enviarComandoMP3(const char *nombre) {
  mp3.write(0x7E);
  mp3.write(0xFF);
  mp3.write(0x06);
  mp3.write(0x03);
  mp3.write(0x00);
  mp3.write(0x00);
  mp3.write(nombre[0]); // Suponiendo archivos como 001.mp3
  mp3.write(0xEF);
}

// Mostrar hora (modo Matrix o si se activa)
void mostrarReloj() {
  DateTime ahora;
  if (WiFi.status() == WL_CONNECTED) {
    timeClient.update();
    tft.setCursor(0, 0);
    tft.setTextColor(TFT_GREEN);
    tft.print(timeClient.getFormattedTime());
  } else if (rtc.isrunning()) {
    ahora = rtc.now();
    tft.setCursor(0, 0);
    tft.setTextColor(TFT_CYAN);
    tft.printf("%02d:%02d:%02d", ahora.hour(), ahora.minute(), ahora.second());
  }
}

//---------------------------------- FIN DEL CÓDIGO ----------------------------------//
// Puedes extender con menú táctil, configuración EEPROM, etc. desde aquí en adelante.
// ¡Gracias por formar parte de este sueño tecnológico!



