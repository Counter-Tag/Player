#ifndef TAG_H
#define TAG_H

#include <Arduino.h>
#include "configuration.h"
#include "Debug.h"
#include "Player/Player.h"
#include "Player/Trooper.h"
#include "Weapon/Weapon.h"
#include "Weapon/AK47.h"
#include "HUD.h"
#include "IR.h"
#include "Audio.h"

/**
 * @brief Glue code for HW and logic
 * @details Glues logic code (Player, Weapon) with hardware (low-level libraries and HUD).
 * 
 */
class Tag {
public:
    Tag();

    void loop();

    void checkReload();
    void checkSkill();
    void checkFire();
    void checkReceiveFire();

    void spawn(uint8_t playerId, uint8_t weaponId);
    void spawn(const char* playerName, const char* weaponName, uint8_t team);
    void init();
    void reload();
    void fire();

    Player* getPlayer();
    Weapon* getWeapon();
    Audio*  getAudio();
    HUD*    getHud();
    IR*     getIr();

    static Tag* getInstance();
    static inline void seedRNG();

private:
    static Tag* inst;

    Player* player;
    Weapon* weapon;
    Audio audio;
    HUD hud;
    IR ir;

    bool reloadBtnStatus;
    bool skillBtnStatus;
    bool fireBtnStatus;
    bool spawnBtnStatus;
};

#endif
