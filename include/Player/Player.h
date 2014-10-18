#ifndef PLAYER_H
#define PLAYER_H

#include <Arduino.h>

#include "../Weapon/Weapon.h"
#include "../HUD.h"

class Player {
public:
    Player();
    
    virtual bool canFire();
    virtual shot_t* fire();

    virtual void reload();
    virtual void refill();

    virtual void receiveShot(shot_t* shot);

    virtual void spawn();

    virtual bool isAlive();

    uint8_t getHp();
    void changeHp(uint8_t hp);    

    Weapon* getWeaponPtr();
    void setWeaponPtr(Weapon* weapon);

    bool hasAutomaticWeapon();

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

    HUD hud;
    Weapon* weapon;

    void (**outModifiers)(weapon_shot_t* wshot);
    void (**inModifiers)(shot_t* shot);

    uint8_t outModifiersSize;
    uint8_t inModifiersSize;
};

#endif
