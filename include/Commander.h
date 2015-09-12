#ifndef COMMANDER_H
#define COMMANDER_H

#include "../include/IR.h"

typedef struct command {
    uint8_t is_short;
    uint8_t opcode;
    uint8_t args;
} command_t;

class Tag;

class Commander {
public:
    Commander(Tag* t);

    ir_pkt_t encode(const command_t* cmd);
    command_t* decode(command_t* dest, ir_pkt_t cmd);
    void run(ir_pkt_t cmd);

    // Short commands
    static const uint8_t OP_RESPAWN = 0x00;

    // Long commands
    static const uint8_t OP_CHANGEWEAPON = 0x00;
    static const uint8_t OP_CHANGECLASS = 0x01;

    // Filters
    static const uint8_t CF_CMD     = 0b10000000;
    static const uint8_t CV_CMD     = 7;

    static const uint8_t CF_ISSHORT = 0b01000000;
    static const uint8_t CV_ISSHORT = 6;

    static const uint8_t CF_SHORTOP = 0b00111000;
    static const uint8_t CV_SHORTOP = 3;

    static const uint8_t CF_SHORTARGS = 0b00000111;
    static const uint8_t CV_SHORTARGS = 0;

    static const uint8_t CF_LONGOP  = 0b00110000;
    static const uint8_t CV_LONGOP  = 4;

    static const uint8_t CF_LONGARGS  = 0b00001111;
    static const uint8_t CV_LONGARGS  = 0;

private:
    Tag* tag;

    void dispatch(command_t* cmd);
};

#endif
