#include "../../include/Player/player_factory.h"

#include "../../include/Player/Player.h"
#include "../../include/Player/Trooper.h"

Player* create_player(int id) {
    if(id == 0) {
        return new Trooper();
    }

    return NULL;
}

Player* create_player(const char* name) {
    if (!strcmp(name, "Trooper")) {
        return create_player(0);
    }

    return NULL;
}