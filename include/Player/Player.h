#ifndef PLAYER_H
#define PLAYER_H

#include <Arduino.h>
#include "../Debug.h"
#include "../Weapon/Weapon.h"

class Player {
public:
    Player(Weapon* weapon);
    
    virtual bool canFire();
    virtual bool canReload();
    virtual shot_t* fire();

    virtual void reload();
    virtual void refill();

    virtual void receiveShot(shot_t shot);

    virtual void spawn();

    virtual bool isAlive();

    virtual void anacron();

    const char* getClassName();

    uint8_t getMaxHp();
    uint8_t getHp();
    void changeHp(int8_t hp);

    Weapon* getWeaponPtr();
    void setWeaponPtr(Weapon* weapon);

    uint8_t getWeaponAmmo();
    uint8_t getWeaponMagazineAmmo();
    uint8_t getWeaponType();
    const char* getWeaponName();

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

    char name[16];

    static const uint8_t HP_RANDOM_PERCENT = 20;
};

#endif
