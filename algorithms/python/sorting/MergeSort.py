#!/usr/bin/env python

"""MergeSort. A "Divide and Conquer" algorithm, implemented in Python.
"""


def MergeSort(unsorted: list):
    if len(unsorted) == 1:
        return unsorted

    # Divide
    center = round(len(unsorted) / 2)
    left, right = unsorted[:center], unsorted[center:]

    left = MergeSort(left)
    right = MergeSort(right)

    # Conquer
    sorted_list = []
    left_index, right_index = 0, 0

    # while len(left) != 0 and len(right) != 0:
    #     first_left, first_right = left[0], right[0]

    #     if first_left <= first_right:
    #         sorted_list.append(first_left)
    #         left = left[1:]
    #     else:
    #         sorted_list.append(first_right)
    #         right = right[1:]

    # # Clean up any remaining elements in either list.
    # while len(left) > 0:
    #     sorted_list.append(left.pop(0))

    # while len(right) > 0:
    #     sorted_list.append(right.pop(0))

    while left_index < len(left) or right_index < len(right):
        left_value, right_value = left[left_index], right[right_index]

        if left_value > right_value:
            sorted_list.append(left_value)
            left_index += 1
        else:

            sorted_list.append(right_value)
            right_index += 1

    return sorted_list


if __name__ == "__main__":
    import random

    dataset = [random.randrange(1, 11) for n in range(10)]
    print(f"Unsorted: {', '.join(map(str, dataset))}")
    print(f"Sorted: {', '.join(map(str, MergeSort(dataset)))}")
