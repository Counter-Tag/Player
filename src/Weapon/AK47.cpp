#include "../../include/Weapon/AK47.h"

AK47::AK47() {
    this->name = "AK47";
    this->cooldown = 333;
    this->reloadCooldown = 2000;
    
    this->capacity = 120;
    this->magazineCapacity = 20;

    this->range = 2;

    this->shot = (weapon_shot_t) {_BV(WV_TARGET_ENEMIES) & _BV(WV_TARGET_ALLIES) & WV_DAMAGE_10, 0x00};

    this->type = Weapon::TYPE_AUTO;
}
