"""Binary Search is a search algorithm that continuously divides a dataset till
it finds a target value. It can be performed iteratively, but also recursively.

It only works on an already sorted array.
"""


def BinarySearch(array: list, target: any) -> any:
    start, stop = 0, len(array) - 1

    while start <= stop:
        mid_point = (start + stop) // 2
        mid_value = array[mid_point]

        if mid_value == target:
            return mid_point
        elif mid_value > target:
            stop = mid_point - 1
        elif mid_value < target:
            start = mid_point + 1

    return -1


if __name__ == "__main__":
    import random

    dataset = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]
    num_to_find = random.randint(1, 10)

    print(f"Finding {num_to_find} in {dataset}:")
    print(f"The index of {num_to_find} is {BinarySearch(num_to_find)}")
