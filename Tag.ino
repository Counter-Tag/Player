#include "include/Tag.h"

Tag tag;
shot_t enemyDmgShot;
shot_t allyHealShot;

void setup() {
    enemyDmgShot = {10, WF_DAMAGE_ENEMIES | 0b00000100};
    allyHealShot = {5, WF_DAMAGE_ENEMIES | WF_HEAL_ALLIES};

    Serial.begin(9600);

    Serial.println("Spawning player...");
    tag.spawn("Trooper", "AK47");
}

void loop() {
    tag.fire();
    //tag.receiveShot(&enemyDmgShot);
    delay(250);
}
