#include "../../include/Player/Player.h"

Player::Player() {
    this->weapon = NULL;
}

Player::~Player() {
    if (this->inModifiersSize)
        free(this->inModifiers);
    if (this->outModifiersSize)
        free(this->outModifiers);
}

bool Player::canFire() {
    return this->isAlive() && this->weapon->canFire();
}

bool Player::canReload() {
    return this->isAlive() && this->weapon->canReload();
}

shot_t* Player::fire() {
    memcpy(&this->weapon_shot, this->weapon->fire(), sizeof(weapon_shot_t));
    this->weapon_shot.shot |= (this->team << WS_TEAM) & WF_TEAM;
    this->applyOutModifiers(&this->weapon_shot);

    print_event("[PLAYER] Firing 0x%x", this->weapon_shot);

    return (shot_t*) &this->weapon_shot;
}

void Player::receiveShot(shot_t shot) {
    this->applyInModifiers(&shot);

    print_event("[PLAYER] Received shot 0x%x.", (uint8_t) shot);
    int8_t damage = WV_DAMAGE(shot) * (shot & WF_TYPE_HEAL ? 1 : -1);

    if (WV_TEAM(shot) == this->team) {
        print_debug("[PLAYER] Shot is friendly.");
        if (shot & WF_TARGET_ALLIES) {
            print_event("[PLAYER] Dealing %d friendly damage", damage);
            this->changeHp(damage);
        }
    } else {
        print_debug("[PLAYER] Shot is hostile.");
        if (shot & WF_TARGET_ENEMIES) {
            print_event("[PLAYER] Dealing %d hostile damage", damage);
            this->changeHp(damage); 
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
        this->hp += hp * (1 + (float) (rand() % (HP_RANDOM_PERCENT * 2) - HP_RANDOM_PERCENT) / 100);
    }

    print_event("[PLAYER] HP changed to %u", this->hp);
}

bool Player::isAlive() {
    return this->hp != 0;
    // Debugging
    //return true;
}

const char* Player::getClassName() {
    return this->name;
}

void Player::spawn() {
    this->hp = this->maxHp;
    this->refill();
}

Weapon* Player::getWeapon() {
    return this->weapon;
}
void Player::setWeapon(Weapon* weapon) {
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

const char* Player::getWeaponName() {
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
    } else {
        this->outModifiers = NULL;
    }
}

void Player::initInModifiers(uint8_t no) {
    this->inModifiersSize = no;
    
    if (no != 0) {
        this->inModifiers = (void(**)(shot_t*)) malloc(sizeof(void(*)(shot_t*)) * this->inModifiersSize);
    } else {
        this->outModifiers = NULL;
    }
}

void Player::anacron() {}
