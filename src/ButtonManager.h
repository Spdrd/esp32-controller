#ifndef BUTTON_CONTROLLER_H
#define BUTTON_CONTROLLER_H

#include <Arduino.h>

struct ButtonPinConfig
{
    int button1Pin;
    int button2Pin;
    int button3Pin;
};

struct ButtonActionCallbacks
{
    void (*onDoubleButton1Tap)() = nullptr;
    void (*onButton3)() = nullptr;
    void (*onButton2)() = nullptr;
    void (*onButton2_Button1)() = nullptr;
    void (*onButton3_Button1)() = nullptr;
    void (*onTripleTap)() = nullptr;
    void (*onQuadTap)() = nullptr;
};

// Buton actio calllback type definitions

class ButtonManager {
public:
    ButtonManager(ButtonPinConfig config);

    void begin();
    void update();

    // Callback definitions
    void onDoubleButton1Tap(void (*callback)());
    void onButton3(void (*callback)());
    void onButton2(void (*callback)());
    void onButton2_Button1(void (*callback)());
    void onButton3_Button1(void (*callback)());
    void onTripleTap(void (*callback)());
    void onQuadTap(void (*callback)());
    
    // Set all callbacks at once
    void setCallbacks(ButtonActionCallbacks callbacks);
private:
    // Pins
    ButtonPinConfig config;

    // States
    bool button1Pressed = false;
    bool button2Pressed = false;
    bool button3Pressed = false;

    bool lastButton1State = false;

    unsigned long lastDebounceTimeButton1 = 0;
    unsigned long lastButton1PressTime = 0;

    unsigned long currentTime = 0;

    int tapCountButton1 = 0;
    const unsigned long DEBOUNCE_MS = 50;
    const unsigned long TAP_TIMEOUT_MS = 400;

    // Long-press counters
    int button2HoldCounter = 0;
    int button3HoldCounter = 0;

    // Action callbacks
    void (*cbDoubleButton1Tap)() = nullptr;
    void (*cbButton3)() = nullptr;
    void (*cbButton2)() = nullptr;
    void (*cbButton3_Button1)() = nullptr;
    void (*cbButton2_Button1)() = nullptr;
    void (*cbTripleTap)() = nullptr;
    void (*cbQuadTap)() = nullptr;

    void processInputs();
    void executeActions();
};

#endif
