#ifndef TROOPER_H
#define TROOPER_H

#include "Player.h"

class Trooper : public Player {
public:
    Trooper(Weapon* weapon);

    const char* getClassName();

    static void bonusWeaponModifier(weapon_shot_t* wshot);
};

#endif
