/*
 * An implementation of a Hashtable. A datastructure that allows for (theoretically)
 * O(1) indexing of all values by "hashing" values.
*/

#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef enum HashType {
    HASH_INT,
    HASH_FLOAT,
    HASH_DOUBLE,
    HASH_STRING,
    HASH_CHAR,

    HASH_INT_PTR,
    HASH_FLOAT_PTR,
    HASH_DOUBLE_PTR,
    HASH_STRING_PTR,
    HASH_CHAR_PTR
} HashType;

int hashInt(int value);
int hashString(char* value);

#define NODE_DEFINE(keyType, valueType) \
    struct {                            \
        keyType    key;                 \
        valueType  value;               \
    }                                   \

#define HASHTABLE_DEFINE(nodeType) \
    struct {                       \
        int       length;          \
        int       capacity;        \
        nodeType* contents;        \
    }                              \

#define hashtableAllocate(hashtableType) \
    malloc(sizeof(hashtableType))

#define hashtableInit(hashtable, nodeType, initialSize, growth, threshold) \
    hashtable->length = 0;                                                    \
    hashtable->capacity = initialSize;                                       \
    hashtable->contents = malloc(sizeof(nodeType) * initialSize)            \

#define hashtableHash(value, var)    \
    0;                               \
    typeof(value) new_val = value;   \
    void* value_ptr = &new_val;      \
    switch(sizeof(value)) {          \
        case sizeof(int):            \
            var = hashInt(value);    \
            break;                   \
        case sizeof(char*):          \
            var = hashString(value); \
            break;                   \
        case sizeof(double):         \
            var = hashDouble(value)  \
            break;                   \
    }                                \

#define hashtableAdd(hashtable, hashKey, hashValue) \
    typeof(*hashtable->contents) newNode = malloc(sizeof(typeof(*hashtable->contents)));            \
    newNode->key = hashKey;                                     \
    newNode->value = hashValue;                                 \
    int hashedValue = 0;            \
    hashtableHash(5, hashedValue);


typedef NODE_DEFINE(int, char*)* IntChar;
typedef HASHTABLE_DEFINE(IntChar) IntCharTable;
