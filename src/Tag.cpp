#include "../include/Tag.h"

Tag::Tag() : audio(), hud(), ir() {
    pinMode(RELOAD_PIN, INPUT);
    pinMode(FIRE_PIN, INPUT);
    pinMode(SKILL_PIN, INPUT);
    pinMode(SPAWN_PIN, INPUT);
    pinMode(TEAM_PIN, INPUT);
    pinMode(POT_SELECT_PIN, OUTPUT);

    digitalWrite(RELOAD_PIN, HIGH);
    digitalWrite(FIRE_PIN, HIGH);
    digitalWrite(SKILL_PIN, HIGH);
    digitalWrite(SPAWN_PIN, HIGH);
    digitalWrite(TEAM_PIN, HIGH);
    digitalWrite(POT_SELECT_PIN, HIGH);

    reloadBtnStatus = false;
    fireBtnStatus = false;
    skillBtnStatus = false;
    spawnBtnStatus = false;
}

void Tag::spawn(uint8_t playerId, uint8_t weaponId) {
    if (weaponId == 0x00) {
        weapon = new AK47();
    }

    if (playerId == 0x00) {
        player = new Trooper(weapon);
    }

    init();
}

void Tag::spawn(const char* playerName, const char* weaponName, uint8_t team) {
    if (!strcmp(weaponName, "AK47")) {
        weapon = new AK47();
    }

    if (!strcmp(playerName, "Trooper")) {
        player = new Trooper(weapon);
        player->setTeam(team);
    }

    init();
}

void Tag::init() {
    player->spawn();
    Serial.print("Player hp: ");
    Serial.println(player->getHp());
    hud.updateHp(player->getHp());
    hud.updateAmmo(player->getWeaponMagazineAmmo(), player->getWeaponAmmo());
    hud.updateClass(player->getClassName());
    hud.updateWeapon(player->getWeaponName());

    if (audio.init()) {
        Serial.println("Audio initialized.");
    } else {
        Serial.println("Error initializing audio.");
    }
    audio.playWeapon(player->getWeaponName());
}

void Tag::fire() {
    seedRNG();
    if (player->canFire()) {
        Serial.println("Fire!");
        audio.stop();
        ir.fire(*player->fire());
        hud.updateAmmo(player->getWeaponMagazineAmmo(), player->getWeaponAmmo());
        audio.playFire();
    }
}

void Tag::reload() {
    seedRNG();
    if (player->canReload()) {
        player->reload();
        hud.updateAmmo(player->getWeaponMagazineAmmo(), player->getWeaponAmmo());
        audio.playReload();
    }
}


void Tag::loop() {
    checkReload();
    checkSkill();
    checkFire();
    checkReceiveFire();
    checkSpawnPoint();
}


void Tag::checkReload() {
    if (!digitalRead(RELOAD_PIN)) {
        if (!reloadBtnStatus) {
            reload();
        }

        reloadBtnStatus = true;
    } else {
        reloadBtnStatus = false;
    }
}

void Tag::checkFire() {
    if (!digitalRead(FIRE_PIN)) {
        if (!fireBtnStatus || player->getWeaponType()) {
            fire();
        }

        fireBtnStatus = true;
    } else {
        fireBtnStatus = false;
    }
}

void Tag::checkSkill() {
    if (!digitalRead(SKILL_PIN)) {
        if (!skillBtnStatus) {
            //player->activateSkill();
        }

        skillBtnStatus = true;
    } else {
        skillBtnStatus = false;
    }
}

void Tag::checkReceiveFire() {
    shot_t shot;

    if (player->isAlive()) {
        shot = ir.getShot();
        
        if (shot != NULL_SHOT) {
            Serial.println((uint8_t) shot, BIN);
            seedRNG();
            player->receiveShot(shot);
            hud.updateHp(player->getHp());
        }

        if (!player->isAlive()) {
            audio.playDeath();
        }
    }
}

void Tag::checkSpawnPoint() {
    if (!digitalRead(SPAWN_PIN)) {
        if (!spawnBtnStatus) {
            init();
        }
        spawnBtnStatus = true;
    } else {
        spawnBtnStatus = false;
    }
}

inline void Tag::seedRNG() {
    srand(millis());
}

