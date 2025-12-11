#include "Button_controller.h"

ButtonController::ButtonController(int button1Pin, int button2Pin, int button3Pin)
    : button1Pin(button1Pin), button2Pin(button2Pin), button3Pin(button3Pin) {}

void ButtonController::begin() {
    pinMode(button1Pin, INPUT_PULLUP);
    pinMode(button2Pin, INPUT_PULLUP);
    pinMode(button3Pin, INPUT_PULLUP);
}

void ButtonController::update() {
    currentTime = millis();
    processInputs();
    executeActions();
}

void ButtonController::processInputs() {
    bool currentButton1 = digitalRead(button1Pin) == LOW;
    button2Pressed = digitalRead(button2Pin) == LOW;
    button3Pressed = digitalRead(button3Pin) == LOW;

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

void ButtonController::executeActions() {
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

void ButtonController::onDoubleButton1Tap(void (*callback)()) { cbDoubleButton1Tap = callback; }
void ButtonController::onButton3(void (*callback)()) { cbButton3 = callback; }
void ButtonController::onButton2(void (*callback)()) { cbButton2 = callback; }
void ButtonController::onButton2_Button1(void (*callback)()) { cbButton2_Button1 = callback; }
void ButtonController::onButton3_Button1(void (*callback)()) { cbButton3_Button1 = callback; }
void ButtonController::onTripleTap(void (*callback)()) { cbTripleTap = callback; }
void ButtonController::onQuadTap(void (*callback)()) { cbQuadTap = callback; }
