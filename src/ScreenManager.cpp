#include "ScreenManager.h"

ScreenManager::ScreenManager(ScreenPinConfig cfg)
    : config(cfg), // 1. Se copia la configuración
      tft(cfg.tftCsPin, cfg.tftDcPin, cfg.tftRstPin) // 2. Se inicializa la pantalla con valores COPIADOS
{
    // Deja el cuerpo vacío, no toques el hardware aquí
}

void ScreenManager::begin() {
    Serial.println("Iniciando pantalla...");
    
    // Configuración específica de pines SPI para el ESP32-C3
    // El C3 usa por defecto: SCK=4, MISO=5, MOSI=6, SS=7
    SPI.begin(config.tftSclkPin, config.tftMisoPin, config.tftMosiPin, config.tftCsPin);
    
    tft.begin();
    tft.setRotation(135);
    
    tft.fillScreen(GC9A01A_BLACK);
    tft.setCursor(60, 110);
    tft.setTextColor(GC9A01A_GREEN);
    tft.setTextSize(2);
    tft.println("MINIMAL OK");
}

void ScreenManager::update(String text) {
    tft.fillScreen(GC9A01A_BLACK);
    tft.setCursor(10, 110);
    tft.setTextColor(GC9A01A_WHITE);
    tft.setTextSize(2);
    tft.println(text);
}