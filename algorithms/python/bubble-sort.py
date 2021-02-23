#!/usr/bin/env python

"""Bubblesort is an O(n^2) algorithm that swaps elements that are greater than
one another.
"""

import random

unsorted_list = [random.randrange(1, 11) for n in range(1, 11)]

print(f"Unsorted: {', '.join(map(str, unsorted_list))}")

def bubble_sort(source: list) -> list:
    source_copy = source.copy()

    for index_a, value_a in enumerate(source_copy):
        for index_b, value_b in enumerate(source_copy):
            temp_a, temp_b = source_copy[index_a], source_copy[index_b]

            if value_a > value_b:
                source_copy[index_a], source_copy[index_b] = temp_b, temp_a

    return source_copy

print(f"Unsorted: {', '.join(map(str, bubble_sort(unsorted_list)))}")

