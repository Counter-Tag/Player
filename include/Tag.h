#ifndef TAG_H
#define TAG_H

#include <Arduino.h>
#include "Player/Player.h"
#include "Player/Trooper.h"
#include "Weapon/Weapon.h"
#include "Weapon/AK47.h"
#include "HUD.h"
#include "IR.h"
#include "common.h"

/**
 * @brief Glue code for HW and logic
 * @details Glues logic code (Player, Weapon) with hardware (low-level libraries and HUD).
 * 
 */
class Tag {
public:
    Tag();

    inline void loop();

    void checkReload();
    void checkSkill();
    void checkFire();
    void checkReceiveFire();
    void checkSpawnPoint();

    void spawn(uint8_t playerId, uint8_t weaponId);
    void spawn(const char* playerName, const char* weaponName);
    void init();
    void reload();
    void fire();
    void receiveShot(shot_t* shot);

private:
    Player* player;
    Weapon* weapon;
    HUD hud;
    //IR Library
    //Other HW stuff

    bool reloadBtnStatus;
    bool skillBtnStatus;
    bool fireBtnStatus;
};

#endif
