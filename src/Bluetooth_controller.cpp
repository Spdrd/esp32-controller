#include "bluetooth_controller.h"

NimBLEServer* server;
NimBLECharacteristic* inputReport;


static const uint8_t reportMap[] = {

    // ------------------------------
    // Keyboard (Report ID 1)
    // ------------------------------
    0x05, 0x01,        // USAGE_PAGE (Generic Desktop)
    0x09, 0x06,        // USAGE (Keyboard)
    0xA1, 0x01,        // COLLECTION (Application)
    0x85, 0x01,        //   REPORT_ID (1)

    // Modifier keys
    0x05, 0x07,        //   USAGE_PAGE (Keyboard)
    0x19, 0xE0,        //   USAGE_MINIMUM (Left Control)
    0x29, 0xE7,        //   USAGE_MAXIMUM (Right GUI)
    0x15, 0x00,        
    0x25, 0x01,
    0x75, 0x01,
    0x95, 0x08,
    0x81, 0x02,        //   INPUT (Data,Var,Abs)

    // Reserved byte
    0x95, 0x01,
    0x75, 0x08,
    0x81, 0x03,        //   INPUT (Const,Var,Abs)

    // Normal keys (6 key rollover)
    0x95, 0x06,
    0x75, 0x08,
    0x15, 0x00,
    0x25, 0x65,
    0x05, 0x07,
    0x19, 0x00,
    0x29, 0x65,
    0x81, 0x00,        //   INPUT (Data,Ary,Abs)
    0xC0,              // END_COLLECTION


    // ------------------------------
    // Consumer Control (Report ID 2)
    // ------------------------------
    0x05, 0x0C,        // USAGE_PAGE (Consumer)
    0x09, 0x01,        // USAGE (Consumer Control)
    0xA1, 0x01,        // COLLECTION (Application)
    0x85, 0x02,        //   REPORT_ID (2)

    0x15, 0x00,
    0x26, 0xFF, 0x03,  //   LOGICAL_MAXIMUM (0x3FF)

    0x19, 0x00,
    0x2A, 0xFF, 0x03,  //   USAGE_MAXIMUM

    0x75, 0x10,        //   REPORT_SIZE (16 bits)
    0x95, 0x01,        //   REPORT_COUNT (1)
    0x81, 0x00,        //   INPUT (Data,Ary,Abs)

    0xC0               // END_COLLECTION
};

void BluetoothController::begin() {
    begin("ESP32-C3 BLE Keyboard");
}

void BluetoothController::begin(std::string device_name) {
    NimBLEDevice::init(device_name);
    server = NimBLEDevice::createServer();

    // Crear servicio HID
    NimBLEService* hidService = server->createService("1812"); // HID UUID

    // Característica Input Report
    inputReport = hidService->createCharacteristic(
        "2A4D",
        NIMBLE_PROPERTY::NOTIFY | NIMBLE_PROPERTY::READ
    );

    // Característica Report Map
    NimBLECharacteristic* reportMapChar = hidService->createCharacteristic(
        "2A4B",
        NIMBLE_PROPERTY::READ
    );
    reportMapChar->setValue((uint8_t*)reportMap, sizeof(reportMap));

    hidService->start();

    // Advertising
    NimBLEAdvertising* adv = NimBLEDevice::getAdvertising();
    adv->addServiceUUID("1812");

    // Scan Response
    NimBLEAdvertisementData scanData;
    scanData.setName(device_name);
    adv->setScanResponseData(scanData);

    adv->start();
}

void BluetoothController::sendKey(uint8_t keycode) {
    uint8_t report[8] = {0};
    report[2] = keycode; // posición del keycode

    inputReport->setValue(report, sizeof(report));
    inputReport->notify();
    delay(20);

    // Soltar tecla
    uint8_t empty[8] = {0};
    inputReport->setValue(empty, sizeof(empty));
    inputReport->notify();
}

void BluetoothController::sendConsumerControl(uint8_t command) {
    uint8_t report[3];

    report[0] = 0x02;       // Report ID 2 (Consumer Control)
    report[1] = command;    // Código HID del botón
    report[2] = 0x00;       // MSB

    inputReport->setValue(report, sizeof(report));
    inputReport->notify();

    delay(20);

    // Soltar tecla (report vacío)
    uint8_t empty[3] = {0x02, 0x00, 0x00};
    inputReport->setValue(empty, sizeof(empty));
    inputReport->notify();
}


