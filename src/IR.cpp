#include "../include/IR.h"

const uint16_t IR::PERIODS[] = {400, 600};
bool IR::initialized = false;
IR* IR::instance = NULL;

IR::IR() {
    pinMode(RECV_PIN, INPUT);
    digitalWrite(RECV_PIN, HIGH);

    attachInterrupt(INTR_PIN, ir_interrupt, FALLING);

    pinMode(SEND_PIN, OUTPUT);

    externalBuffer = NULL_SHOT;
    this->reset();

    IR::instance = this;

    TCCR2A = _BV(WGM21) | _BV(WGM20);
    //       Mode         8 Prescaler
    TCCR2B = _BV(WGM22) | _BV(CS21);
    OCR2A = 52; // Stop value. For 8 prescaler it equals 52.6
    OCR2B = 17; // 52.6 / 2 = 26.3 for 50% duty, 52.6 / 3 = 17.533.
    //TCCR2A |= _BV(COM2B1);

    ContextProvider::set("IR", this);
}

void IR::fire(shot_t shot) {
    for (int i = START_BIT; i > 0; i--) {
        // For each pulse, we send the IR carrier for a fixed length (IR::SHOT_TYPES[0]),
        // and then wait for a variable amount of time, depending on the shot type.
        TCCR2A |= _BV(COM2B1);
        delayMicroseconds(IR::PERIODS[0]);

        TCCR2A &= ~_BV(COM2B1);
        delayMicroseconds(IR::PERIODS[1 & (shot >> i)]);
    }

    // Turn LED on once more to read last bit, and shut down.
    TCCR2A |= _BV(COM2B1);
    delayMicroseconds(IR::PERIODS[0]);

    TCCR2A &= ~_BV(COM2B1);
}

void IR::interrupt() {
    const uint64_t time = micros();
    uint16_t period = time - lastReceptionTime - IR::PERIODS[0];

    if (period > 2 * IR::PERIODS[1]) {
        reset();
    } else {
        lastReceptionTime = time;

        if (period > IR::PERIODS[0] - IR::LOW_HYSTERESIS && period < IR::PERIODS[0] + IR::HIGH_HYSTERESIS) {
            currentBit--;
        } else if (period > IR::PERIODS[1] - IR::LOW_HYSTERESIS && period < IR::PERIODS[1] + IR::HIGH_HYSTERESIS) {
            buffer |= _BV(currentBit--);
        } else {
            reset();
            return;
        }

        if (currentBit == 0) {
            externalBuffer = (shot_t) buffer;
            reset();
        }
    }
}

shot_t IR::getShot() {
    shot_t shot;

    if (micros() - lastReceptionTime > 2 * IR::PERIODS[1]) {
        shot = (shot_t) externalBuffer;
        externalBuffer = NULL_SHOT;
        return shot;
    } else {
        return NULL_SHOT;
    }
}

inline void IR::reset() {
    // Reset counters and buffers, ladies and gentlemen.
    //memset(&buffer, 0, sizeof(buffer));
    buffer = 0;
    currentBit = START_BIT;
    lastReceptionTime = micros();
}

void ir_interrupt() {
    IR::instance->interrupt();
}
