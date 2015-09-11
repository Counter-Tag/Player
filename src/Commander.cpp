#include "../include/Commander.h"
#include "../include/Tag.h"

Commander::Commander(Tag* t) {
    this->tag = t;
}

ir_pkt_t Commander::encode(const command_t* cmd) {
    ir_pkt_t packet = Commander::CF_CMD;

    if (cmd->is_short) {
        packet |= Commander::CF_ISSHORT & _BV(Commander::CV_ISSHORT);
        packet |= Commander::CF_SHORTOP & (cmd->opcode << Commander::CV_SHORTOP);
        packet |= Commander::CF_SHORTARGS & (cmd->args << Commander::CV_SHORTARGS);
    } else {
        packet |= Commander::CF_LONGOP & (cmd->opcode << Commander::CV_LONGOP);
        packet |= Commander::CF_LONGARGS & (cmd->args << Commander::CV_LONGARGS);
    }

    print_event("Encoded: 0x%x", packet);

    return packet;
}

command_t* Commander::decode(command_t* dest, ir_pkt_t cmd) {
    if ((dest->is_short = ((Commander::CF_ISSHORT >> Commander::CV_ISSHORT) & (cmd >> Commander::CV_ISSHORT)))) {
        dest->opcode = ((Commander::CF_SHORTOP >> Commander::CV_SHORTOP) & (cmd >> Commander::CV_SHORTOP));
        dest->args = (CF_SHORTARGS) & cmd;
    } else {
        dest->opcode = ((Commander::CF_LONGOP >> Commander::CV_LONGOP) & (cmd >> CV_LONGOP));
        dest->args = CF_LONGARGS & cmd;
    }

    print_event("Decoded: {short: %d, opcode: 0x%x, args: 0x%x}", dest->is_short, dest->opcode, dest->args);

    return dest;
}

void Commander::run(ir_pkt_t cmd) {
    command_t command;

    decode(&command, cmd);
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
