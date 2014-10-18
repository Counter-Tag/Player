#include "../../include/Weapon/Weapon.h"

/*
 * Not used (yet)
Weapon::Weapon() {

}
*/

bool Weapon::canFire() {
    return this->magazineAmmo > 0 && this->nextFire < millis();
}

weapon_shot_t* Weapon::fire() {
    this->nextFire = millis() + this->cooldown;
    
    if (this->magazineAmmo > 0) {
        --this->magazineAmmo;
    }

    return &this->shot;
}

void Weapon::reload() {
    if (this->ammo > 0) {
        int swap;

        if (this->ammo > this->magazineCapacity) {
            swap = this->magazineCapacity;
        } else {
            swap = ammo;
        }

        this->ammo -= swap;
        this->magazineAmmo = swap;

        this->nextFire = millis() + this->reloadCooldown;
    }
}

void Weapon::refill() {
    this->ammo = this->capacity;
    this->magazineAmmo = this->magazineCapacity;
}

int Weapon::getAmmo() {
    return this->ammo;
}
void Weapon::setAmmo(int ammo) {
    this->ammo = ammo;
}

uint8_t Weapon::getMagazineAmmo() {
    return this->magazineAmmo;
}
void Weapon::setMagazineAmmo(uint8_t magazineAmmo) {
    this->magazineAmmo = magazineAmmo;
}

int Weapon::getCapacity() {
    return this->capacity;
}
void Weapon::setCapacity(int capacity) {
    this->capacity = capacity;
}

uint8_t Weapon::getMagazineCapacity() {
    return this->magazineCapacity;
}
void Weapon::setMagazineCapacity(uint8_t magazineCapacity) {
    this->magazineCapacity = magazineCapacity;
}

uint8_t Weapon::getRange() {
    return this->range;
}

bool isAutomatic() {
    return this.isAutomatic;
}
