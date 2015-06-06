#include "../include/HUD.h"

HUD::HUD() : lcd(DISPLAY_PIN_RS, DISPLAY_PIN_E, DISPLAY_PIN_D4, DISPLAY_PIN_D5, DISPLAY_PIN_D6, DISPLAY_PIN_D7) {
    this->lcd.createChar(0, HUD::heart);
    this->lcd.createChar(1, HUD::bullet);
    this->lcd.createChar(2, HUD::skull);
    this->lcd.begin(HUD::cols, HUD::rows = 2);

    ContextProvider::set("HUD", this);

    lcd.setCursor(0, 0);
    lcd.write((uint8_t) 0);
    lcd.write(':');

    lcd.setCursor(8, 0);
    lcd.write((uint8_t) 1);
    lcd.write(':');

    this->updateHp(0);
    this->updateAmmo(0, 0);
}

void HUD::updateHp(int hp) {
  sprintf(this->buf, ":%i%%  ", hp);

  lcd.setCursor(0, 0);
  lcd.write(hp == 0 ? (uint8_t) 2 : (uint8_t) 0);
  lcd.print(this->buf);
}

void HUD::updateAmmo(int magazine, int total) {
  sprintf(this->buf, "%i/%i ", magazine, total);

  lcd.setCursor(8 + 2, 0); // 8 + 2: First row, second zone, skip bullet and colon characters.
  lcd.print(this->buf);
}

void HUD::updateWeapon(const char* weapon) {
  lcd.setCursor(8, 1);
  lcd.print(weapon);
}

void HUD::updateClass(const char* cls) {
  lcd.setCursor(0, 1);
  lcd.print(cls);
}

uint8_t HUD::cols = 16;
uint8_t HUD::rows = 2;

uint8_t HUD::heart[] = {
  0b00000,
  0b01010,
  0b11111,
  0b11111,
  0b01110,
  0b00100,
  0b00000,
  0b00000
};

uint8_t HUD::bullet[] = {
  0b00100,
  0b01110,
  0b11111,
  0b11111,
  0b11111,
  0b00000,
  0b11111,
  0b00000
};

uint8_t HUD::skull[] = {
  0b01110,
  0b10001,
  0b11011,
  0b10001,
  0b01110,
  0b01010,
  0b10001,
  0b00000
};
