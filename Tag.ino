#include "include/Tag.h"

Tag tag;
TMRpcm tmrpcm;

void setup() {
    Serial.begin(9600);
    SD.begin(SDCS_PIN);

    Serial.println("Spawning player...");
    tag.spawn("Trooper", "AK47", 0);
}

void loop() {
    tag.loop();
}
