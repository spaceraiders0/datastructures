#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <math.h>
#include "hashtable.h"

int main() {
    IntCharTable* my_hashtable = hashtableAllocate(IntCharTable);
    hashtableInit(my_hashtable, IntChar, 5, 2, 0.75);

    hashtableAdd(my_hashtable, 5, "foo");
}
