#include "include/Tag.h"

Tag* tag;

void setup() {
    Serial.begin(9600);
    tag = new Tag();
    tag->spawn("Trooper", "AK47", digitalRead(TEAM_PIN));
}

void loop() {
    tag->loop();
}
