#ifndef CONTEXT_PROVIDER_H
#define CONTEXT_PROVIDER_H

#include <stdlib.h>
#include <string.h>
#include "Debug.h"

namespace ContextProvider {
    const int MAX_ENTRIES = 8;
    const int MAX_KEY_LEN = 8;

    extern char keys[MAX_ENTRIES][MAX_KEY_LEN];
    extern void* values[MAX_ENTRIES];
    extern uint8_t last;

    void init();
    void* get(const char* key);
    void* set(const char* key, void* entry);
}

#endif
