#include <TFT_eSPI.h>       // Pantalla ST7796
#include <SPI.h>
#include <SD.h>
#include <SoftwareSerial.h>
#include <DFRobotDFPlayerMini.h>

TFT_eSPI tft = TFT_eSPI();  // TFT instance

// Pines SD (ya definidos en TFT_eSPI)
#define SD_CS    5

// Pines DFPlayer
#define MP3_RX   16
#define MP3_TX   17
SoftwareSerial mp3Serial(MP3_RX, MP3_TX);
DFRobotDFPlayerMini mp3;

unsigned long lastChange = 0;
const unsigned long delayTime = 30000; // 30 segundos
int index = 0;
bool randomMode = false;

void setup() {
  Serial.begin(115200);
  tft.init();
  tft.setRotation(1);
  tft.fillScreen(TFT_BLACK);
  
  // SD
  if (!SD.begin(SD_CS)) {
    tft.println("SD Card Error!");
    while (true);
  }
  tft.println("SD OK");

  // MP3
  mp3Serial.begin(9600);
  if (!mp3.begin(mp3Serial)) {
    tft.println("MP3 Error!");
    while (true);
  }
  mp3.volume(20); // Volumen entre 0 - 30
  tft.println("MP3 OK");

  showImageAndPlay(index);
  lastChange = millis();
}

void loop() {
  if (millis() - lastChange > delayTime) {
    index++;
    showImageAndPlay(index);
    lastChange = millis();
  }

  // Aquí se incluirá detección de toque en el futuro
}

void showImageAndPlay(int id) {
  String filename = "/"+String(id)+".bmp";
  tft.fillScreen(TFT_BLACK);
  drawBmp(filename.c_str(), 0, 0);

  mp3.play(id); // Reproduce canción número N
}

// Función para mostrar imagen BMP
void drawBmp(const char *filename, int16_t x, int16_t y) {
  File bmp = SD.open(filename);
  if (!bmp) return;
  
  // Saltar cabecera BMP de 54 bytes
  bmp.seek(54);

  uint16_t w = 320, h = 240; // Ajusta según tu pantalla
  tft.setSwapBytes(true);
  tft.pushImage(x, y, w, h, (uint16_t*)bmp.read(w * h * 2));
  bmp.close();
}
