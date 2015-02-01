#ifndef IR_H
#define IR_H

#include <Arduino.h>
#include "Weapon/weapon_shot.h"
#include "common.h"

class IR {
public:
    IR();

    void interrupt();
    void shoot(const shot_t* shot);
    shot_t* receiveShot();
    static void timerSetup();

    shot_t shot;

    static IR* instance;
    static bool initialized;
    unsigned long period;

private:
    static const uint16_t MAX_RECEPTION_TIME = 4000;

    static const uint16_t LOW_HYSTERESIS = 100;
    static const uint16_t HIGH_HYSTERESIS = 200;

    static const uint8_t MIN_SHOTS = 2;

    static const uint16_t SHOT_TYPES[3];

    static const uint8_t DAMAGE_PER_PULSE = 3;

    unsigned long lastReceptionTime;
    uint8_t receivedShots[3];
    uint8_t totalShots;
};

void ir_interrupt();

#endif
