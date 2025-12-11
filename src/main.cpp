#include <Arduino.h>
#include <NimBLEDevice.h>

NimBLEServer* server;
NimBLECharacteristic* inputReport;

// Report Map estándar de teclado (simplificado)
static const uint8_t reportMap[] = {
    0x05, 0x01,       // USAGE_PAGE (Generic Desktop)
    0x09, 0x06,       // USAGE (Keyboard)
    0xA1, 0x01,       // COLLECTION (Application)
    0x05, 0x07,       // USAGE_PAGE (Keyboard)
    0x19, 0xE0,       // USAGE_MINIMUM (Left Control)
    0x29, 0xE7,       // USAGE_MAXIMUM (Right GUI)
    0x15, 0x00,
    0x25, 0x01,
    0x75, 0x01,
    0x95, 0x08,
    0x81, 0x02,       // INPUT (modifier)
    0x95, 0x01,
    0x75, 0x08,
    0x81, 0x03,       // INPUT (reserved)
    0x95, 0x06,
    0x75, 0x08,
    0x15, 0x00,
    0x25, 0x65,
    0x05, 0x07,
    0x19, 0x00,
    0x29, 0x65,
    0x81, 0x00,       // INPUT (keys[6])
    0xC0              // END_COLLECTION
};

void setup() {
    Serial.begin(115200);
    Serial.println("Iniciando BLE Keyboard ESP32-C3...");

    NimBLEDevice::init("C3 BLE Keyboard");
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
    scanData.setName("C3 BLE Keyboard");
    adv->setScanResponseData(scanData);

    adv->start();

    Serial.println("Listo! Conéctalo desde tu celular.");
}

// Enviar tecla 0x04 = “a”
void sendKey(uint8_t keycode) {
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

void loop() {
    Serial.println("Enviando tecla A...");
    sendKey(0x04); // “a”
    delay(5000);
}
