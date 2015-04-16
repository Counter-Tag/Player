#include "../include/Audio.h"

Audio::Audio() : tmrpcm() {
    tmrpcm.speakerPin = SPKR_PIN;
}

int Audio::init() {
    return (initialized = SD.begin(SDCS_PIN));
}

void Audio::play(const char* track) {
    if (initialized) {
        tmrpcm.stopPlayback();
        tmrpcm.play((char*) track);
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
    Serial.println("Fire playing!");
    play("FIRE.WAV");
}
