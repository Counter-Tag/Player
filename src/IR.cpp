#include "../include/IR.h"

const uint16_t IR::SHOT_TYPES[3] = {1000, 2000, 3000};

IR::IR() {
    pinMode(RECV_PIN, INPUT);
    digitalWrite(RECV_PIN, HIGH);
    attachInterrupt(INTR_PIN, IR::interrupt, FALLING);

    pinMode(SEND_PIN, OUTPUT);
    TCCR2A = _BV(COM2A0) | _BV(COM2B1) | _BV(WGM20);
    TCCR2B = _BV(WGM22) | _BV(CS20);
    OCR2A = 210;
    OCR2B = 0;
}

void IR::shoot(const shot_t* shot) {
    int sent = 0;
    bool halfPeriod = 1;

    unsigned long time = 0;
    while(sent < (shot->damage / 5)) {
        if(micros() - time >= IR::SHOT_TYPES[(shot->flags & WF_TEAM) << 4]) {
            if (halfPeriod) {
                OCR2B = IR::CARRIER_PERIOD;
                time = micros();
                halfPeriod = false;
            } else {
                OCR2B = 0;
                time = micros();
                halfPeriod = true;
                sent++;
            }
        }
    }
}

shot_t* IR::receiveShot() {
    uint8_t totalShots = receivedShots[0] + receivedShots[1] + receivedShots[2];
    bool valid = false;

    if (totalShots >= IR::MIN_SHOTS) {
        shot.damage = totalShots * 5;
        shot.flags = (uint8_t) 0;
        
        for (int i = 0; i < 3 && !valid; i++) {
            if ((receivedShots[i] * 10 / totalShots * 10) > 6) {
                shot.flags |= ((uint8_t) i >> 4) & WF_TEAM;
                valid = true;
            }
        }


        // WARNING: We are waiting for invalid shots to make sense.
        if (valid) {
            // Workaround for setting heal flags
            if ((shot.flags & WF_TEAM) << 4 == 0x01) { // Team 3 aka heal shots in the provisional IR lib
                shot.flags = WF_HEAL_ENEMIES | WF_HEAL_ALLIES;
                shot.flags |= (0xff >> 4) & WF_TEAM; // Set team tag to 11
            }
            
            receivedShots[0] = 0;
            receivedShots[1] = 0;
            receivedShots[2] = 0;

            return &(shot);
        } else {
            return NULL;
        }
    } else {
        return NULL;
    }
}

void IR::interrupt() {
    // Reset counters and means if more than MAX_RECEPTION_TIME pased since last reception.
    uint16_t period;

    if ((micros() - lastReceptionTime) > IR::MAX_RECEPTION_TIME) {
        period = 0;
        receivedShots[0] = 0;
        receivedShots[1] = 0;
        receivedShots[2] = 0;
    }

    period = micros() - lastReceptionTime;
    lastReceptionTime = micros();

    for (int i = 0; i < 3; i++) {
        if (period > IR::SHOT_TYPES[i] - IR::LOW_HYSTERESIS && period < IR::SHOT_TYPES[i] + IR::HIGH_HYSTERESIS) {
            receivedShots[i]++;
        }
    }
}

