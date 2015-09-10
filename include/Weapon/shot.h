#ifndef SHOT_H
#define SHOT_H

typedef uint8_t shot_t;

typedef struct weapon_shot {
    shot_t shot;
    uint8_t type;
} weapon_shot_t;

#define NULL_SHOT (shot_t) 0xffff

// Shot Flags
// bit0 Shot type (damage/heal)
const uint8_t WF_TYPE_HEAL =      0b00010000;

// bit1 Damage allies
const uint8_t WF_TARGET_ALLIES =  0b00001000;
// bit2 Heal enemies
const uint8_t WF_TARGET_ENEMIES = 0b00000100;

// Filters
const uint8_t WF_TEAM =           0b01100000;
const uint8_t WF_DAMAGE =         0b00000011;

const uint8_t WS_TEAM = 5;

// Values for damage field
const uint8_t WV_DAMAGE_1 =       0b00000000;
const uint8_t WV_DAMAGE_5 =       0b00000001;
const uint8_t WV_DAMAGE_10 =      0b00000010;
const uint8_t WV_DAMAGE_100 =     0b00000011;
// Last bit is unused

const uint8_t WV_DAMAGES[] = {1, 5, 10, 100};

#define WV_DAMAGE(shot) WV_DAMAGES[(shot & WF_DAMAGE)]
#define WV_TEAM(shot) ((shot & WF_TEAM) >> 5)

/* Little explanation about damages:
 * Last 2 bits of the "shot" bitmap are used to define how much damage deals that shot.
 * For 0b00 it does 1 damage, 0b01 = 5, 0b10 = 10 and 0b11 = 100. The damage is stored in constants WV_DAMAGE_X.
 * To get the reverse lookup, the WV_DAMAGE(shot) macro simply masks and shifts relevant bits and ask the array.
 */

#endif
