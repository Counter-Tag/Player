#include "../include/Weapon/AK47.h"

AK47::AK47() {
    this->cooldown = 100;
    this->reloadCooldown = 2000;
    
    this->capacity = 120;
    this->magazineCapacity = 20;

    this->range = 2;

    this->shot = (weapon_shot_t) {15, WF_DAMAGE_ENEMIES, 0x00};
}
