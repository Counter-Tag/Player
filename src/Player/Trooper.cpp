#include "../../include/Player/Trooper.h"
#include "../../include/Weapon/shot.h"

Trooper::Trooper(Weapon* weapon) : Player::Player(weapon) {
    this->maxHp = 100;

    this->initInModifiers(0);

    this->initOutModifiers(0);
    //this->outModifiers[0] = Trooper::bonusWeaponModifier;

    strcpy(this->name, "Trooper");
}

// AK-47 bonus
void Trooper::bonusWeaponModifier(weapon_shot_t* wshot) {
    if (wshot->type == 0x00) {
        wshot->shot &= ~WF_DAMAGE;
        wshot->shot |= WV_DAMAGE_10;
    }
}
