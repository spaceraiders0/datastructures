#!/usr/bin/env python
"""QuickSort, an  O(n log n) algorithm that partitions a dataset based off a
pivot point and sorts it from there.
"""

import random

dataset = [random.randrange(1, 11) for n in range(1, 7)]

print(f"Unsorted: {', '.join(map(str, dataset))}")


def quicksort(source: list) -> list:
    if len(source) <= 1:
        return source

    # Divide
    source_copy = source.copy()
    pivot_index = round(len(source) / 2)
    pivot = source_copy[pivot_index]
    source_copy.pop(pivot_index)

    # Re-arrange
    greater, lesser = [], []

    for cmp_val in source_copy:
        if cmp_val >= pivot:
            greater.append(cmp_val)
        else:
            lesser.append(cmp_val)

    # Conquer
    greater = quicksort(greater)
    lesser = quicksort(lesser)

    # Merge
    return greater + [pivot] + lesser




print(f"Sorted: {', '.join(map(str, quicksort(dataset)))}")
