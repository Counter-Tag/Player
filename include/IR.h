#ifndef IR_H
#define IR_H

#include <Arduino.h>
#include "Weapon/weapon_shot.h"
#include "common.h"

class IR {
public:
    IR();

    static void interrupt();
    
    static void shoot(const shot_t* shot);
    static shot_t* receiveShot();

    static shot_t shot;


private:
    static const uint16_t MAX_RECEPTION_TIME = 8000;
    
    static const uint16_t LOW_HYSTERESIS = 100;
    static const uint16_t HIGH_HYSTERESIS = 400;

    static const uint8_t MIN_SHOTS = 3;

    static const uint8_t CARRIER_PERIOD = 105; // 38kHz

    static const uint16_t SHOT_TYPES[3];

    static unsigned long lastReceptionTime;
    static uint8_t receivedShots[3];
};

#endif
