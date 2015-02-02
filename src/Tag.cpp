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
    audio.playWeapon(player->getWeaponName());
}

void Tag::fire() {
    if (player->canFire()) {
        Serial.println("Fire!");
        ir.shoot(player->fire());
        hud.updateAmmo(player->getWeaponMagazineAmmo(), player->getWeaponAmmo());
        audio.playFire();
    }
}

void Tag::reload() {
    if (player->canReload()) {
        player->reload();
        hud.updateAmmo(player->getWeaponMagazineAmmo(), player->getWeaponAmmo());
        audio.playReload();
    }
}

void Tag::receiveShot(shot_t* shot) {
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
    shot_t* shot;

    bool previouslyAlive = player->isAlive();

    if ((shot = ir.receiveShot())) {
        player->receiveShot(shot);
        hud.updateHp(player->getHp());
    }

    if (previouslyAlive && !player->isAlive()) {
        audio.playDeath();
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

