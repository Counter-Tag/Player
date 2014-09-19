 #include "../include/Weapon/weapon_factory.h"

Weapon* create_weapon(uint8_t id) {
    if (id == 0x00) {
        return new AK47();
    }

    return NULL;
}

Weapon* create_weapon(const char* name) {
    if (!strcmp(name, "AK47")) {
        return create_weapon((uint8_t) 0x00);
    }

    return NULL;
}
