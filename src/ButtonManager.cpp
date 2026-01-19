#include "ButtonManager.h"


ButtonManager::ButtonManager(ButtonPinConfig config) : config(config) {}

void ButtonManager::begin() {
    pinMode(config.button1Pin, INPUT_PULLUP);
    pinMode(config.button2Pin, INPUT_PULLUP);
    pinMode(config.button3Pin, INPUT_PULLUP);
}

void ButtonManager::update() {
    currentTime = millis();
    processInputs();
    executeActions();
}

void ButtonManager::processInputs() {
    bool currentButton1 = digitalRead(config.button1Pin) == LOW;
    button2Pressed = digitalRead(config.button2Pin) == LOW;
    button3Pressed = digitalRead(config.button3Pin) == LOW;

    if (currentButton1 != lastButton1State) {
        lastDebounceTimeButton1 = currentTime;
    }

    if ((currentTime - lastDebounceTimeButton1) > DEBOUNCE_MS) {
        if (currentButton1 != button1Pressed) {
            button1Pressed = currentButton1;

            if (button1Pressed) {
                tapCountButton1++;
                lastButton1PressTime = currentTime;
            }
        }
    }

    lastButton1State = currentButton1;

    if (!button3Pressed) button3HoldCounter = 0;
    if (!button2Pressed) button2HoldCounter = 0;
}

void ButtonManager::executeActions() {
    if (button1Pressed && button2Pressed) {
        if (cbButton2_Button1) cbButton2_Button1();
        tapCountButton1 = 0;
        lastButton1PressTime = 0;
        return;
    }

    if (button1Pressed && button3Pressed) {
        if (cbButton3_Button1) cbButton3_Button1();
        tapCountButton1 = 0;
        lastButton1PressTime = 0;
        return;
    }

    if (button2Pressed && !button1Pressed) {
        if (cbButton2) cbButton2();
        tapCountButton1 = 0;
        lastButton1PressTime = 0;
        return;
    }

    if (button3Pressed && !button1Pressed) {
        if (cbButton3) cbButton3();
        tapCountButton1 = 0;
        lastButton1PressTime = 0;
        return;
    }

    if (!button1Pressed &&
        tapCountButton1 > 0 &&
        (currentTime - lastButton1PressTime > TAP_TIMEOUT_MS)) {

        if (tapCountButton1 == 2 && cbDoubleButton1Tap) cbDoubleButton1Tap();
        else if (tapCountButton1 == 3 && cbTripleTap) cbTripleTap();
        else if (tapCountButton1 == 4 && cbQuadTap) cbQuadTap();

        tapCountButton1 = 0;
    }
}

/* ---------------- Callback setters ---------------- */

void ButtonManager::setCallbacks(ButtonActionCallbacks callbacks) {
    cbDoubleButton1Tap = callbacks.onDoubleButton1Tap;
    cbButton3 = callbacks.onButton3;
    cbButton2 = callbacks.onButton2;
    cbButton2_Button1 = callbacks.onButton2_Button1;
    cbButton3_Button1 = callbacks.onButton3_Button1;
    cbTripleTap = callbacks.onTripleTap;
    cbQuadTap = callbacks.onQuadTap;
}

void ButtonManager::onDoubleButton1Tap(void (*callback)()) { cbDoubleButton1Tap = callback; }
void ButtonManager::onButton3(void (*callback)()) { cbButton3 = callback; }
void ButtonManager::onButton2(void (*callback)()) { cbButton2 = callback; }
void ButtonManager::onButton2_Button1(void (*callback)()) { cbButton2_Button1 = callback; }
void ButtonManager::onButton3_Button1(void (*callback)()) { cbButton3_Button1 = callback; }
void ButtonManager::onTripleTap(void (*callback)()) { cbTripleTap = callback; }
void ButtonManager::onQuadTap(void (*callback)()) { cbQuadTap = callback; }
