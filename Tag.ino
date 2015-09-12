#include "include/Tag.h"

Tag* tag;

void setup() {
    Serial.begin(9600);

    pinMode(TEAM_PIN, INPUT);
    digitalWrite(TEAM_PIN, HIGH);

    tag = new Tag();
    tag->updateClass(0x00);
    tag->updateWeapon(0x00);
    tag->updateTeam(digitalRead(TEAM_PIN));
}

void loop() {
    tag->loop();
}
