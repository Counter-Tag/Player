#include "../include/IR.h"

const uint16_t IR::PERIODS[] = {400, 600};
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

void IR::fire(shot_t shot) {
    IR::timerSetup();

    // We send one pulse per 3 damage points.
    for (int i = 0; i < SHOT_REAL_SIZE; i++) {
        // For each pulse, we send the IR carrier for a fixed length (IR::SHOT_TYPES[0]),
        // and then wait for a variable amount of time, depending on the shot type.
        TCCR2A |= _BV(COM2B1);
        delayMicroseconds(IR::SHOT_TYPES[0]);

        TCCR2A &= ~_BV(COM2B1);
        delayMicroseconds(IR::SHOT_TYPES[0x01 & (shot << i)]);
    }
}

void IR::interrupt() {
    // TODO
}

shot_t* IR::receiveShot() {
    bool valid = false;

    if (totalShots >= IR::MIN_SHOTS && lastReceptionTime + SHOT_TYPES[0] + SHOT_TYPES[2] < micros()) {
        //shot.damage = totalShots * DAMAGE_PER_PULSE;
        
        for (uint8_t i = 0; i < 3; i++) {
            // Check if we have received more than 60% shots of one type
            if (((float) receivedShots[i] / (float) totalShots) >= 0.6f) {
                //shot.flags = (i << 2) & WF_TEAM;
                //shot.flags |= WF_DAMAGE_ENEMIES;
                valid = true;
                break;
            }
        }

        if (valid) {
            //Serial.print("Valid shot received team ");
            //Serial.println((shot.flags & WF_TEAM) >> 2);

            // TODO: Remove.
            //shot.flags = _BV(3) | WF_DAMAGE_ENEMIES;

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
