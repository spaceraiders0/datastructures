/*
 * Hash functions for various datatypes.
*/

#include <string.h>
#include "hashtable.h"
#include <math.h>

int hashInt(int value) {
    return value;
}

int hashString(char* value) {
    unsigned long hash = 5381;

    for (int i = 0; i < strlen(value); i++) {
        hash = ((hash << 5) + hash) + value[i];
    }

    return hash;
}
