#ifndef COMMANDER_H
#define COMMANDER_H

#include "../include/Tag.h"

typedef struct command {
    uint8_t is_short;
    uint8_t opcode;
    uint8_t args;
} command_t;

class Commander {
public:
    Commander(Tag* tag);

    void run(uint8_t cmd);

private:
    // Short commands
    static const uint8_t OP_RESPAWN = 0x00;

    // Long commands
    static const uint8_t OP_CHANGEWEAPON = 0x00;
    static const uint8_t OP_CHANGECLASS = 0x01;

    Tag* tag;

    void dispatch(command_t* cmd);
    inline void parse(command_t* dest, uint8_t cmd);
};

#endif
