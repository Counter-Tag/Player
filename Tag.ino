#include "include/Tag.h"

Tag tag;
TMRpcm tmrpcm;

void setup() {
    Serial.begin(9600);
    SD.begin(SDCS_PIN);

    Serial.print("Spawning player team ");
    Serial.println(digitalRead(TEAM_PIN));
    tag.spawn("Trooper", "AK47", digitalRead(TEAM_PIN));
}

void loop() {
    tag.loop();
}
