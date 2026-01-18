#pragma once
#include <Arduino.h>
#include <NimBLEDevice.h>

// ===== Consumer Control HID Usage IDs =====
#define CC_VOLUME_UP       0xE9
#define CC_VOLUME_DOWN     0xEA
#define CC_PLAY_PAUSE      0xCD
#define CC_NEXT_TRACK      0xB5
#define CC_PREV_TRACK      0xB6
#define CC_STOP            0xB7
#define CC_MUTE            0xE2

class BluetoothManager {
public:
    void begin();
    void begin(std::string device_name);
    void sendKey(uint8_t keycode);
    void sendConsumerControl(uint8_t command);
};
