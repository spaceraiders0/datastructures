#!/usr/bin/env python

"""Script to tell you whether or not a given number is prime.

A prime is any number greater than one that is only divisible by one, and itself.
Given a number n, n is prime if (n / 1) and (n / p) are the only two division
operations that have no remainder.
"""

import math
import time


def is_prime(num: int) -> bool:
    """Determines whether or not a given number is a prime.

    @param num: the number to check for prime-ness
    @type num: integer
    @return: whether or not the number is a prime
    @rtype: boolean
    """

    # Primes must be greater or equal to two.
    if num <= 1:
        return False

    # Starting at two because we already did a check for the number
    # being divisible by 1.

    # Why does only going up to the integer square root of a number
    # speed things up to much?
    for divisor in range(3, math.isqrt(num) + 1, 2):
        if (num % divisor) == 0:
            return False

    # All primes after two are not even.
    if num != 2 and num % 2 == 0:
        return False

    return True


if __name__ == "__main__":
    print("Finding all primes from 1, to 10000001:")

    current_time = time.time()

    for i in range(1, 10000001):
        is_prime(i)

    print(f"Time spent: {time.time() - current_time}")
