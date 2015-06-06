#include "../include/Debug.h"

#if CT_DEBUG

char debugMsg[64];
char codes[3][8] = {"[ERROR]", "[EVENT]", "[DEBUG]"};

void _debug_print(uint8_t level, const char* msg, ...) {
    va_list valist;
    va_start(valist, msg);

    vsprintf(debugMsg, msg, valist);
    memmove(debugMsg + 8, debugMsg, strlen(debugMsg) + 1);
    memcpy(debugMsg, codes[level - 1], 7);
    debugMsg[7] = ' ';
    strcat(debugMsg, "\r\n");
    Serial.write(debugMsg);

    va_end(valist);
}

#endif
