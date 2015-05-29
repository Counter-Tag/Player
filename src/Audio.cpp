#include "../include/Audio.h"

Audio::Audio() : tmrpcm() {
    tmrpcm.speakerPin = SPKR_PIN;
}

int Audio::init() {
    return (initialized = SD.begin(SDCS_PIN));
}

void Audio::playWeapon(String weapon) {
    weapon += ".WAV";
    Serial.print("[AUDIO]: ");
    Serial.print(weapon);
    Serial.println(" playing.");
    play(weapon.c_str());
}

void Audio::playReload() {
    Serial.println("[AUDIO]: Reload playing.");
    play("RELOAD.WAV");
}

void Audio::playDeath() {
    Serial.println("[AUDIO]: Death playing.");
    play("DEATH.WAV");
}

void Audio::playFire() {
    Serial.println("[AUDIO]: Fire playing.");
    play("SHOT.WAV");
}

void Audio::stop() {
    tmrpcm.stopPlayback();
}

void Audio::play(const char* track) {
    if (initialized) {
        tmrpcm.play((char*) track);
    }
}
