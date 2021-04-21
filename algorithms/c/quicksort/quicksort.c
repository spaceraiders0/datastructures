/*
 * QuickSort, an O(n log n) algorithm for sorting using partitioning.
*/

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "macro-array/array.h"

int* quicksort(int arr_length, int* arr_start) {
    if (arr_length <= 1) {
        return arr_start;
    }

    int arr_center = arr_length / 2;
    int pivot_value = arr_start[arr_center];
    printf("Selected pivot: %i\n", arr_center);
    printf("Array length: %i\n", arr_length);
    printf("Array contents: ");

    for (int i = 0; i < arr_length; i++) {
        printf("%i, ", arr_start[i]);
    }
    printf("\n\n");

    // Create arrays to store various values in
    array_int greater = array_allocate(array_int);
    array_int equal   = array_allocate(array_int);
    array_int lesser  = array_allocate(array_int);

    array_init(greater, 0.75, 2, 4);
    array_init(equal, 0.75, 2, 4);
    array_init(lesser, 0.75, 2, 4);

    // Divide
    for (int i = 0; i < arr_length; i++) {
        int selected_value = arr_start[i];

        if (selected_value == pivot_value) {
            array_append(equal, selected_value);
        }
        else if (selected_value > pivot_value) {
            array_append(greater, selected_value);
        }
        else if (selected_value < pivot_value) {
            array_append(lesser, selected_value);
        }
    }

    sleep(1);

    // Conquer
    greater->data = quicksort(greater->length, greater->data);
    equal->data = quicksort(equal->length, equal->data);
    lesser->data = quicksort(lesser->length, lesser->data);

    // Merge
    array_int final_array = array_allocate(array_int);
    array_init(final_array, 0.75, 2, 4);

    for (int i = 0; i < greater->length; i++) {
        array_append(final_array, greater->data[i]);
    }

    for (int i = 0; i < equal->length; i++) {
        array_append(final_array, equal->data[i]);
    }

    for (int i = 0; i < lesser->length; i++) {
        array_append(final_array, lesser->data[i]);
    }


    return final_array->data;
}

