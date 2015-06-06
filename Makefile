.SUBLIME_TARGETS: all reset upload clean

ARDUINO_SKETCHBOOK = /home/roobre/Arduino
AVRDUDE = /usr/bin/avrdude
AVRDUDE_CONF = /etc/avrdude.conf
AVR_TOOLS_PATH = /usr/bin

BOARD_TAG = nano
BOARD_SUB = atmega328
ARDUINO_LIBS = LiquidCrystal TMRpcm SD SPI

SOURCE_FOLDERS = src src/Player src/Weapon

LOCAL_C_SRCS = $(foreach dir,$(SOURCE_FOLDERS),$(wildcard $(dir)/*.c))
LOCAL_CPP_SRCS = $(foreach dir,$(SOURCE_FOLDERS),$(wildcard $(dir)/*.cpp))

#OPTIMIZATION_LEVEL = 3

#include /home/roobre/Devel/Arduino-Makefile/Arduino.mk
include /usr/share/arduino/Arduino.mk
