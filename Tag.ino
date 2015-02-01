#include "include/Tag.h"

Tag tag;

void setup() {
    Serial.begin(9600);

    Serial.println("Spawning player...");
    tag.spawn("Trooper", "AK47", 0);
}

void loop() {
    tag.loop();
}
