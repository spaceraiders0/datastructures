#ifndef JSON_H_
#define JSON_H_

#define ARRAY_TYPE int
#define LOAD_THRESHOLD 0.7
#define GROWTH_FACTOR 2

typedef struct DynamicArray {
    int length;
    int capacity;
    ARRAY_TYPE* data;
} DynamicArray;

DynamicArray* array_init(int initial_size);
ARRAY_TYPE array_pop(DynamicArray*, int index);
double array_load_factor(DynamicArray* array);
int array_find(DynamicArray* array, ARRAY_TYPE find);
void array_insert(DynamicArray* array, int index, ARRAY_TYPE value);
void array_resize(DynamicArray* array);
void array_append(DynamicArray* array, ARRAY_TYPE value);
void array_free(DynamicArray* array);
void array_display(DynamicArray* array);
void array_debug(DynamicArray* array);

#endif
