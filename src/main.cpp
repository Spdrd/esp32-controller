#include <Arduino.h>
#include "bluetooth_controller.h"

BluetoothController bleKeyboard;

void setup() {
    Serial.begin(115200);
    Serial.println("Iniciando BLE Keyboard ESP32-C3...");
    bleKeyboard.begin();
    Serial.println("Listo! Conéctalo desde tu celular.");
}

void loop() {
    Serial.println("Enviando");
    bleKeyboard.sendConsumerControl(CC_VOLUME_UP);  // Subir volumen
    delay(1000);
}
