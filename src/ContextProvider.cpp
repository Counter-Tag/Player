#include "../include/ContextProvider.h"

namespace ContextProvider {
    char keys[MAX_ENTRIES][MAX_KEY_LEN];
    void* entries[MAX_ENTRIES];
    uint8_t last = 0;

    void* get(const char* key) {
        for (int i = 0; i < last; i++) {
            if (!strcmp(keys[i], key)) {
                print_debug("[CONTEXT] Retrieving %s @ %i.", key, i);
                return entries[i];
            }
        }

        print_error("[CONTEXT] %s not found.", key);
        return NULL;
    }

    void* set(const char* key, void* entry) {
        if (last == (MAX_ENTRIES - 1)) {
            print_error("[CONTEXT] Not enough space to store %s (%i).", key, last);
            return NULL;
        }

        strncpy(keys[last], key, MAX_KEY_LEN - 1);
        entries[last] = entry;
        print_debug("[CONTEXT] Storing %s @ %i.", key, last);
        last++;

        return entry;
    }
}