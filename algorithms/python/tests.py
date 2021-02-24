#!/usr/bin/env python

"""A little test-suite for me to test the speeds of algorithms.
"""

from timeit import timeit
from random import randrange
from InsertionSort import InsertionSort
from BubbleSort import BubbleSort
from QuickSort import QuickSort
from MergeSort import MergeSort

TIMES = 1
SORT_COUNT = 10001
dataset = [randrange(1, 1000) for _ in range(SORT_COUNT)]

insertionsort_time = timeit(lambda: InsertionSort(dataset), number=TIMES)
bubblesort_time = timeit(lambda: BubbleSort(dataset), number=TIMES)
quicksort_time = timeit(lambda: QuickSort(dataset), number=TIMES)
mergesort_time = timeit(lambda: MergeSort(dataset), number=TIMES)

print(f"Sorted {SORT_COUNT - 1} integers.")
print(f"Execution time of InsertionSort, executed {TIMES} times: {insertionsort_time}")
print(f"Execution time of Bubblesort, executed {TIMES} times: {bubblesort_time}")
print(f"Execution time of QuickSort, executed {TIMES} times: {quicksort_time}")
print(f"Execution time of MergeSort, executed {TIMES} times: {mergesort_time}")
