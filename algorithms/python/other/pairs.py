#!/usr/bin/env python

"""Finds factor pairs of a given integer.
"""


def can_yield(yielded: int, max_count: int) -> bool:
    if yielded == max_count:
        return False

    return True


def pairs(num: int, primes: bool = False) -> (int, int):
    """Yields a tuple of two factors that multiply together to
    make another integer.

    @param num: the number to find pairs of
    @type num: integer
    @param primes: whether or not to include 1 and itself
    @type primes: boolean, defaults to False
    @param factors: how many factors to yield, not including 1 and itself
    @type factors: integer, defaults to -1
    """

    for i in range((num // 2) + 1):
        for j in range((num // 2) + 1):
            if i * j == num:
                yield i, j

    if primes is True:
        yield 1, num
        yield num, 1
