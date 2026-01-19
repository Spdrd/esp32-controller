#include "ScreenManager.h"

ScreenManager::ScreenManager(ScreenPinConfig config) : config(config) {delay(1000);

    // Configuramos el bus SPI con tus pines elegidos
    SPI.begin(config.tftSclkPin, config.tftMisoPin, config.tftMosiPin, -1); 

    Serial.println("Iniciando con configuración mínima...");
    
    tft.begin();
    tft.setRotation(135);
    
    // Test visual
    tft.fillScreen(GC9A01A_BLACK);
    tft.setCursor(60, 110);
    tft.setTextColor(GC9A01A_GREEN);
    tft.setTextSize(2);
    tft.println("MINIMAL OK");
}



void ScreenManager::loop() {
    tft.invertDisplay(true);
    delay(500);
    tft.invertDisplay(false);
    delay(500);
}