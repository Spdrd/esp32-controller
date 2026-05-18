#ifndef ESPNOW_MANAGER_H
#define ESPNOW_MANAGER_H

#include <Arduino.h>
#include <WiFi.h>
#include <esp_now.h>

typedef void (*EspNowReceiveCallback)(const uint8_t *mac, const uint8_t *incomingData, int len);

class EspNowManager {
public:
    EspNowManager();

    bool begin();
    bool begin(EspNowReceiveCallback callback);

    void setReceiveCallback(EspNowReceiveCallback callback);
    bool addPeer(const uint8_t *peer_addr);
    bool removePeer(const uint8_t *peer_addr);
    bool sendData(const uint8_t *peer_addr, const uint8_t *data, size_t len);
    bool isInitialized() const;

private:
    static void onDataRecvStatic(const uint8_t *mac, const uint8_t *incomingData, int len);
    void handleReceived(const uint8_t *mac, const uint8_t *incomingData, int len);

    bool initialized = false;
    EspNowReceiveCallback receiveCallback = nullptr;
};

#endif // ESPNOW_MANAGER_H
