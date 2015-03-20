#include "../../include/Player/Player.h"

Player::Player(Weapon* weapon) {
    this->weapon = weapon;
}

bool Player::canFire() {
    return this->isAlive() && this->weapon->canFire();
}

bool Player::canReload() {
    return this->isAlive() && this->weapon->canReload();
}

shot_t* Player::fire() {
    memcpy(&this->weapon_shot, this->weapon->fire(), sizeof(weapon_shot_t));
    this->weapon_shot.shot |= (this->team << 6) & WF_TEAM;
    this->applyOutModifiers(&this->weapon_shot);

    return (shot_t*) &this->weapon_shot;
}

void Player::receiveShot(shot_t shot) {
    this->applyInModifiers(&shot);

    if (((shot & WF_TEAM) >> 6) == this->team) {
        if (shot & WF_TARGET_ALLIES) {
            Serial.println("Received ally shot");
            this->changeHp(WV_DAMAGE(shot) * (shot & WF_TYPE_HEAL ? 1 : -1));
        }
    } else {
        if (shot & WF_TARGET_ENEMIES) {
            Serial.println("Received enemy shot");
            this->changeHp(WV_DAMAGE(shot) * (shot & WF_TYPE_HEAL ? 1 : -1)); 
        }
    }
}

void Player::reload() {
    this->weapon->reload();
}

void Player::refill() {
    this->weapon->refill();
}

uint8_t Player::getMaxHp() {
    return this->maxHp;
}

uint8_t Player::getHp() {
    return this->hp;
}

void Player::changeHp(int8_t hp) {
    if (this->hp + hp > this->maxHp) {
        this->hp = this->maxHp;
    } else if (this->hp + hp < 0) {
        this->hp = 0;
    } else {
        this->hp += hp;
    }
}

bool Player::isAlive() {
    return this->hp != 0;
}

String Player::getClassName() {
    return this->name;
}

void Player::spawn() {
    this->hp = this->maxHp;
    this->refill();
}

Weapon* Player::getWeaponPtr() {
    return this->weapon;
}
void Player::setWeaponPtr(Weapon* weapon) {
    this->weapon = weapon;
}

uint8_t Player::getWeaponAmmo() {
    return this->weapon->getAmmo();
}

uint8_t Player::getWeaponMagazineAmmo() {
    return this->weapon->getMagazineAmmo();
}

uint8_t Player::getWeaponType() {
    return this->weapon->getType();
}

String Player::getWeaponName() {
    return this->weapon->getName();
}

uint8_t Player::getTeam() {
    return this->team;
}
void Player::setTeam(uint8_t team) {
    this->team = team;
}

void Player::applyInModifiers(shot_t* shot) {
    if (this->inModifiersSize != 0)  {
        for (int i = 0; i < inModifiersSize; i++) {
            (*this->inModifiers[i])(shot);
        }
    }
}

void Player::applyOutModifiers(weapon_shot_t* wshot) {
    if (this->outModifiersSize != 0)  {
        for (int i = 0; i < outModifiersSize; i++) {
            (*this->outModifiers[i])(wshot);
        }
    }
}

void Player::initOutModifiers(uint8_t no) {
    this->outModifiersSize = no;
    
    if (no != 0) {
        this->outModifiers = (void(**)(weapon_shot_t*)) malloc(sizeof(void(*)(weapon_shot_t*)) * this->outModifiersSize);
    }
}

void Player::initInModifiers(uint8_t no) {
    this->inModifiersSize = no;
    
    if (no != 0) {
        this->inModifiers = (void(**)(shot_t*)) malloc(sizeof(void(*)(shot_t*)) * this->inModifiersSize);
    }
}
