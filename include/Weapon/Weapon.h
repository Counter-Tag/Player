#ifndef WEAPON_H
#define WEAPON_H

#include <Arduino.h>
#include <string.h>
#include <stdint.h>
#include "../Debug.h"
#include "shot.h"

class Weapon {
public:
    Weapon();

    virtual weapon_shot_t* fire();
    virtual bool canFire();
    virtual bool canReload();

    virtual void reload();
    virtual void refill();

    virtual void anacron();

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
    const char* getName();

    weapon_shot_t  shot;

    char name[16];

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

    static const uint8_t COOLDOWN_RANDOM_PERCENT = 10;
};

#endif
