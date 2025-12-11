#include <Arduino.h>
#include "Bluetooth_controller.h"
#include "Button_controller.h"

#define BUTTON_COOLDOWN_MS 500

// --- BUTTONS ---
#define BUTTON1_PIN 5
#define BUTTON2_PIN 6
#define BUTTON3_PIN 7

// Controller instances
BluetoothController bleKeyboard;
ButtonController buttons(BUTTON1_PIN, BUTTON2_PIN, BUTTON3_PIN);

void setup() {
    Serial.begin(115200);

    Serial.println("Starting BLE Keyboard ESP32-C3...");
    bleKeyboard.begin();
    Serial.println("Ready! Connect from your phone.");

    // Init buttons
    buttons.begin();

    buttons.onDoubleButton1Tap([]() {
        Serial.println("Double Tap Button 1 detected: Play/Pause");
        bleKeyboard.sendConsumerControl(CC_PLAY_PAUSE);
    });

    buttons.onButton2([]() {
        Serial.println("Button 2 pressed: Volume Down");
        bleKeyboard.sendConsumerControl(CC_VOLUME_DOWN);
        delay(BUTTON_COOLDOWN_MS);
    });

    buttons.onButton3([]() {
        Serial.println("Button 3 pressed: Volume Up");
        bleKeyboard.sendConsumerControl(CC_VOLUME_UP);
        delay(BUTTON_COOLDOWN_MS);
    });

    buttons.onButton2_Button1([]() {
        Serial.println("Buttons 1 + 2 pressed: Previous Track");
        bleKeyboard.sendConsumerControl(CC_PREV_TRACK);
        delay(BUTTON_COOLDOWN_MS);
    });

    buttons.onButton3_Button1([]() {
        Serial.println("Buttons 1 + 3 pressed: Next Track");
        bleKeyboard.sendConsumerControl(CC_NEXT_TRACK);
        delay(BUTTON_COOLDOWN_MS);
    });
}

void loop() {
    buttons.update();
}
