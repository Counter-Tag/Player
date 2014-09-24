.SUBLIME_TARGETS: all reset upload clean

ARDUINO_SKETCHBOOK = /home/roobre/Arduino/
AVRDUDE = /usr/bin/avrdude
AVRDUDE_CONF = /etc/avrdude.conf
AVR_TOOLS_PATH = /usr/bin/

BOARD_TAG = nano328
ARDUINO_LIBS = LiquidCrystal

#CXXFLAGS_STD = -std=gnu++11

SOURCE_FOLDERS = src src/Player src/Weapon

include /home/roobre/Devel/Arduino-Makefile/Arduino.mk
