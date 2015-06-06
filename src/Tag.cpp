#include "../include/Tag.h"

Tag::Tag() : audio(), hud(), ir() {
    pinMode(RELOAD_PIN, INPUT);
    pinMode(FIRE_PIN, INPUT);
    pinMode(SKILL_PIN, INPUT);
    pinMode(TEAM_PIN, INPUT);
    pinMode(POT_SELECT_PIN, OUTPUT);

    digitalWrite(RELOAD_PIN, HIGH);
    digitalWrite(FIRE_PIN, HIGH);
    digitalWrite(SKILL_PIN, HIGH);
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
    print_event("[CORE] Spawned %s with an %s.", player->getClassName(), player->getWeaponName());
    hud.updateHp(player->getHp());
    hud.updateAmmo(player->getWeaponMagazineAmmo(), player->getWeaponAmmo());
    hud.updateClass(player->getClassName());
    hud.updateWeapon(player->getWeaponName());

    audio.init();
    audio.playWeapon(player->getWeaponName());
}

void Tag::fire() {
    seedRNG();
    if (player->canFire()) {
        print_debug("[CORE] Player firing.");
        audio.stop();
        ir.fire(*player->fire());
        hud.updateAmmo(player->getWeaponMagazineAmmo(), player->getWeaponAmmo());
        audio.playFire();
    }
}

void Tag::reload() {
    seedRNG();
    if (player->canReload()) {
        print_debug("[CORE] Player reloading.");
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
}


void Tag::checkReload() {
    if (!digitalRead(RELOAD_PIN)) {
        if (!reloadBtnStatus) {
            print_debug("[CORE] Reload button pressed.");
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
            print_debug("[CORE] Fire button pressed.");
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
            print_debug("[CORE] Skill button pressed.");
            //player->activateSkill();
        }

        skillBtnStatus = true;
    } else {
        skillBtnStatus = false;
    }
}

void Tag::checkReceiveFire() {
    shot_t shot = ir.getShot();

    if (player->isAlive()) {
        if (shot != NULL_SHOT) {
            print_event("[CORE] Received shot: %x.", (uint8_t) shot);
            seedRNG();
            player->receiveShot(shot);
            hud.updateHp(player->getHp());
        }

        if (!player->isAlive()) {
            audio.playDeath();
        }
    }
}

void Tag::seedRNG() {
    print_debug("[CORE] Seeding RNG with %lu.", millis());
    srand(millis());
}
