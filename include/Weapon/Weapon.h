#ifndef WEAPON_H
#define WEAPON_H

#include <Arduino.h>
#include "weapon_shot.h"

class Weapon {
public:
    virtual weapon_shot_t* fire();
    virtual bool canFire();

    virtual void reload();
    virtual void refill();

    virtual int getCooldown();
    virtual void setCooldown(int cooldown);

    virtual int getCapacity();
    virtual void setCapacity(int capacity);

    virtual int getAmmo();
    virtual void setAmmo(int ammo);

    virtual uint8_t getMagazineCapacity();
    virtual void setMagazineCapacity(uint8_t magazineCapacity);

    virtual uint8_t getMagazineAmmo();
    virtual void setMagazineAmmo(uint8_t magazineAmmo);

    virtual uint8_t getRange();

    weapon_shot_t  shot;

protected:
    unsigned int nextFire;

    int cooldown;
    int reloadCooldown;
    
    int ammo;
    int capacity;

    int range;
    
    uint8_t magazineAmmo;
    uint8_t magazineCapacity;
};

#endif
