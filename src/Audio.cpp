#include "../include/Audio.h"

Audio::Audio() : tmrpcm() {
    tmrpcm.speakerPin = SPKR_PIN;

    initialized = SD.begin(SDCS_PIN);

    if (initialized) {
        print_debug("[AUD] Audio module initialized.");
    } else {
        print_error("[AUD] Error initializing audio.");
    }
}

void Audio::playWeapon(String weapon) {
    weapon += ".WAV";
    play(weapon.c_str());
}

void Audio::playReload() {
    play("RELOAD.WAV");
}

void Audio::playDeath() {
    play("DEATH.WAV");
}

void Audio::playFire() {
    play("SHOT.WAV");
}

void Audio::stop() {
    tmrpcm.stopPlayback();
}

void Audio::play(const char* track) {
    if (initialized) {
        print_debug("[AUDIO] Playing '%s'.", track);
        tmrpcm.play((char*) track);
    }
}
