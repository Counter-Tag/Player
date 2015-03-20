#ifndef IR_H
#define IR_H

#include <Arduino.h>
#include "Weapon/shot.h"
#include "common.h"

class IR {
public:
    IR();

    void interrupt();
    void fire(shot_t shot);
    shot_t* receiveShot();

    shot_t shot;

    static IR* instance;

private:
    static const uint16_t MAX_RECEPTION_TIME = 1000;

    static const uint16_t LOW_HYSTERESIS = 100;
    static const uint16_t HIGH_HYSTERESIS = 200;

    static const uint8_t MIN_SHOTS = 2;

    static const uint16_t PERIODS[2];

    unsigned long lastReceptionTime;
    uint8_t receivedPulses;
    uint8_t buffer;

    static bool initialized;


    static void timerSetup();
};

void ir_interrupt();

#endif
