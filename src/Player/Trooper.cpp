#include "../../include/Player/Trooper.h"

Trooper::Trooper() {
    this->maxHp = 100;

    this->initInModifiers(0);

    this->initOutModifiers(1);
    this->outModifiers[0] = Trooper::bonusWeaponModifier;
}

// AK-47 20% bonus
void Trooper::bonusWeaponModifier(weapon_shot_t* wshot) {
    if (wshot->type == 0x00) {
        wshot->damage *= 1.2;
    }
}
