#!/usr/bin/env python

"""Bubblesort is an O(n^2) algorithm that swaps elements that are greater than
one another.
"""


def BubbleSort(source: list) -> list:
    source_copy = source.copy()
    source_len = len(source)

    for index_a in range(source_len):
        for index_b in range(source_len):
            temp_a, temp_b = source_copy[index_a], source_copy[index_b]

            if temp_a > temp_b:
                source_copy[index_a], source_copy[index_b] = temp_b, temp_a

    return source_copy


if __name__ == "__main__":
    import random

    unsorted_list = [random.randrange(1, 11) for n in range(10)]
    print(f"Unsorted: {', '.join(map(str, unsorted_list))}")
    print(f"Sorted: {', '.join(map(str, BubbleSort(unsorted_list)))}")
