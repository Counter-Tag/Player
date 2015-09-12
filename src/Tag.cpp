#include "../include/Tag.h"

Tag* Tag::inst = NULL;

Tag::Tag() : audio(), hud(), ir(), commander(this) {
    pinMode(RELOAD_PIN, INPUT);
    pinMode(FIRE_PIN, INPUT);
    pinMode(SKILL_PIN, INPUT);
    pinMode(POT_SELECT_PIN, OUTPUT);

    digitalWrite(RELOAD_PIN, HIGH);
    digitalWrite(FIRE_PIN, HIGH);
    digitalWrite(SKILL_PIN, HIGH);
    digitalWrite(POT_SELECT_PIN, HIGH);

    reloadBtnStatus = false;
    fireBtnStatus = false;
    skillBtnStatus = false;
    spawnBtnStatus = false;

    player = NULL;
    weapon = NULL;

    Tag::inst = this;
}


void Tag::updateClass(uint8_t classId) {
    delete player;

    switch (classId) {
        case 0x00:
        player = new Trooper();
        print_debug("Created player %s", player->getClassName());
        break;
        default:
        player = NULL;
        print_error("Unknown class 0x%x", classId);
    }

    spawn();
}

void Tag::updateWeapon(uint8_t weaponId) {
    delete weapon;

    switch (weaponId) {
        case 0x00:
        weapon = new AK47();
        print_debug("Created weapon %s", weapon->getName());
        break;

        default:
        weapon = NULL;
        print_error("Unknown class 0x%x", weaponId);
    }

    spawn();
}

void Tag::updateTeam(uint8_t team) {
    player->setTeam(team);
}

void Tag::spawn() {
    if (player != NULL && weapon != NULL) {
        player->setWeapon(weapon);
        player->spawn();

        print_event("Spawned %s with an %s.", player->getClassName(), player->getWeaponName());

        hud.updateHp(player->getHp());
        hud.updateAmmo(player->getWeaponMagazineAmmo(), player->getWeaponAmmo());
        hud.updateClass(player->getClassName());
        hud.updateWeapon(player->getWeaponName());

        audio.playWeapon(player->getWeaponName());
    } else {
        print_error("Refusing, partial initialization.");
    }
}

void Tag::fire() {
    seedRNG();
    if (player->canFire()) {
        print_debug("Firing.");
        audio.stop();
        ir.send((ir_pkt_t) *player->fire());
        hud.updateAmmo(player->getWeaponMagazineAmmo(), player->getWeaponAmmo());
        audio.playFire();
    }
}

void Tag::reload() {
    seedRNG();
    if (player->canReload()) {
        print_debug("Reloading.");
        player->reload();
        hud.updateAmmo(player->getWeaponMagazineAmmo(), player->getWeaponAmmo());
        audio.playReload();
    }
}


void Tag::loop() {
    checkReload();
    checkSkill();
    checkFire();
    checkIR();
}


void Tag::checkReload() {
    if (!digitalRead(RELOAD_PIN)) {
        if (!reloadBtnStatus) {
            print_debug("Reload button pressed.");
            reload();
        }

        reloadBtnStatus = true;
    } else {
        reloadBtnStatus = false;
    }
}

void Tag::checkFire() {
    if (!digitalRead(FIRE_PIN)) {
        if (!fireBtnStatus || player->getWeaponType() == Weapon::TYPE_AUTO) {
            print_debug("Fire button pressed.");
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
            print_debug("Skill button pressed.");
            //player->activateSkill();
        }

        skillBtnStatus = true;
    } else {
        skillBtnStatus = false;
    }
}

void Tag::checkIR() {
    ir_pkt_t packet = ir.recv();

    if (packet != IR::NULL_PKT) {
        seedRNG();
        print_event("Received packet 0x%x.", (uint8_t) packet);

        if ((packet & Commander::CF_CMD) >> Commander::CV_CMD) {
            commander.run(packet);
        } else {
            if (player->isAlive()) {
                player->receiveShot(packet);
                hud.updateHp(player->getHp());

                if (!player->isAlive()) {
                    audio.playDeath();
                }
            }
        }
    }
}

Player* Tag::getPlayer() {
    return this->player;
}

Audio* Tag::getAudio() {
    return &(this->audio);
}

HUD* Tag::getHud() {
    return &(this->hud);
}

IR* Tag::getIr() {
    return &(this->ir);
}

Tag* Tag::getInstance() {
    return Tag::inst;
}

inline void Tag::seedRNG() {
    print_debug("Seeding RNG with %lu.", millis());
    srand(millis());
}
