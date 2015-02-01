#include "../include/IR.h"

const uint16_t IR::SHOT_TYPES[3] = {400, 800, 1200};
bool IR::initialized = false;
IR* IR::instance = NULL;

IR::IR() {
    pinMode(RECV_PIN, INPUT);
    digitalWrite(RECV_PIN, HIGH);

    attachInterrupt(INTR_PIN, ir_interrupt, FALLING);

    // TODO: Try NOINLINE macro to call external function from constructor.

    pinMode(SEND_PIN, OUTPUT);
    
    lastReceptionTime = 0;

    receivedShots[0] = 0;
    receivedShots[1] = 0;
    receivedShots[2] = 0;

    totalShots = 0;

    IR::instance = this;
}

void IR::shoot(const shot_t* shot) {
    const uint8_t type = (shot->flags & WF_TEAM) << 4;
    const uint8_t pulses = shot->damage / IR::DAMAGE_PER_PULSE;
    int sent = 0;

    IR::timerSetup();

    // We send one pulse per 3 damage points.
    for (sent = 0; sent < pulses; sent++) {
        // For each pulse, we send the IR carrier for a fixed length (IR::SHOT_TYPES[0]),
        // and then wait for a variable amount of time, depending on the shot type.
        TCCR2A |= _BV(COM2B1);
        delayMicroseconds(IR::SHOT_TYPES[0]);

        TCCR2A &= ~_BV(COM2B1);
        delayMicroseconds(IR::SHOT_TYPES[type]);

    }
}

void IR::interrupt() {
    uint16_t period;

    // Reset counters and means if more than MAX_RECEPTION_TIME pased since last reception.
    if ((micros() - lastReceptionTime) > IR::MAX_RECEPTION_TIME) {
        receivedShots[0] = 0;
        receivedShots[1] = 0;
        receivedShots[2] = 0;
        totalShots = 0;
    }

    // Space period equals to actual time less last reception time less constant period.
    period = micros() - lastReceptionTime - SHOT_TYPES[0];
    lastReceptionTime = micros();
    int i = -1;
    for (i = 0; i < 3; i++) {
        if (period > IR::SHOT_TYPES[i] - IR::LOW_HYSTERESIS && period < IR::SHOT_TYPES[i] + IR::HIGH_HYSTERESIS) {
            receivedShots[i]++;
            break; // Ugly, but we are interrupting main code execution and this must be as fast as possible.
        }
    }

    totalShots++;
}

shot_t* IR::receiveShot() {
    bool valid = false;

    //Serial.print(totalShots);
    //Serial.println(" shots pending.");

    if (totalShots >= IR::MIN_SHOTS) {
        shot.damage = totalShots * DAMAGE_PER_PULSE;
        shot.flags = (uint8_t) 0;

        Serial.println("Minimum reached.");
        
        for (int i = 0; i < 3; i++) {
            // Check if we have received more than 60% shots of one type
            if ((receivedShots[i] * 10 / totalShots * 10) >= 6) {
                shot.flags |= ((uint8_t) i >> 4) & WF_TEAM;
                valid = true;
                break;
            }
        }

        if (valid) {
            Serial.println("Valid shot received");
            // Workaround for setting heal flags
            if ((shot.flags & WF_TEAM) << 4 == 0x01) { // Team 3 aka heal shots in the provisional IR lib
                shot.flags = WF_HEAL_ENEMIES | WF_HEAL_ALLIES;
                shot.flags |= (1 >> 4) & WF_TEAM; // Set team tag to 11
            }

            // TODO: Remove.
            shot.flags = _BV(3) | WF_DAMAGE_ENEMIES;

            receivedShots[0] = 0;
            receivedShots[1] = 0;
            receivedShots[2] = 0;
            totalShots = 0;

            return &(shot);
        } else {
            return NULL;
        }
    } else {
        return NULL;
    }
}

void IR::timerSetup() {
    if (!initialized) {
        TCCR2A = _BV(WGM21) | _BV(WGM20);
        //       Mode         8 Prescaler
        TCCR2B = _BV(WGM22) | _BV(CS21);
        OCR2A = 51; // Stop value. For 8 prescaler it equals 52.6
        OCR2B = 26; // 52.6 / 2 = 26.3 for 50% duty.
        //TCCR2A |= _BV(COM2B1);

        initialized = true;
    }
}

void ir_interrupt() {
    IR::instance->interrupt();
}
