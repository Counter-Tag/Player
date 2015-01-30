#include "include/Tag.h"

Tag tag;

void setup() {
    shot_t enemyDmgShot = {10, WF_DAMAGE_ENEMIES | 0b00000100};
    shot_t allyHealShot = {5, WF_DAMAGE_ENEMIES | WF_HEAL_ALLIES};
    shot_t* firedShot;

    Serial.begin(9600);

    Serial.println("Spawning player...");
    tag.spawn("Trooper", "AK47");
}

void loop() {
    /*
    if (player->canFire()) {
        Serial.println("Fire!");
        player->fire();
        Serial.print(player->getWeaponMagazineAmmo());
        Serial.println(" bullets left.");
        hud.updateAmmo(player->getWeaponMagazineAmmo(), player->getWeaponAmmo());
    }

    delay(200);
    */
}
