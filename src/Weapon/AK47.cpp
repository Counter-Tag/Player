#include "../../include/Weapon/AK47.h"

AK47::AK47() {
    this->cooldown = 200;
    this->reloadCooldown = 2000;
    
    this->capacity = 120;
    this->magazineCapacity = 20;

    this->range = 2;

    this->shot = (weapon_shot_t) {WF_TARGET_ENEMIES | WV_DAMAGE_10, 0x00};

    this->type = Weapon::TYPE_AUTO;

    strcpy(this->name, "AK47");
}
