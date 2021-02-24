#!/usr/bin/env python
"""QuickSort, an  O(n log n) algorithm that partitions a dataset based off a
pivot point, collects datapoints larger and less than the pivot into their own
individual lists, and recursively calls itself on them, eventually merging up
the final lists.

This implementation is pivot-optimized. Meaning that it collects all values
that are the same as the piviot, and puts them in the middle so there is no
need to sort through values that would go in the middle regardless.
"""


def QuickSort(source: list) -> list:
    if len(source) <= 1:
        return source

    # Divide
    pivot_index = round(len(source) / 2)
    pivot = source[pivot_index]

    # Re-arrange
    greater, lesser, pivots = [], [], [pivot]

    for cmp_val in source:
        if cmp_val == pivot:
            pivots.append(cmp_val)
        elif cmp_val >= pivot:
            greater.append(cmp_val)
        else:
            lesser.append(cmp_val)

    # Conquer, and Merge
    return QuickSort(lesser) + pivots + QuickSort(greater)


if __name__ == "__main__":
    import random

    dataset = [random.randrange(1, 11) for n in range(10)]
    print(f"Unsorted: {', '.join(map(str, dataset))}")
    print(f"Sorted: {', '.join(map(str, QuickSort(dataset)))}")
