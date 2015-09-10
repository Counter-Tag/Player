#include "../include/IR.h"

const uint16_t IR::PERIODS[] = {400, 600};
bool IR::initialized = false;
IR* IR::instance = NULL;

IR::IR() {
    pinMode(RECV_PIN, INPUT);
    digitalWrite(RECV_PIN, HIGH);

    attachInterrupt(INTR_PIN, ir_interrupt, FALLING);

    pinMode(SEND_PIN, OUTPUT);

    externalBuffer = IR::NULL_PKT;
    this->reset();

    IR::instance = this;

    IR::off(); // Just in case.
    TCCR2A = _BV(WGM21) | _BV(WGM20);
    //       Mode         8 Prescaler
    TCCR2B = _BV(WGM22) | _BV(CS21);
    OCR2A = 52; // Stop value. For 8 prescaler it equals 52.6
    OCR2B = 17; // 52.6 / 2 = 26.3 for 50% duty, 52.6 / 3 = 17.533 for 33%.
}

void IR::send(ir_pkt_t shot) {
    for (int i = START_BIT; i >= 0; i--) {
        // For each pulse, we send the IR carrier for a fixed length (IR::SHOT_TYPES[0]),
        // and then wait for a variable amount of time, depending on the shot type.
        IR::on();
        delayMicroseconds(IR::PERIODS[0]);

        IR::off();
        delayMicroseconds(IR::PERIODS[0x01 & (shot >> i)]);
    }

    // Turn LED on once more to read last bit, and shut down.
    IR::on();
    delayMicroseconds(IR::PERIODS[0]);

    IR::off();
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

        if (currentBit == -1) {
            externalBuffer = buffer;
            reset();
        }
    }
}

ir_pkt_t IR::recv() {
    ir_pkt_t packet;

    if (micros() - lastReceptionTime > 2 * IR::PERIODS[1]) {
        packet = externalBuffer;
        externalBuffer = NULL_PKT;
        return packet;
    } else {
        return NULL_PKT;
    }
}

inline void IR::reset() {
    // Reset counters and buffers, ladies and gentlemen.
    //memset(&buffer, 0, sizeof(buffer));
    buffer = 0;
    currentBit = START_BIT;
    lastReceptionTime = micros();
}

inline void IR::on() {
    TCCR2A |= _BV(COM2B1);
}

inline void IR::off() {
    TCCR2A &= ~_BV(COM2B1);
}


void ir_interrupt() {
    IR::instance->interrupt();
}
