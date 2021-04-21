#!/usr/bin/env python

"""Creates a prime factorization tree of a given integer.
"""

import json
import pairs
import is_prime
from tree.tree import Tree


def prime_factorize(num: int) -> dict:
    """Returns a prime-factorization tree of a given integer.

    @param num: the number to factorize
    @type num: int
    @return: a prime factorization tree
    @rtype: dictj
    """

    factorization_tree = Tree({num: {}}, allowed_nodes=2)
    factor_queue = [factorization_tree._root_node]

    # Continuously factorize the numbers until there are none left.
    while len(factor_queue) > 0:
        node = factor_queue.pop(0)
        number = node.value

        # Only non-primes can be further subdivided
        if is_prime.is_prime(number) is True:
            continue

        try:
            factor_a, factor_b = next(iter(pairs.pairs(number, primes=False)))
        except StopIteration:
            break

        node_a = factorization_tree.insert(node, factor_a)
        node_b = factorization_tree.insert(node, factor_b)

        factor_queue.append(node_a)
        factor_queue.append(node_b)

    return factorization_tree


if __name__ == "__main__":
    factorized = prime_factorize(125)

    for value in factorized:
        print(value)

        #drawitem(struct item)
