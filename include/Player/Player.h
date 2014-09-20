#ifndef PLAYER_H
#define PLAYER_H

#include <Arduino.h>

#include "../Weapon/Weapon.h"

class Player {
public:
    Player();
    
    virtual bool canFire();
    virtual shot_t* fire();

    virtual void receiveShot(shot_t* shot);

    virtual uint8_t getHp();
    virtual void changeHp(uint8_t hp);
    
    virtual bool isAlive();

    virtual void spawn();

    Weapon* getWeaponPtr();
    void setWeaponPtr(Weapon* weapon);

    uint8_t getTeam();
    void setTeam(uint8_t team);

    weapon_shot_t weapon_shot;

protected:
    void applyInModifiers(shot_t* shot);
    void applyOutModifiers(weapon_shot_t* wshot);

    void initInModifiers(uint8_t no);
    void initOutModifiers(uint8_t no);

    uint8_t maxHp;
    uint8_t hp;

    uint8_t team;

    Weapon* weapon;

    void (**outModifiers)(weapon_shot_t* wshot);
    void (**inModifiers)(shot_t* shot);

    uint8_t outModifiersSize;
    uint8_t inModifiersSize;
};

#endif
