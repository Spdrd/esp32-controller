// ScreenManager.cpp

#include "ScreenManager.h"

static ScreenManager* screenInstance = nullptr;

// =====================================================
// CALLBACK JPEG
// =====================================================

bool tftOutput(
    int16_t x,
    int16_t y,
    uint16_t w,
    uint16_t h,
    uint16_t* bitmap
) {

    if (screenInstance == nullptr) {
        return false;
    }

    screenInstance->tft.drawRGBBitmap(
        x,
        y,
        bitmap,
        w,
        h
    );

    return true;
}

// =====================================================
// CONSTRUCTOR
// =====================================================

ScreenManager::ScreenManager(ScreenPinConfig cfg)
    : config(cfg),
      tft(cfg.tftCsPin, cfg.tftDcPin, cfg.tftRstPin)
{
}

// =====================================================
// BEGIN
// =====================================================

void ScreenManager::begin() {

    Serial.println("Iniciando pantalla...");

    SPI.begin(
        config.tftSclkPin,
        -1,
        config.tftMosiPin,
        config.tftCsPin
    );

    tft.begin();

    tft.setRotation(3);

    tft.fillScreen(GC9A01A_BLACK);

    tft.setCursor(60, 110);
    tft.setTextColor(GC9A01A_GREEN);
    tft.setTextSize(2);

    tft.println("MINIMAL OK");

    // =====================================
    // JPEG DECODER
    // =====================================

    screenInstance = this;

    TJpgDec.setCallback(tftOutput);

    // Opcional:
    TJpgDec.setJpgScale(1);

    Serial.println("JPEG decoder listo");
}

// =====================================================
// UPDATE
// =====================================================

void ScreenManager::update(String text) {

    tft.fillScreen(GC9A01A_BLACK);

    tft.setCursor(10, 110);

    tft.setTextColor(GC9A01A_WHITE);

    tft.setTextSize(2);

    tft.println(text);
}

// =====================================================
// CLEAR
// =====================================================

void ScreenManager::clear() {

    tft.fillScreen(GC9A01A_BLACK);
}

// =====================================================
// SHOW JPEG
// =====================================================

void ScreenManager::showJpeg(
    uint8_t* jpgBuffer,
    uint32_t jpgSize,
    int jpg_w,
    int jpg_h
) {

    if (jpgBuffer == nullptr || jpgSize == 0) {

        Serial.println("JPEG invalido");

        return;
    }

    // =========================================
    // CENTRADO AUTOMATICO
    // =========================================

    int posX = (tft.width()  - jpg_w) / 2;
    int posY = (tft.height() - jpg_h) / 2;

    // Evita coordenadas negativas
    if (posX < 0) posX = 0;
    if (posY < 0) posY = 0;

    // =========================================
    // LIMPIAR PANTALLA
    // =========================================

    tft.fillScreen(GC9A01A_BLACK);

    // =========================================
    // DIBUJAR JPEG
    // =========================================

    TJpgDec.drawJpg(
        posX,
        posY,
        jpgBuffer,
        jpgSize
    );

    // =========================================
    // DEBUG
    // =========================================

    Serial.println("JPEG mostrado");

    Serial.print("Width: ");
    Serial.println(jpg_w);

    Serial.print("Height: ");
    Serial.println(jpg_h);

    Serial.print("X: ");
    Serial.println(posX);

    Serial.print("Y: ");
    Serial.println(posY);
}