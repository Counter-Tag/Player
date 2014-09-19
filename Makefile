.SUBLIME_TARGETS: all show_boards upload clean

ARDUINO_SKETCHBOOK = /home/roobre/Arduino/
AVRDUDE = /usr/bin/avrdude
AVRDUDE_CONF = /etc/avrdude.conf
AVR_TOOLS_PATH = /usr/bin

BOARD_TAG = nano328
ARDUINO_LIBS =

SOURCE_FOLDERS = Player Weapon

include /home/roobre/Devel/Arduino-Makefile/Arduino.mk
