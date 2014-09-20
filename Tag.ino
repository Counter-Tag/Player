#include "include/Player/Player.h"
#include "include/Player/player_factory.h"

#include "include/Weapon/Weapon.h"
#include "include/Weapon/weapon_factory.h"

Player* player;

void setup() {
    shot_t enemyDmgShot = {10, WF_DAMAGE_ENEMIES | 0b00000100};
    shot_t allyHealShot = {5, WF_DAMAGE_ENEMIES | WF_HEAL_ALLIES};
    shot_t* firedShot;

    Serial.begin(9600);

    Serial.println("Creating new player...");
    
    player = create_player("Trooper");
    player->setWeaponPtr(create_weapon("AK47"));

    player->setTeam(0);
    player->spawn();
    
    Serial.print("Created new player with team ");
    Serial.print(player->getTeam());
    Serial.print(" and hp ");
    Serial.println(player->getHp());

    /*
    player->receiveShot(&enemyDmgShot);
    Serial.println(player->getHp());
    player->receiveShot(&allyHealShot);
    Serial.println(player->getHp());
    */

    firedShot = player->fire();
    Serial.print("Fired shot with ");
    Serial.print(firedShot->damage);
    Serial.print(" damage and flags ");
    Serial.println(firedShot->flags);
}

void loop() {
    if (player->canFire()) {
        Serial.println("Fire!");
        player->fire();
        Serial.print(player->getWeaponPtr()->getMagazineAmmo());
        Serial.println(" bullets left.");
    }

    delay(50);
}
