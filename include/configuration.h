#ifndef CONFIGURATION_H
#define CONFIGURATION_H

// Configuration

// Debug level:
//  0: Disabled
//  1: Error
//  2: Events
//  3: Info
#define CT_DEBUG 2

// Baud rate
const int BAUDRATE = 9600;


// Pins

const int INTR_PIN = 0; // IR receivers interrupt (means pin 2)
const int RECV_PIN = 2; // Same as above
const int SEND_PIN = 3; // IR LED

// const int SPAWN_PIN = 4; // Respawn trigger (no longer used)

const int RELOAD_PIN = 5; // Reload trigger
const int POT_SELECT_PIN = 6; // Only God(os) knows
const int SKILL_PIN = 7; // Skill trigger
const int FIRE_PIN = 8; // Fire trigger

const int SPKR_PIN = 9; // Forced on non-mega boards due to timer constraints

const int SDCS_PIN = 10; // Hardware SS pin
// PIN 11 is also used by the SD Card.

const int TEAM_PIN = 7; // Temporary workaround to hardset team on boot

// LCD connections
const int DISPLAY_PIN_E  = 14; // A0
const int DISPLAY_PIN_RS = 15; // A1
const int DISPLAY_PIN_D4 = 16; // A2
const int DISPLAY_PIN_D5 = 17; // A3
const int DISPLAY_PIN_D6 = 18; // A4
const int DISPLAY_PIN_D7 = 19; // A5

#endif
