#include "include/Tag.h"

Tag* tag;

void setup() {
    Serial.begin(9600);
    tag = new Tag();
    tag->updateClass(0x00);
    tag->updateWeapon(0x00);
}

void loop() {
    tag->loop();
}
