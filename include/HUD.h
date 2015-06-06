#ifndef HUD_H
#define HUD_H

#include <LiquidCrystal.h>
#include "configuration.h"
#include "Debug.h"
#include "ContextProvider.h"

class HUD {
public:
    HUD();

    void updateHp(int hp);
    void updateAmmo(int magazine, int total);
    void updateWeapon(const char* weapon);
    void updateClass(const char* cls);

private:
    static uint8_t cols;
    static uint8_t rows;

    static uint8_t heart[8];
    static uint8_t bullet[8];
    static uint8_t skull[8];

    LiquidCrystal lcd;
    char buf[16];

    void clearRow(int row);
};

#endif
