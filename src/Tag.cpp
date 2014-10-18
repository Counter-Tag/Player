#include "../include/Tag.h"

Tag::Tag() : hud() {
    pinMode(RELOAD_PIN, INPUT);
    pinMode(FIRE_PIN, INPUT);
    pinMode(SKILL_PIN, INPUT);

    this->reloadBtnStatus = false;
    this->fireBtnStatus = false;
    this->skillBtnStatus = false;
}

void Tag::loop() {
    this->checkReload();
    this->checkSkill();
    this->checkFire();
    this->checkReceiveFire();
}


void Tag::checkReload() {
    if (digitalRead(RELOAD_PIN)) {
        if (!reloadBtnStatus) {
            this->player->reload();
            this->hud.updateAmmo(this->player->getWeaponMagazineAmmo(), this->player->getWeaponAmmo());
        }

        this->reloadBtnStatus = true;
    } else {
        this->reloadBtnStatus = false;
    }
}

void Tag::checkFire() {
    if (digitalRead(FIRE_PIN)) {
        if (!fireBtnStatus || player->hasAutomaticWeapon()) {
            this->player->fire();
            this->hud.updateAmmo(this->player->getWeaponMagazineAmmo(), this->player->getWeaponAmmo());
        }

        this->fireBtnStatus = true;
    } else {
        this->fireBtnStatus = false;
    }
}

void Tag::checkSkill() {
    if (digitalRead(SKILL_PIN)) {
        if (!skillBtnStatus) {
            //player->activateSkill();
        }

        this->skillBtnStatus = true;
    } else {
        this->skillBtnStatus = false;
    }
}

void Tag::checkReceiveFire() {
    // Check IR Library for buffer
    // Copy buffer to shot_t* shot
    // this->player->receiveShot(shot);
    this->hud.updateHp(100 * this->player->getHp() / this->player->getMaxHp());
}

void Tag::checkSpawnPoint() {
    // Check for Spawn Point connection
    // free(this->player->getWeaponPtr());
    // free(this->player);
    // this->player = create_player(conndata.player_id);
    // this->player->setWeaponPtr(create_weapon(conndata.weapon_id));
    // this->player->spawn();
    // this->hud.updateAmmo(this->player->getWeaponMagazineAmmo(), this->player->getWeaponAmmo());

}
