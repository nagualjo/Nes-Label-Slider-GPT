// NES Label GPT V3
// Donde los sueños se encuentran con la realidad... ¡y ahora también con funciones avanzadas!
// Autor: nagualjo & ChatGPT

// Código optimizado y rediseñado a partir de la V2.3

#define ST7796_DRIVER     // Controlador de la pantalla

#define TFT_WIDTH  320    // Ancho de la pantalla
#define TFT_HEIGHT 480    // Alto de la pantalla

#define TFT_MOSI  13      // Pin MOSI
#define TFT_SCLK  14      // Pin SCK
#define TFT_CS    15      // Pin CS
#define TFT_DC    2       // Pin DC/RS
#define TFT_RST   4       // Pin RESET
#define TFT_BL    32      // Pin LED (control de brillo)

#define SPI_FREQUENCY  40000000  // Frecuencia SPI

#include <TFT_eSPI.h>          // Librería para la pantalla TFT
#include <SPI.h>               // Librería SPI
#include <SD.h>                // Librería para la tarjeta SD
#include <DFRobotDFPlayerMini.h> // Librería para el módulo MP3

// Pines de conexión
#define SD_CS 5                // Pin CS para la tarjeta SD
#define MP3_RX 16              // Pin RX para el módulo MP3
#define MP3_TX 17              // Pin TX para el módulo MP3

// Configuración de la pantalla TFT
TFT_eSPI tft = TFT_eSPI();     // Usa la configuración de User_Setup.h

// Configuración del módulo MP3
HardwareSerial mp3Serial(1);   // UART1 para el módulo MP3
DFRobotDFPlayerMini mp3;

// Declaración de funciones auxiliares
uint16_t read16(File &f);
uint32_t read32(File &f);

// Función para ajustar el brillo de la pantalla
void setBrightness(int brightness) {
  if (brightness < 0) brightness = 0;       // Limitar el brillo mínimo
  if (brightness > 255) brightness = 255;   // Limitar el brillo máximo
  ledcWrite(0, brightness);                 // Ajustar el brillo usando PWM
}

// Función para mostrar una imagen BMP en la pantalla
void drawBMP(const char *filename, int x, int y) {
  File bmpFile;
  int bmpWidth, bmpHeight; // Dimensiones de la imagen
  uint8_t bmpDepth;        // Bits por píxel
  uint32_t rowSize;        // Tamaño de cada fila en bytes
  uint8_t sdbuffer[3 * 20]; // Buffer para leer datos de la SD
  uint8_t buffidx = sizeof(sdbuffer);
  bool goodBmp = false;    // Verifica si el archivo BMP es válido
  bool flip = true;        // Indica si la imagen está invertida
  int w, h, row, col;
  uint8_t r, g, b;

  // Abre el archivo BMP
  bmpFile = SD.open(filename);
  if (!bmpFile) {
    Serial.print("ERROR: No se pudo abrir el archivo ");
    Serial.println(filename);
    return;
  }

  // Verifica el encabezado del archivo BMP
  if (read16(bmpFile) == 0x4D42) { // BMP signature
    read32(bmpFile);               // Tamaño del archivo
    read32(bmpFile);               // Reservado
    uint32_t bmpImageOffset = read32(bmpFile); // Inicio de los datos de la imagen
    uint32_t headerSize = read32(bmpFile);
    bmpWidth = read32(bmpFile);
    bmpHeight = read32(bmpFile);
    if (read16(bmpFile) == 1) { // Planos
      bmpDepth = read16(bmpFile); // Bits por píxel
      if ((bmpDepth == 24) && (read32(bmpFile) == 0)) { // Solo soporta BMP de 24 bits
        goodBmp = true;
        rowSize = (bmpWidth * 3 + 3) & ~3;
        if (bmpHeight < 0) {
          bmpHeight = -bmpHeight;
          flip = false;
        }

        w = bmpWidth;
        h = bmpHeight;
        if ((x + w - 1) >= tft.width()) w = tft.width() - x;
        if ((y + h - 1) >= tft.height()) h = tft.height() - y;

        for (row = 0; row < h; row++) {
          int pos = bmpImageOffset + (flip ? (bmpHeight - 1 - row) * rowSize : row * rowSize);
          if (bmpFile.position() != pos) {
            bmpFile.seek(pos);
            buffidx = sizeof(sdbuffer);
          }

          for (col = 0; col < w; col++) {
            if (buffidx >= sizeof(sdbuffer)) {
              bmpFile.read(sdbuffer, sizeof(sdbuffer));
              buffidx = 0;
            }

            b = sdbuffer[buffidx++];
            g = sdbuffer[buffidx++];
            r = sdbuffer[buffidx++];
            tft.drawPixel(x + col, y + row, tft.color565(r, g, b));
          }
        }
      }
    }
  }

  bmpFile.close();
  if (!goodBmp) Serial.println("ERROR: Archivo BMP no válido");
}

// Funciones auxiliares para leer datos del archivo BMP
uint16_t read16(File &f) {
  uint16_t result;
  ((uint8_t *)&result)[0] = f.read(); // LSB
  ((uint8_t *)&result)[1] = f.read(); // MSB
  return result;
}

uint32_t read32(File &f) {
  uint32_t result;
  ((uint8_t *)&result)[0] = f.read(); // LSB
  ((uint8_t *)&result)[1] = f.read();
  ((uint8_t *)&result)[2] = f.read();
  ((uint8_t *)&result)[3] = f.read(); // MSB
  return result;
}

bool randomMode = false; // Variable global para activar/desactivar el modo aleatorio

// Función para alternar entre modo aleatorio y secuencial
void toggleRandomMode() {
  randomMode = !randomMode; // Alternar el estado del modo aleatorio
  if (randomMode) {
    Serial.println("Modo aleatorio activado.");
  } else {
    Serial.println("Modo secuencial activado.");
  }
}

void setup() {
  Serial.begin(115200);

  // Configurar el pin de brillo como salida PWM
  ledcSetup(0, 5000, 8); // Canal 0, frecuencia 5 kHz, resolución de 8 bits
  ledcAttachPin(TFT_BL, 0); // Asignar el pin TFT_BL al canal 0
  setBrightness(13); // Establecer un brillo inicial (50%)

  // Inicializar la pantalla
  tft.init();
  tft.setRotation(0);
  tft.fillScreen(TFT_BLACK);

  // Inicializar la tarjeta SD
  if (!SD.begin(SD_CS)) {
    Serial.println("ERROR: No se pudo inicializar la tarjeta SD");
    while (true);
  }
  Serial.println("Tarjeta SD inicializada correctamente");

  // Inicializar el módulo MP3
  mp3Serial.begin(9600, SERIAL_8N1, MP3_RX, MP3_TX);
  if (!mp3.begin(mp3Serial)) {
    Serial.println("ERROR: No se pudo inicializar el módulo MP3");
    while (true);
  }
  mp3.volume(4); // Ajustar volumen
  //mp3.play(8);    // Reproducir el primer archivo MP3
}

void loop() {
  for (int i = 1; i <= 811; i++) {
    int index;

    // Seleccionar el índice según el modo
    if (randomMode) {
      index = random(1, 812); // Generar un índice aleatorio entre 1 y 811
    } else {
      index = i; // Usar el índice secuencial
    }

    char imageFile[15]; // Buffer para el nombre de la imagen
    char audioFile[15]; // Buffer para el nombre del archivo MP3

    // Generar el nombre del archivo de audio
    sprintf(audioFile, "%d.mp3", index); // Por ejemplo, "1.mp3"
    Serial.print("Reproduciendo: ");
    Serial.println(audioFile);

    // Reproducir el archivo MP3
    mp3.play(index); // Reproduce el archivo MP3 correspondiente

    // Generar el nombre del archivo de imagen
    sprintf(imageFile, "/%d.bmp", index); // Por ejemplo, "/1.bmp"
    Serial.print("Mostrando: ");
    Serial.println(imageFile);
    drawBMP(imageFile, 0, 0); // Muestra la imagen en la pantalla

    delay(20000); // Espera 20 segundos antes de mostrar la siguiente imagen
  }
}
