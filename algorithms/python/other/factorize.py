#!/usr/bin/env python

"""Returns the factors of a given integer.
"""

import sys


def factorize(n: int, primes: bool = True) -> list:
    """Generator that yields the factors of a given integer.

    @param n: the integer to find factors of
    @type n: integer
    @param primes: whether or not to include 1 and itself
    @type primes: boolean
    @return: the factors of a given integer
    @rtype: integer
    """

    # Always factors of any integer
    if primes is True:
        yield 1
        yield n

    for i in range((n // 2) + 1):
        for j in range((n // 2) + 1):
            if i * j == n:
                yield i


if __name__ == "__main__":
    num = int(sys.argv[1])
    print(f"Factors of {num}:")

    for i in factorize(num, primes=False):
        print(i)
