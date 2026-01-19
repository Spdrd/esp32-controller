#include "GlobalConfig.h"

// --- BUTTON CONFIG ---
ButtonPinConfig buttonConfig = {
    BUTTON1_PIN,
    BUTTON2_PIN,
    BUTTON3_PIN
};

// --- MANAGERS INSTANCES ---
BluetoothManager bleKeyboard;
ButtonManager buttons(buttonConfig);

void (*playPauseCallback)() = []() {
        Serial.println("Play/Pause");
        bleKeyboard.sendConsumerControl(CC_PLAY_PAUSE);
    };

void (*nextTrackCallback)() = []() {
        Serial.println("Next Track");
        bleKeyboard.sendConsumerControl(CC_NEXT_TRACK);
        delay(BUTTON_COOLDOWN_MS);
    };

void (*previousTrackCallback)() = []() {
        Serial.println("Previous Track");
        bleKeyboard.sendConsumerControl(CC_PREV_TRACK);
        delay(BUTTON_COOLDOWN_MS);
    };

void (*volumeUpCallback)() = []() {
        Serial.println("Volume Up");
        bleKeyboard.sendConsumerControl(CC_VOLUME_UP);
        delay(BUTTON_COOLDOWN_MS);
    };

void (*volumeDownCallback)() = []() {
        Serial.println("Volume Down");
        bleKeyboard.sendConsumerControl(CC_VOLUME_DOWN);
        delay(BUTTON_COOLDOWN_MS);
    };

ButtonActionCallbacks setupMusicControllerActions(){
    ButtonActionCallbacks buttonActions;
    buttonActions.onDoubleButton1Tap = playPauseCallback;
    buttonActions.onButton3 = nextTrackCallback;
    buttonActions.onButton2 = previousTrackCallback;
    buttonActions.onButton3_Button1 = volumeUpCallback;
    buttonActions.onButton2_Button1 = volumeDownCallback;
    return buttonActions;
}
