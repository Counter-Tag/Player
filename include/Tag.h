#ifndef TAG_H
#define TAG_H

#include <Arduino.h>
#include "Player/Player.h"
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

private:
    Player* player;
    HUD hud;
    //IR Library
    //Other HW stuff

    bool reloadBtnStatus;
    bool skillBtnStatus;
    bool fireBtnStatus;
};

#endif
