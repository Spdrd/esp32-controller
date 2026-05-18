#include "EspNowManager.h"

static EspNowManager *instance = nullptr;

EspNowManager::EspNowManager() {
    instance = this;
}

bool EspNowManager::begin() {
    WiFi.mode(WIFI_STA);

    if (esp_now_init() != ESP_OK) {
        Serial.println("Error inicializando ESP-NOW");
        initialized = false;
        return false;
    }

    esp_now_register_recv_cb(EspNowManager::onDataRecvStatic);
    initialized = true;
    Serial.println("ESP-NOW iniciado correctamente.");
    return true;
}

bool EspNowManager::begin(EspNowReceiveCallback callback) {
    setReceiveCallback(callback);
    return begin();
}

void EspNowManager::setReceiveCallback(EspNowReceiveCallback callback) {
    receiveCallback = callback;
}

bool EspNowManager::addPeer(const uint8_t *peer_addr) {
    if (!initialized || peer_addr == nullptr) {
        return false;
    }

    esp_now_peer_info_t peerInfo = {0};
    memcpy(peerInfo.peer_addr, peer_addr, 6);
    peerInfo.channel = 0;
    peerInfo.encrypt = false;

    return esp_now_add_peer(&peerInfo) == ESP_OK;
}

bool EspNowManager::removePeer(const uint8_t *peer_addr) {
    if (!initialized || peer_addr == nullptr) {
        return false;
    }

    return esp_now_del_peer(peer_addr) == ESP_OK;
}

bool EspNowManager::sendData(const uint8_t *peer_addr, const uint8_t *data, size_t len) {
    if (!initialized || peer_addr == nullptr || data == nullptr || len == 0) {
        return false;
    }

    return esp_now_send(peer_addr, data, len) == ESP_OK;
}

bool EspNowManager::isInitialized() const {
    return initialized;
}

void EspNowManager::onDataRecvStatic(const uint8_t *mac, const uint8_t *incomingData, int len) {
    if (instance) {
        instance->handleReceived(mac, incomingData, len);
    }
}

void EspNowManager::handleReceived(const uint8_t *mac, const uint8_t *incomingData, int len) {
    if (receiveCallback) {
        receiveCallback(mac, incomingData, len);
    }
}
