#pragma once

#include "ButtonManager.h"
#include "BluetoothManager.h"
#include "ScreenManager.h"

// --- SCREEN PINS ---
#define TFT_DC    10
#define TFT_MOSI  9   
#define TFT_SCLK  8   

// --- BUTTON PINS ---
#define BUTTON1_PIN 5
#define BUTTON2_PIN 6
#define BUTTON3_PIN 7

// --- TIMINGS ---
#define BUTTON_COOLDOWN_MS 500

// --- BUTTON CONFIG ---
extern ButtonPinConfig buttonConfig;

// --- ACTIONS SETUP ---
ButtonActionCallbacks setupMusicControllerActions();

// --- MANAGERS INSTANCES ---
extern BluetoothManager bleKeyboard;
extern ButtonManager buttons;
extern ScreenManager screen;
