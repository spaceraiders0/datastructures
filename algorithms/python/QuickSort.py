#!/usr/bin/env python
"""QuickSort, an  O(n log n) algorithm that partitions a dataset based off a
pivot point and sorts it from there.
"""


# SOME GENERAL IMRPOVEMENTS:
# check for multiple occurrances of the pivot, and collect them.
# join them all in the same list, then do:
# return lesser + [ALL_PIVOT_OCCURANCES] + greater

# update the original source list, instead of copying it.
# however, this does hinder thread safety.


def QuickSort(source: list) -> list:
    if len(source) <= 1:
        return source

    # Divide
    source_copy = source.copy()
    pivot_index = round(len(source) / 2)
    pivot = source_copy.pop(pivot_index)

    # Re-arrange
    greater, lesser = [], []

    for cmp_val in source_copy:
        if cmp_val >= pivot:
            greater.append(cmp_val)
        else:
            lesser.append(cmp_val)

    # Conquer
    greater = QuickSort(greater)
    lesser = QuickSort(lesser)

    # Merge
    return lesser + [pivot] + greater


if __name__ == "__main__":
    import random

    dataset = [random.randrange(1, 11) for n in range(10)]
    print(f"Unsorted: {', '.join(map(str, dataset))}")
    print(f"Sorted: {', '.join(map(str, QuickSort(dataset)))}")
