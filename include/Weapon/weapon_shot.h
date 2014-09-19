#ifndef WEAPON_SHOT_H
#define WEAPON_SHOT_H

typedef struct weapon_shot {
    uint8_t damage;
    uint8_t flags;
    uint8_t type;
} weapon_shot_t;

typedef struct shot {
    uint8_t damage;
    uint8_t flags;
} shot_t;

// Weapon Flags
// bit0 Damage enemies
#define WF_DAMAGE_ENEMIES 0b10000000
// bit1 Damage allies
#define WF_DAMAGE_ALLIES  0b01000000

// bit2 Heal enemies
#define WF_HEAL_ENEMIES   0b00100000
// bit3 Heal allies
#define WF_HEAL_ALLIES    0b00010000

// bit4 & bit5: Reserved for team tag
// bit6 & bit7: Reserved for shot replays

// Filters
#define WF_TEAM   0b00001100
#define WF_REPLAY 0b00000011

#endif
