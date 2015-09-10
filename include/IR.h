#ifndef IR_H
#define IR_H

#include <Arduino.h>
#include "configuration.h"
#include "Debug.h"

typedef uint8_t ir_pkt_t;

#define IS_OPCODE(packet) (0x01 & (packet >> 7))

class IR {
public:
    IR();

    void interrupt();
    void send(ir_pkt_t data);
    ir_pkt_t recv();

    ir_pkt_t packet;

    static IR* instance;

private:
    inline void reset();

    inline void on();
    inline void off();

    static const uint16_t MAX_RECEPTION_TIME = 1000;

    static const uint16_t LOW_HYSTERESIS = 50;
    static const uint16_t HIGH_HYSTERESIS = 100;

    static const uint8_t MIN_SHOTS = 2;

    static const uint8_t START_BIT = 7;

    static const uint16_t PERIODS[2];

    static const ir_pkt_t NULL_PKT = (ir_pkt_t) 0xffff;

    static bool initialized;

    uint64_t lastReceptionTime;
    int8_t currentBit;
    ir_pkt_t buffer;
    ir_pkt_t externalBuffer;
};

void ir_interrupt();

#endif
