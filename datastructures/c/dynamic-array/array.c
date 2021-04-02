#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "array.h"

DynamicArray* array_init(int initial_size) {
    DynamicArray* created_array = malloc(sizeof(DynamicArray));
    created_array->length = 0;
    created_array->capacity = initial_size + 1;
    created_array->data = malloc(sizeof(ARRAY_TYPE) * initial_size);

    return created_array;
}

ARRAY_TYPE array_pop(DynamicArray* array, int index) {
    // Store the original popped value and overwrite it's place in the array.
    ARRAY_TYPE popped_value = array->data[index];
    array->data[index] = 0;

    // Push values that follow the popped one back
    for (int ahead_index = index + 1; ahead_index < array->length; ahead_index++) {
        ARRAY_TYPE original_value = array->data[ahead_index];
        array->data[ahead_index - 1] = original_value;
        array->data[ahead_index] = 0;
    }

    // There are none left, so you cannot subtract more.
    if (array->length > 0) {
        array->length--;
    }

    return popped_value;
}

double array_load_factor(DynamicArray* array) {
    double double_length = array->length;
    double double_capacity = array->capacity;


    return double_length / double_capacity;
}

int array_find(DynamicArray* array, ARRAY_TYPE find) {
    /*
     * Finds the index of a value in an array.
     * @param array: the array to search through
     * @param find: the value to find
     * @return: the index of find
    */

    for (int i = 0; i < array->length; i++) {
        if (array->data[i] == find) {
            return i;
        }
    } 

    return -1;
}

void array_append(DynamicArray* array, ARRAY_TYPE value) {
    /*
     * Inserts a new value at the end of the array.
     * @param array: the array to append to
     * @param value: the value to append
    */

    array_resize(array);

    array->length++;
    array->data[array->length - 1] = value;
}

void array_insert(DynamicArray* array, int index, ARRAY_TYPE value) {
    /*
     * Inserts a value into the array at a certain position in the array,
     * resizing if necessary.
     * @param array: the array to insert to
     * @param index: the index to insert into
     * @param value: the value to insert
    */

    // Attempting to insert two values at the same position causes
    // the program to segfault =(

    // Resize the array if necessary
    array_resize(array);

    // Push all values after the index to one ahead.
    // If (length == 0 && index == 0) then this for loop will not run.
    for (int i = array->length - 1; i >= index; i--) {
        array->data[i + 1] = array->data[i];
        array->data[i] = 0;  // This might be redundant
    }

    array->length++;
    array->data[index] = value;
}

void array_free(DynamicArray* array) {
    /*
     * Frees both the array structure, and data it holds
     * @param array: the array to free
    */

    free(array->data);
    free(array);
}

void array_resize(DynamicArray* array) {
    /*
     * Resizes the array if necessary.
     * @param array: the array to resize
    */

    double load_factor = array_load_factor(array);

    if (load_factor >= LOAD_THRESHOLD) {
        // Determines the new size of the array and allocates new memory
        // to hold the previous values.
        int new_capacity = array->capacity * GROWTH_FACTOR;
        ARRAY_TYPE* new_data = malloc(sizeof(ARRAY_TYPE) * new_capacity);

        // You ran out of memory, idiot.
        if (new_data == NULL) {
            fprintf(stderr, "Ran out of memory!");
            abort();
        }

        // Copy the area of the area that contains values into the new array.
        for (int i = 0; i < array->length; i++) {
            new_data[i] = array->data[i];
        }

        // Do some cleanup to prevent memory leaks.
        free(array->data);
        array->data = new_data;
        array->capacity = new_capacity;
    }
}

// Debugging
void array_display(DynamicArray* array) {
    for (int index = 0; index < array->capacity; index++) {
        printf("Element at index %i: %p\n", index, array->data[index]);
    }
    printf("\n");
}

void array_debug(DynamicArray* array) {
    printf("----- DEBUG INFORMATION FOR ARRAY %p -----\n", array);
    printf("        Length: %i\n", array->length);
    printf("      Capacity: %i\n", array->capacity);
    printf("   Load factor: %lf\n", array_load_factor(array));
    printf("Array Location: %p\n", array->data);
    printf("Struct Address: %p\n\n", array);
}
