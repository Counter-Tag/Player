#include "../include/Player/Player.h"

shot_t* Player::fire() {
    memcpy(&this->weapon_shot, this->weapon->fire(), sizeof(weapon_shot_t));

    this->applyOutModifiers(&this->weapon_shot);

    return (shot_t*) &this->weapon_shot;
}

void Player::receiveShot(shot_t* shot) {
    this->applyInModifiers(shot);

    if (((shot->flags & WF_TEAM) >> 2) == this->team) {
        if (shot->flags & WF_DAMAGE_ALLIES) {
            Serial.println("Friendly fire!! Dealing damage.");
            this->changeHp(-shot->damage);
        } else if (shot->flags & WF_HEAL_ALLIES) {
            Serial.println("Friendly healing! Healing damage.");
            this->changeHp(shot->damage);
        }
    } else {
        Serial.println("Received enemy shot");
        if (shot->flags & WF_DAMAGE_ENEMIES) {
            Serial.println("Enemy fire! Dealing damage.");
            this->changeHp(-shot->damage);
        } else if (shot->flags & WF_HEAL_ENEMIES) {
            Serial.println("Enemy healing!! Healing damage.");
            this->changeHp(shot->damage);
        }
    }
}

bool Player::canFire() {
    return this->weapon->canFire();
}

uint8_t Player::getHp() {
    return this->hp;
}

void Player::changeHp(uint8_t hp) {
    this->hp += hp;

    if (this->hp > this->maxHp)
        this->hp = this->maxHp;
    else if (this->hp < 0)
        this->hp = 0;
}

bool Player::isAlive() {
    return this->hp != 0;
}

void Player::spawn() {
    this->hp = this->maxHp;
    if (this->weapon != NULL) {
        this->weapon->refill();
    }
}

Weapon* Player::getWeaponPtr() {
    return this->weapon;
}
void Player::setWeaponPtr(Weapon* weapon) {
    this->weapon = weapon;
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
