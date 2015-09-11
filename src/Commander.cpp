#include "../include/Commander.h"

Commander::Commander(Tag* tag) {
    this->tag = tag;
}

void Commander::parse(command_t* dest, uint8_t cmd) {
    if (dest->is_short = (0x01 & (cmd >> 6))) {
        dest->opcode = (0x07 & (cmd >> 3));
        dest->args = 0x07 & cmd;
    } else {
        dest->opcode = (0x03 & (cmd >> 4));
        dest->args = 0x0f & cmd;
    }
}

void Commander::run(uint8_t cmd) {
    command_t command;

    parse(&command, cmd);
    dispatch(&command);
}

void Commander::dispatch(command_t* cmd) {
    if (cmd->is_short) {
        switch (cmd->opcode) {
        case OP_RESPAWN:
            this->tag->getPlayer()->spawn();
            break;
        }
    } else {
        switch (cmd->opcode) {
        case OP_CHANGEWEAPON:
            this->tag->updateWeapon(cmd->args);
            break;
        case OP_CHANGECLASS:
            this->tag->updateClass(cmd->args);
            break;
        }
    }
}
