#ifndef _DEBUG_H
#define _DEBUG_H

#include "configuration.h"

#if CT_DEBUG == 1
#define print_error(...) _debug_print(1, __VA_ARGS__)
#define print_event(...)
#define print_debug(...)
#elif CT_DEBUG == 2
#define print_error(...) _debug_print(1, __VA_ARGS__)
#define print_event(...) _debug_print(2, __VA_ARGS__)
#define print_debug(...)
#elif CT_DEBUG == 3
#define print_error(...) _debug_print(1, __VA_ARGS__)
#define print_event(...) _debug_print(2, __VA_ARGS__)
#define print_debug(...) _debug_print(3, __VA_ARGS__)
#else
#define print_debug(...)
#define print_event(...)
#define print_error(...)
#endif

#if CT_DEBUG

#include <Arduino.h>
#include <stdint.h>
#include <string.h>
#include <stdarg.h>

extern char debugMsg[64];
extern char codes[3][8];

void _debug_print(uint8_t level, const char* msg, ...);

#endif

#endif
