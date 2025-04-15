// NES Label GPT V2.1
// Donde los sueños se encuentran con la realidad... ¡y ahora también con funciones avanzadas!
// Autor: nagualjo & ChatGPT



#include <Arduino.h>
#include <SPI.h>
#include <SD.h>
#include <TFT_eSPI.h>
#include <JPEGDecoder.h>
#include <TouchScreen.h>
#include <EEPROM.h>
#include <DFMiniMp3.h>
#include <WiFi.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <RTClib.h>

// --- Configuración de Pines y Objetos ---
TFT_eSPI tft = TFT_eSPI();
TouchScreen ts = TouchScreen(); // Ajusta según tu hardware

#define PIN_MP3_RX 16
#define PIN_MP3_TX 17
#define PIN_SD_CS 5
#define PIN_PWM_BACKLIGHT 32
#define PIN_TOUCH_IRQ 12

// --- Variables Globales ---
int brillo = 128;              // Valor PWM 0-255
int volumen = 20;              // Valor 0-30
int tiempoEspera = 30;         // En segundos
bool modoAleatorio = false;
bool mostrarReloj = false;

// --- Variables para imágenes y música ---
std::vector<String> archivosImagenes;
int indiceActual = 0;
unsigned long ultimoCambio = 0;
bool enMenu = false;

// --- Configuración EEPROM ---
struct Configuracion {
  int brillo;
  int volumen;
  int tiempoEspera;
  bool modoAleatorio;
  bool mostrarReloj;
};

Configuracion config;

// --- Inicialización del PWM para brillo ---
void configurarBrilloPWM() {
  ledcSetup(0, 5000, 8);
  ledcAttachPin(PIN_PWM_BACKLIGHT, 0);
  ledcWrite(0, brillo);
}

// --- Guardar y cargar configuración ---
void guardarConfiguracion() {
  EEPROM.put(0, config);
  EEPROM.commit();
}

void cargarConfiguracion() {
  EEPROM.get(0, config);
  brillo = config.brillo;
  volumen = config.volumen;
  tiempoEspera = config.tiempoEspera;
  modoAleatorio = config.modoAleatorio;
  mostrarReloj = config.mostrarReloj;
}

// --- Función para mezclar los archivos si está activo modo aleatorio ---
void mezclarArchivos() {
  if (!modoAleatorio) return;
  for (int i = archivosImagenes.size() - 1; i > 0; i--) {
    int j = random(i + 1);
    std::swap(archivosImagenes[i], archivosImagenes[j]);
  }
}

// --- Cargar archivos desde SD ---
void cargarArchivos() {
  File dir = SD.open("/");
  archivosImagenes.clear();
  while (true) {
    File entry = dir.openNextFile();
    if (!entry) break;
    String name = entry.name();
    if (name.endsWith(".png")) archivosImagenes.push_back(name);
    entry.close();
  }
  mezclarArchivos();
}

// --- Mostrar imagen en pantalla ---
void mostrarImagen(String filename) {
  tft.fillScreen(TFT_BLACK);
  tft.drawString("Mostrando: " + filename, 10, 10); // Sustituir con renderizado real
  // Código de carga real del PNG omitido aquí por brevedad
}

// --- Reproducir música ---
void reproducirMusica(String filename) {
  // Asume que el nombre del archivo MP3 coincide con el PNG
  // mp3.play(filename);
}

// --- Dibujar menú táctil interactivo ---
void mostrarMenuConfiguracion() {
  enMenu = true;
  tft.fillScreen(TFT_NAVY);
  tft.setTextColor(TFT_WHITE);
  tft.setTextSize(2);
  tft.drawString("Configuracion NES Label GPT", 20, 10);

  // Botones de brillo
  tft.drawString("Brillo -", 20, 50);
  tft.drawString("Brillo +", 150, 50);

  // Botones de volumen
  tft.drawString("Volumen -", 20, 90);
  tft.drawString("Volumen +", 150, 90);

  // Botón de modo aleatorio
  tft.drawString(modoAleatorio ? "Aleatorio: ON" : "Aleatorio: OFF", 20, 130);

  // Botón salir
  tft.drawString("Salir", 20, 180);
}

// --- Manejar interacción táctil en menú ---
void manejarToqueMenu(int x, int y) {
  if (y > 50 && y < 70) {
    if (x < 100) brillo = max(0, brillo - 20);
    else brillo = min(255, brillo + 20);
  } else if (y > 90 && y < 110) {
    if (x < 100) volumen = max(0, volumen - 1);
    else volumen = min(30, volumen + 1);
  } else if (y > 130 && y < 150) {
    modoAleatorio = !modoAleatorio;
  } else if (y > 180 && y < 200) {
    // Guardar y salir del menú
    config.brillo = brillo;
    config.volumen = volumen;
    config.modoAleatorio = modoAleatorio;
    guardarConfiguracion();
    configurarBrilloPWM();
    cargarArchivos();
    enMenu = false;
  }
  if (enMenu) mostrarMenuConfiguracion();
}

// --- Setup ---
void setup() {
  Serial.begin(115200);
  EEPROM.begin(512);
  cargarConfiguracion();
  configurarBrilloPWM();

  tft.begin();
  tft.setRotation(1);
  SD.begin(PIN_SD_CS);
  cargarArchivos();
  mostrarMenuConfiguracion();
}

// --- Loop principal ---
void loop() {
  if (enMenu) {
    if (ts.touched()) {
      TSPoint p = ts.getPoint();
      manejarToqueMenu(p.x, p.y);
    }
    delay(100);
    return;
  }

  if (millis() - ultimoCambio > (tiempoEspera * 1000)) {
    mostrarImagen(archivosImagenes[indiceActual]);
    reproducirMusica(archivosImagenes[indiceActual]);
    indiceActual = (indiceActual + 1) % archivosImagenes.size();
    ultimoCambio = millis();
  }
}  
