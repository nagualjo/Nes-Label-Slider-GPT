// NES Label GPT V2
// Donde los sueños se encuentran con la nostalgia... ¡y ahora también con funciones avanzadas!
// Autor: nagualjo & ChatGPT

#include <SPI.h>
#include <TFT_eSPI.h>
#include <FS.h>
#include <SPIFFS.h>
#include <SD.h>
#include <EEPROM.h>
#include <Wire.h>
#include <RTClib.h>
#include <DFRobotDFPlayerMini.h>
#include "TouchLib.h"

// --------------------------- CONFIGURACIÓN DE PINES ---------------------------
#define PIN_DFPLAYER_RX 16
#define PIN_DFPLAYER_TX 17
#define PIN_SD_CS 5
#define PIN_TFT_CS 15
#define PIN_TFT_DC 2
#define PIN_TFT_RST 4
#define PIN_TOUCH_IRQ 12
#define PIN_BACKLIGHT 32

// --------------------------- OBJETOS GLOBALES ---------------------------
TFT_eSPI tft = TFT_eSPI();
TouchLib touch(PIN_TOUCH_IRQ);
DFRobotDFPlayerMini mp3;
RTC_DS3231 rtc;

File root;
String fileList[1000];
int fileCount = 0;
int currentIndex = 0;
bool shuffleMode = false;
int brightness = 255;
int volume = 20;

unsigned long lastChange = 0;
unsigned long changeInterval = 30000;

// --------------------------- FUNCIONES DE UTILIDAD ---------------------------
void shuffleFileList() {
  for (int i = fileCount - 1; i > 0; i--) {
    int j = random(0, i + 1);
    String temp = fileList[i];
    fileList[i] = fileList[j];
    fileList[j] = temp;
  }
}

void loadFileList() {
  fileCount = 0;
  File dir = SD.open("/");
  while (true) {
    File entry = dir.openNextFile();
    if (!entry) break;
    String name = entry.name();
    if (name.endsWith(".png")) {
      fileList[fileCount++] = name;
    }
    entry.close();
  }
  dir.close();
  if (shuffleMode) shuffleFileList();
}

void drawImageAndMusic() {
  tft.fillScreen(TFT_BLACK);
  String imageFile = fileList[currentIndex];
  String musicFile = imageFile;
  musicFile.replace(".png", ".mp3");
  // Aquí iría el código para mostrar imagen y reproducir música
}

void nextMedia() {
  currentIndex = (currentIndex + 1) % fileCount;
  drawImageAndMusic();
}

void saveSettings() {
  File f = SPIFFS.open("/config.txt", FILE_WRITE);
  if (f) {
    f.printf("shuffle=%d\nbrightness=%d\nvolume=%d\n", shuffleMode, brightness, volume);
    f.close();
  }
}

void loadSettings() {
  File f = SPIFFS.open("/config.txt");
  if (f) {
    while (f.available()) {
      String line = f.readStringUntil('\n');
      if (line.startsWith("shuffle=")) shuffleMode = line.substring(8).toInt();
      if (line.startsWith("brightness=")) brightness = line.substring(11).toInt();
      if (line.startsWith("volume=")) volume = line.substring(7).toInt();
    }
    f.close();
  }
}

void showSettingsMenu() {
  tft.fillScreen(TFT_BLACK);
  tft.setCursor(20, 20);
  tft.setTextSize(2);
  tft.setTextColor(TFT_WHITE);
  tft.println("Settings Menu");

  tft.setCursor(20, 60);
  tft.printf("Brillo: %d\n", brightness);

  tft.setCursor(20, 100);
  tft.printf("Volumen: %d\n", volume);

  tft.setCursor(20, 140);
  tft.printf("Shuffle: %s\n", shuffleMode ? "ON" : "OFF");
}

void handleTouchMenu() {
  uint16_t x, y;
  if (touch.read()) {
    x = touch.getX();
    y = touch.getY();
    if (y > 130 && y < 170) {
      shuffleMode = !shuffleMode;
      saveSettings();
      showSettingsMenu();
    }
  }
}

// --------------------------- SETUP ---------------------------
void setup() {
  Serial.begin(115200);
  Wire.begin();
  SPI.begin();
  tft.init();
  tft.setRotation(1);
  touch.begin();

  pinMode(PIN_BACKLIGHT, OUTPUT);
  ledcSetup(0, 5000, 8);
  ledcAttachPin(PIN_BACKLIGHT, 0);
  ledcWrite(0, brightness);

  if (!SPIFFS.begin(true)) Serial.println("Error SPIFFS");
  if (!SD.begin(PIN_SD_CS)) Serial.println("Error SD");

  loadSettings();

  Serial2.begin(9600, SERIAL_8N1, PIN_DFPLAYER_RX, PIN_DFPLAYER_TX);
  if (!mp3.begin(Serial2)) Serial.println("DFPlayer no conectado");
  mp3.volume(volume);

  if (!rtc.begin()) Serial.println("RTC no detectado");

  loadFileList();
  drawImageAndMusic();
  lastChange = millis();
}

// --------------------------- LOOP PRINCIPAL ---------------------------
void loop() {
  handleTouchMenu();

  if (millis() - lastChange > changeInterval) {
    nextMedia();
    lastChange = millis();
  }
}
