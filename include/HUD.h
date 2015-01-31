#ifndef HUD_H
#define HUD_H

#include <LiquidCrystal.h>
#include "common.h"

class HUD {
public:
    HUD();

    void init();
    void updateHp(int hp);
    void updateAmmo(int magazine, int total);
    void updateWeapon(String weapon);
    void updateClass(String cls);

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
