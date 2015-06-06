#ifndef IR_H
#define IR_H

#include <Arduino.h>
#include "configuration.h"
#include "Debug.h"
#include "ContextProvider.h"
#include "Weapon/shot.h"

class IR {
public:
    IR();

    void interrupt();
    void fire(shot_t shot);
    shot_t getShot();

    shot_t shot;

    static IR* instance;

private:
    inline void reset();

    static const uint16_t MAX_RECEPTION_TIME = 1000;

    static const uint16_t LOW_HYSTERESIS = 50;
    static const uint16_t HIGH_HYSTERESIS = 100;

    static const uint8_t MIN_SHOTS = 2;

    static const uint8_t START_BIT = 8 * sizeof(shot_t) - 1;

    static const uint16_t PERIODS[2];

    uint64_t lastReceptionTime;
    uint16_t buffer;
    uint8_t currentBit;
    shot_t externalBuffer;

    static bool initialized;
};

void ir_interrupt();

#endif
