#include "../include/Tag.h"

Tag::Tag() : hud(), tmrpcm(), ir() {
    pinMode(RELOAD_PIN, INPUT);
    pinMode(FIRE_PIN, INPUT);
    pinMode(SKILL_PIN, INPUT);
    pinMode(SPAWN_PIN, INPUT);
    pinMode(POT_SELECT_PIN, OUTPUT);

    digitalWrite(RELOAD_PIN, HIGH);
    digitalWrite(FIRE_PIN, HIGH);
    digitalWrite(SKILL_PIN, HIGH);
    digitalWrite(SPAWN_PIN, HIGH);
    digitalWrite(POT_SELECT_PIN, HIGH);

    this->reloadBtnStatus = false;
    this->fireBtnStatus = false;
    this->skillBtnStatus = false;
    this->spawnBtnStatus = false;

    tmrpcm.speakerPin = SPKR_PIN;
}

void Tag::spawn(uint8_t playerId, uint8_t weaponId) {
    if (weaponId == 0x00) {
        this->weapon = new AK47();
    }

    if (playerId == 0x00) {
        this->player = new Trooper(this->weapon);
    }

    this->init();
}

void Tag::spawn(const char* playerName, const char* weaponName, uint8_t team) {
    if (!strcmp(weaponName, "AK47")) {
        this->weapon = new AK47();
    }

    if (!strcmp(playerName, "Trooper")) {
        this->player = new Trooper(this->weapon);
        this->player->setTeam(team);
    }

    this->init();
}

void Tag::init() {
    this->player->spawn();
    Serial.print("Player hp: ");
    Serial.println(this->player->getHp());
    this->tmrpcm.play("AK47.WAV");
    this->hud.updateHp(this->player->getHp());
    this->hud.updateAmmo(this->player->getWeaponMagazineAmmo(), this->player->getWeaponAmmo());
    this->hud.updateClass(this->player->getClassName());
    this->hud.updateWeapon(this->player->getWeaponName());
}

void Tag::fire() {
    if (this->player->canFire()) {
        Serial.println("Fire!");
        ir.shoot(this->player->fire());
        this->hud.updateAmmo(this->player->getWeaponMagazineAmmo(), this->player->getWeaponAmmo());
        tmrpcm.stopPlayback();
        tmrpcm.play("SHOT.WAV");
    }
}

void Tag::reload() {
    if (this->player->canReload()) {
        this->player->reload();
        tmrpcm.stopPlayback();
        this->tmrpcm.play("RELOAD.WAV");
        this->hud.updateAmmo(this->player->getWeaponMagazineAmmo(), this->player->getWeaponAmmo());
    }
}

void Tag::receiveShot(shot_t* shot) {
}

void Tag::loop() {
    this->checkReload();
    this->checkSkill();
    this->checkFire();
    this->checkReceiveFire();
    this->checkSpawnPoint();
}


void Tag::checkReload() {
    if (!digitalRead(RELOAD_PIN)) {
        if (!reloadBtnStatus) {
            this->reload();
        }

        this->reloadBtnStatus = true;
    } else {
        this->reloadBtnStatus = false;
    }
}

void Tag::checkFire() {
    if (!digitalRead(FIRE_PIN)) {
        if (!fireBtnStatus || player->getWeaponType()) {
            this->fire();
        }

        this->fireBtnStatus = true;
    } else {
        this->fireBtnStatus = false;
    }
}

void Tag::checkSkill() {
    if (!digitalRead(SKILL_PIN)) {
        if (!skillBtnStatus) {
            //player->activateSkill();
        }

        this->skillBtnStatus = true;
    } else {
        this->skillBtnStatus = false;
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
        tmrpcm.play("DEATH.WAV");
    }
}

void Tag::checkSpawnPoint() {
    if (!digitalRead(SPAWN_PIN)) {
        if (!spawnBtnStatus) {
            this->init();
        }
        this->spawnBtnStatus = true;
    } else {
        this->spawnBtnStatus = false;
    }
}

