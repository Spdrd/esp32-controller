#include <Adafruit_GFX.h>
#include <Adafruit_GC9A01A.h>
#include <SPI.h>
struct ScreenPinConfig
{
    int tftCsPin;
    int tftRstPin;
    int tftMisoPin;
    int tftDcPin;
    int tftMosiPin;
    int tftSclkPin;
};

class ScreenManager {
public:
    ScreenManager(ScreenPinConfig config);
    void loop();

private:
    ScreenPinConfig config;
    Adafruit_GC9A01A tft = Adafruit_GC9A01A(config.tftCsPin, config.tftDcPin, config.tftRstPin);
};

