#ifndef WEAPON_H
#define WEAPON_H

#include <Arduino.h>
#include "weapon_shot.h"

class Weapon {
public:
    Weapon();

    virtual weapon_shot_t* fire();
    virtual bool canFire();

    virtual void reload();
    virtual void refill();


    int getCapacity();
    void setCapacity(int capacity);

    int getAmmo();
    void setAmmo(int ammo);

    uint8_t getMagazineCapacity();
    void setMagazineCapacity(uint8_t magazineCapacity);

    uint8_t getMagazineAmmo();
    void setMagazineAmmo(uint8_t magazineAmmo);

    virtual uint8_t getRange();

    uint8_t getType();
    String getName();

    weapon_shot_t  shot;

    String name;

    static const uint8_t TYPE_SEMI = 0;
    static const uint8_t TYPE_AUTO = 1;
    static const uint8_t TYPE_NORE = 2;

protected:
    unsigned long nextFire;

    int cooldown;
    int reloadCooldown;
    
    int ammo;
    int capacity;

    int range;
    
    uint8_t magazineAmmo;
    uint8_t magazineCapacity;

    uint8_t type;
};

#endif
