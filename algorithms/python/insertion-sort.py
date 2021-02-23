#!/usr/bin/env python

"""Insertion sort is an O(n^2) algorithm that builds a new list as it traverses
another one.
"""

import random

unsorted_list = [random.randrange(1, 11) for n in range(1, 11)]

print(f"Unsorted: {', '.join(map(str, unsorted_list))}")


def insertion_sort(source: list) -> list:
    new_source = [source.pop(0)] if len(source) > 0 else []

    for cmp_val in source:
        index = 0

        while index < len(new_source) and new_source[index] <= cmp_val:
            index += 1

        new_source.insert(index, cmp_val)

    return new_source


print(f"Sorted: {', '.join(map(str, insertion_sort(unsorted_list)))}")
