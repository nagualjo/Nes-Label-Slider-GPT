// NES Label GPT V3.1
// Donde los sueños se encuentran con la realidad... ¡y ahora también con funciones avanzadas!
// Autor: nagualjo & ChatGPT Copilot GPT 4.1

#define ST7796_DRIVER

#define TFT_WIDTH  320
#define TFT_HEIGHT 480

#define TFT_MOSI  13
#define TFT_SCLK  14
#define TFT_CS    15
#define TFT_DC    2
#define TFT_RST   4
#define TFT_BL    32

#define SPI_FREQUENCY  40000000

#include <TFT_eSPI.h>
#include <SPI.h>
#include <SD.h>
#include <DFRobotDFPlayerMini.h>

// Pines de conexión
#define SD_CS 5
#define MP3_RX 16
#define MP3_TX 17

TFT_eSPI tft = TFT_eSPI();
HardwareSerial mp3Serial(1);
DFRobotDFPlayerMini mp3;

// Variables para reanudar desde el menú
int resumeImageIndex = 1;
bool resumeFromMenu = false;

// Declaración de funciones auxiliares
uint16_t read16(File &f);
uint32_t read32(File &f);
void setBrightness(int brightness);
void selectSD();
void selectTFT();
void drawBMP(const char *filename, int x, int y);
void toggleRandomMode();
void showBrightnessMenu();
void showVolumeMenu();

// 1. Animación de barrido al entrar al menú
void retroWipe() {
  selectTFT();
  for (int y = 0; y < 480; y += 8) {
    tft.drawFastHLine(0, y, 320, TFT_GREEN);
    delay(2); // Ajusta la velocidad del barrido
  }
}

// 2. Mensajes de bienvenida tipo BIOS (rotativos)
const char* biosMessages[] = {
  "Nes Label GPT v3.0 - Ready",
  "640K OK",
  "Booting..."
};
int biosMsgIndex = 0;
unsigned long lastBiosMsg = 0;

// 3. Indicador de actividad (LED verde parpadeante)
bool activityLedOn = false;
unsigned long lastLedBlink = 0;

// 4. Opciones de menú con selección
const char* menuOptions[] = {"Desordenar Juegos", "BRILLO", "VOLUMEN"};
int menuSelected = 0;
const int menuOptionCount = 3;

// --- Menú básico ---
void drawBasicMenu() {
  selectTFT();
  tft.fillScreen(TFT_BLACK);

  // Marco verde doble retro
  tft.drawRect(0, 0, 320, 480, TFT_GREEN);
  tft.drawRect(2, 2, 316, 476, TFT_GREEN);

  // Mensaje BIOS rotativo
  tft.setTextColor(TFT_GREEN, TFT_BLACK);
  tft.setTextSize(1);
  tft.setCursor(10, 20);
  tft.println(biosMessages[biosMsgIndex]);

  // Indicador de actividad (LED verde parpadeante)
  if (activityLedOn) {
    tft.fillRect(300, 10, 10, 10, TFT_GREEN);
  } else {
    tft.fillRect(300, 10, 10, 10, TFT_DARKGREY);
  }

  // Titulo de menú
  tft.setTextSize(3);
  tft.setTextColor(TFT_GREEN, TFT_BLACK);
  tft.setCursor(100, 60); // Centrado aproximado para "MENU"
  tft.println("MENU");

  // Opciones de menú con selección
  tft.setTextSize(2);
  int yOpt = 160;
  for (int i = 0; i < menuOptionCount; i++) {
    if (i == menuSelected) {
      tft.fillRect(30, yOpt - 4, 260, 28, TFT_GREEN);
      tft.setTextColor(TFT_BLACK, TFT_GREEN);
      tft.setCursor(40, yOpt);
      tft.print(">");
      tft.setCursor(70, yOpt);
      tft.println(menuOptions[i]);
    } else {
      tft.setTextColor(TFT_GREEN, TFT_BLACK);
      tft.setCursor(70, yOpt);
      tft.println(menuOptions[i]);
    }
    yOpt += 40;
  }

  // Botón VOLVER (toda la parte inferior, negro con marco verde)
  tft.fillRect(0, 380, 320, 100, TFT_BLACK);
  tft.drawRect(0, 380, 320, 100, TFT_GREEN);   // Marco exterior
  tft.drawRect(2, 382, 316, 96, TFT_GREEN);    // Marco interior

  tft.setTextColor(TFT_GREEN, TFT_BLACK);
  tft.setTextSize(3);
  tft.setCursor(100, 420);
  tft.println("VOLVER");
}

void waitForTouchRelease() {
  uint16_t x, y;
  while (tft.getTouch(&x, &y)) delay(10);
}

// --- Manejo del menú ---
void showBasicMenu() {
  retroWipe();
  drawBasicMenu();
  waitForTouchRelease();
  bool inMenu = true;
  bool cursorOn = false;
  unsigned long lastBlink = millis();
  lastBiosMsg = millis();
  lastLedBlink = millis();
  while (inMenu) {
    uint16_t x, y;

    // 2. Cambia mensaje BIOS cada 2 segundos (solo esa zona)
    if (millis() - lastBiosMsg > 2000) {
      biosMsgIndex = (biosMsgIndex + 1) % 3;
      tft.setTextColor(TFT_GREEN, TFT_BLACK);
      tft.setTextSize(1);
      tft.fillRect(10, 20, 200, 12, TFT_BLACK); // Borra solo la zona del mensaje
      tft.setCursor(10, 20);
      tft.println(biosMessages[biosMsgIndex]);
      lastBiosMsg = millis();
    }

    // 3. Parpadeo del LED de actividad cada 500 ms (solo esa zona)
    if (millis() - lastLedBlink > 500) {
      activityLedOn = !activityLedOn;
      if (activityLedOn) {
        tft.fillRect(300, 10, 10, 10, TFT_GREEN);
      } else {
        tft.fillRect(300, 10, 10, 10, TFT_DARKGREY);
      }
      lastLedBlink = millis();
    }

    // 4. Selección de menú por touch (igual que antes)
    if (tft.getTouch(&x, &y)) {
      for (int i = 0; i < menuOptionCount; i++) {
        int yOpt = 160 + i * 40;
        if (y >= yOpt - 4 && y <= yOpt + 24) {
          menuSelected = i;
          drawBasicMenu(); // Solo aquí se redibuja todo para resaltar la opción
          if (strcmp(menuOptions[i], "Desordenar Juegos") == 0) {
            toggleRandomMode();
            waitForTouchRelease();
          } else if (strcmp(menuOptions[i], "BRILLO") == 0) {
            waitForTouchRelease();
            showBrightnessMenu();
            drawBasicMenu(); // Redibuja el menú principal al volver
          } else if (strcmp(menuOptions[i], "VOLUMEN") == 0) {
            waitForTouchRelease();
            showVolumeMenu();
            drawBasicMenu(); // Redibuja el menú principal al volver
          }
        }
      }
      // Botón grande VOLVER (parte inferior)
      if (x >= 0 && x < 320 && y >= 380 && y < 480) {
        waitForTouchRelease();
        inMenu = false;
      }
    }
  }
}

// Función para ajustar el brillo de la pantalla
void setBrightness(int brightness) {
  if (brightness < 0) brightness = 0;
  if (brightness > 255) brightness = 255;
  ledcWrite(0, brightness);
}

// Funciones para controlar el pin CS
void selectSD() {
  digitalWrite(TFT_CS, HIGH);
  digitalWrite(SD_CS, LOW);
}

void selectTFT() {
  digitalWrite(SD_CS, HIGH);
  digitalWrite(TFT_CS, LOW);
}

// Función para mostrar una imagen BMP en la pantalla
void drawBMP(const char *filename, int x, int y) {
  File bmpFile;
  int bmpWidth, bmpHeight;
  uint8_t bmpDepth;
  uint32_t rowSize;
  uint8_t sdbuffer[3 * 20];
  uint8_t buffidx = sizeof(sdbuffer);
  bool goodBmp = false;
  bool flip = true;
  int w, h, row, col;
  uint8_t r, g, b;

  selectSD();
  bmpFile = SD.open(filename);
  if (!bmpFile) {
    Serial.print("ERROR: No se pudo abrir el archivo ");
    Serial.println(filename);
    return;
  }

  selectTFT();

  if (read16(bmpFile) == 0x4D42) {
    read32(bmpFile);
    read32(bmpFile);
    uint32_t bmpImageOffset = read32(bmpFile);
    uint32_t headerSize = read32(bmpFile);
    bmpWidth = read32(bmpFile);
    bmpHeight = read32(bmpFile);
    if (read16(bmpFile) == 1) {
      bmpDepth = read16(bmpFile);
      if ((bmpDepth == 24) && (read32(bmpFile) == 0)) {
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
  ((uint8_t *)&result)[0] = f.read();
  ((uint8_t *)&result)[1] = f.read();
  return result;
}

uint32_t read32(File &f) {
  uint32_t result;
  ((uint8_t *)&result)[0] = f.read();
  ((uint8_t *)&result)[1] = f.read();
  ((uint8_t *)&result)[2] = f.read();
  ((uint8_t *)&result)[3] = f.read();
  return result;
}

bool randomMode = false;

// Función para alternar entre modo aleatorio y secuencial
void toggleRandomMode() {
  randomMode = !randomMode;
  if (randomMode) {
    Serial.println("Modo aleatorio activado.");
  } else {
    Serial.println("Modo secuencial activado.");
  }
}

// Función para mostrar el menú de ajuste de brillo
void showBrightnessMenu() {
  int brillo = 128; // O lee el valor actual si tienes variable global
  bool inSubMenu = true;
  while (inSubMenu) {
    selectTFT();
    tft.fillScreen(TFT_BLACK);
    tft.drawRect(0, 0, 320, 480, TFT_GREEN);
    tft.drawRect(2, 2, 316, 476, TFT_GREEN);

    tft.setTextColor(TFT_GREEN, TFT_BLACK);
    tft.setTextSize(2);
    tft.setCursor(60, 40);
    tft.println("AJUSTAR BRILLO");

    // Botones y valor
    tft.setTextSize(4);
    tft.setCursor(40, 200);
    tft.print("-");
    tft.setCursor(140, 200);
    tft.printf("%3d", brillo);
    tft.setCursor(240, 200);
    tft.print("+");

    // Botón VOLVER
    tft.setTextSize(2);
    tft.setCursor(100, 400);
    tft.println("VOLVER");

    // Espera touch
    uint16_t x, y;
    while (!tft.getTouch(&x, &y)) delay(10);

    // [ - ] botón
    if (x > 40 && x < 100 && y > 200 && y < 260 && brillo > 0) {
      brillo -= 8;
      setBrightness(brillo);
    }
    // [ + ] botón
    else if (x > 240 && x < 300 && y > 200 && y < 260 && brillo < 255) {
      brillo += 8;
      setBrightness(brillo);
    }
    // VOLVER
    else if (y > 400 && y < 440) {
      inSubMenu = false;
    }
    waitForTouchRelease();
  }
}

// Función para mostrar el menú de ajuste de volumen
void showVolumeMenu() {
  int volumen = mp3.readVolume(); // O usa tu variable de volumen
  bool inSubMenu = true;
  while (inSubMenu) {
    selectTFT();
    tft.fillScreen(TFT_BLACK);
    tft.drawRect(0, 0, 320, 480, TFT_GREEN);
    tft.drawRect(2, 2, 316, 476, TFT_GREEN);

    tft.setTextColor(TFT_GREEN, TFT_BLACK);
    tft.setTextSize(2);
    tft.setCursor(60, 40);
    tft.println("AJUSTAR VOLUMEN");

    // Botones y valor
    tft.setTextSize(4);
    tft.setCursor(40, 200);
    tft.print("-");
    tft.setCursor(140, 200);
    tft.printf("%3d", volumen);
    tft.setCursor(240, 200);
    tft.print("+");

    // Botón VOLVER
    tft.setTextSize(2);
    tft.setCursor(100, 400);
    tft.println("VOLVER");

    // Espera touch
    uint16_t x, y;
    while (!tft.getTouch(&x, &y)) delay(10);

    // [ - ] botón
    if (x > 40 && x < 100 && y > 200 && y < 260 && volumen > 0) {
      volumen -= 1;
      mp3.volume(volumen);
    }
    // [ + ] botón
    else if (x > 240 && x < 300 && y > 200 && y < 260 && volumen < 30) {
      volumen += 1;
      mp3.volume(volumen);
    }
    // VOLVER
    else if (y > 400 && y < 440) {
      inSubMenu = false;
    }
    waitForTouchRelease();
  }
}

void setup() {
  Serial.begin(115200);

  pinMode(SD_CS, OUTPUT);
  pinMode(TFT_CS, OUTPUT);
  digitalWrite(SD_CS, HIGH);
  digitalWrite(TFT_CS, HIGH);

  ledcSetup(0, 5000, 8);
  ledcAttachPin(TFT_BL, 0);
  setBrightness(128);

  Serial.println("Inicializando pantalla...");
  selectTFT();
  tft.init();
  tft.setRotation(0);
  tft.fillScreen(TFT_BLACK);
  Serial.println("Pantalla inicializada correctamente");

  Serial.println("Inicializando tarjeta SD...");
  selectSD();
  if (!SD.begin(SD_CS)) {
    Serial.println("ERROR: No se pudo inicializar la tarjeta SD");
    while (true);
  }
  Serial.println("Tarjeta SD inicializada correctamente");

  Serial.println("Inicializando módulo MP3...");
  mp3Serial.begin(9600, SERIAL_8N1, MP3_RX, MP3_TX);
  if (!mp3.begin(mp3Serial)) {
    Serial.println("ERROR: No se pudo inicializar el módulo MP3");
    while (true);
  }
  mp3.volume(4);
  Serial.println("Módulo MP3 inicializado correctamente");
}

void loop() {
  int startIndex = 1;
  if (resumeFromMenu) {
    startIndex = resumeImageIndex;
    resumeFromMenu = false;
  }
  for (int i = startIndex; i <= 811; i++) {
    int index;
    uint16_t x, y;

    // Seleccionar el índice según el modo
    if (randomMode) {
      index = random(1, 812);
    } else {
      index = i;
    }

    char imageFile[15];
    char audioFile[15];

    sprintf(audioFile, "%d.mp3", index);
    Serial.print("Reproduciendo: ");
    Serial.println(audioFile);

    mp3.play(index);

    sprintf(imageFile, "/%d.bmp", index);
    Serial.print("Mostrando: ");
    Serial.println(imageFile);
    drawBMP(imageFile, 0, 0);

    // Espera 20 segundos o permite salir antes si se detecta un toque normal
    unsigned long start = millis();
    while (millis() - start < 20000) {
      if (tft.getTouch(&x, &y)) {
        Serial.println("TOUCH detectado, mostrando menú...");
        resumeImageIndex = i;
        resumeFromMenu = true;
        showBasicMenu();
        waitForTouchRelease();
        return; // <-- Esto es clave: termina el loop aquí
      }
      delay(10);
    }
  }
}
