// NES Label GPT V2.2 - Código optimizado y preparado para expansión RTC
// Donde los sueños se encuentran con la realidad… ¡y ahora también con funciones avanzadas!
// Autor: nagualjo & ChatGPT

#include <TFT_eSPI.h>
#include <SPI.h>
#include <FS.h>
#include <SD.h>
#include <EEPROM.h>
#include <DFRobotDFPlayerMini.h>
#include <XPT2046_Touchscreen.h>

// -------------------------
// CONFIGURACIÓN DE PINES
// -------------------------

// MP3
#define PIN_MP3_RX 16
#define PIN_MP3_TX 17

// SD
#define PIN_SD_CS 5

// TOUCH
#define PIN_TOUCH_CS 21   // T_CS real del chip táctil
#define PIN_TOUCH_IRQ 12  // T_IRQ: interrupción del touch

// BRILLO TFT
#define PIN_BRIGHTNESS 32

// RTC (a integrar próximamente)
#define PIN_RTC_SCL 22
#define PIN_RTC_SDA 25

// Dimensiones pantalla
#define SCREEN_WIDTH 480
#define SCREEN_HEIGHT 320

// -------------------------
// INSTANCIAS DE OBJETOS
// -------------------------

TFT_eSPI tft = TFT_eSPI();
HardwareSerial mp3Serial(1);
DFRobotDFPlayerMini mp3;
XPT2046_Touchscreen touch(PIN_TOUCH_CS, PIN_TOUCH_IRQ); // Corrección aplicada

// -------------------------
// VARIABLES GLOBALES
// -------------------------

int currentIndex = 0;
int numFiles = 0;
int delayTime = 30000;
bool shuffleMode = false;
bool showClock = false;
int volume = 20;
int brightness = 200;

String fileList[1000];
unsigned long lastChange = 0;
bool showMenu = false;

// -------------------------
// PROTOTIPOS DE FUNCIONES
// -------------------------

void loadFileList();
void shuffleFileList();
void drawMenu();
void handleTouch();
void showImage(String filename);
void playMusic(String filename);
void saveConfig();
void loadConfig();
void setBrightness(int val);
void drawButtons();

// -------------------------
// SETUP
// -------------------------

void setup() {
  Serial.begin(115200);
  EEPROM.begin(512);
  tft.begin();
  tft.setRotation(1);
  tft.fillScreen(TFT_BLACK);

  // PWM para control de brillo
  pinMode(PIN_BRIGHTNESS, OUTPUT);
  ledcSetup(0, 5000, 8);
  ledcAttachPin(PIN_BRIGHTNESS, 0);
  setBrightness(brightness);

  // Inicializar SD
  if (!SD.begin(PIN_SD_CS)) {
    tft.println("Fallo en la SD");
    return;
  }

  // Inicializar MP3
  mp3Serial.begin(9600, SERIAL_8N1, PIN_MP3_RX, PIN_MP3_TX);
  if (mp3.begin(mp3Serial)) {
    mp3.volume(volume);
  }

  // Inicializar Touch
  touch.begin();

  // Cargar configuración y lista de archivos
  loadConfig();
  loadFileList();
  if (shuffleMode) shuffleFileList();

  // Mensaje de bienvenida
  tft.fillScreen(TFT_BLACK);
  tft.setTextSize(2);
  tft.setTextColor(TFT_GREEN);
  tft.setCursor(10, 10);
  tft.println("NES Label GPT V2");
  delay(2000);
  tft.fillScreen(TFT_BLACK);
}

// -------------------------
// LOOP PRINCIPAL
// -------------------------

void loop() {
  handleTouch();

  if (showMenu) {
    drawMenu();
    delay(100);
    return;
  }

  if (millis() - lastChange > delayTime) {
    String base = fileList[currentIndex];
    showImage("/covers/" + base + ".png");
    playMusic("/music/" + base + ".mp3");

    currentIndex++;
    if (currentIndex >= numFiles) currentIndex = 0;
    lastChange = millis();
  }
}

// -------------------------
// FUNCIONES CLAVE
// -------------------------

void loadFileList() {
  File root = SD.open("/covers");
  numFiles = 0;
  while (true) {
    File entry = root.openNextFile();
    if (!entry) break;
    String name = entry.name();
    if (name.endsWith(".png")) {
      name.replace("/covers/", "");
      name.replace(".png", "");
      fileList[numFiles++] = name;
    }
    entry.close();
  }
}

void shuffleFileList() {
  for (int i = numFiles - 1; i > 0; i--) {
    int j = random(0, i + 1);
    String temp = fileList[i];
    fileList[i] = fileList[j];
    fileList[j] = temp;
  }
}

void showImage(String filename) {
  tft.fillScreen(TFT_BLACK);
  tft.setCursor(20, 150);
  tft.println("Mostrando: " + filename);
}

void playMusic(String filename) {
  mp3.stop();
  mp3.playMp3Folder(filename.c_str());
}

void handleTouch() {
  if (touch.touched()) {
    TS_Point p = touch.getPoint();
    if (p.x < 100 && p.y < 100) {
      showMenu = !showMenu;
      delay(500);
    }
  }
}

void drawMenu() {
  tft.fillScreen(TFT_DARKGREY);
  drawButtons();
}

void drawButtons() {
  tft.fillRect(20, 20, 200, 40, TFT_BLUE);
  tft.setCursor(30, 30);
  tft.setTextColor(TFT_WHITE);
  tft.print("Brillo: "); tft.print(brightness);

  tft.fillRect(20, 70, 200, 40, TFT_GREEN);
  tft.setCursor(30, 80);
  tft.print("Volumen: "); tft.print(volume);

  tft.fillRect(20, 120, 200, 40, TFT_RED);
  tft.setCursor(30, 130);
  tft.print("Aleatorio: "); tft.print(shuffleMode ? "Sí" : "No");
}

void saveConfig() {
  EEPROM.write(0, shuffleMode);
  EEPROM.write(1, volume);
  EEPROM.write(2, brightness);
  EEPROM.commit();
}

void loadConfig() {
  shuffleMode = EEPROM.read(0);
  volume = EEPROM.read(1);
  brightness = EEPROM.read(2);
}

void setBrightness(int val) {
  ledcWrite(0, val);
}
