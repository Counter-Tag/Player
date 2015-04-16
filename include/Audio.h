#ifndef AUDIO_H
#define AUDIO_H

#include <TMRpcm.h>
#include <SPI.h>
#include <SD.h>
#include "common.h"

class Audio {
public:
    Audio();

    int init();

    void playWeapon(String weapon);
    void playFire();
    void playReload();
    void playDeath();

private:
    void play(const char* track);

    TMRpcm tmrpcm;
    bool initialized;
};

#endif
