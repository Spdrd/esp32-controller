#include <Arduino.h>
#include "GlobalConfig.h"

void setup() {

  ButtonActionCallbacks buttonActions;
  

    Serial.begin(115200); 

    Serial.println("Starting BLE Keyboard ESP32-C3...");
    bleKeyboard.begin();
    Serial.println("Ready! Connect from your phone.");

    // Init buttons
    buttons.begin();
    buttons.setCallbacks(setupMusicControllerActions());
    screen.begin();
}

void loop() {
    buttons.update();
}
