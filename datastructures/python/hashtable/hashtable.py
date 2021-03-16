#!/usr/bin/env python

"""A Hashtable is a datastructure that utilises hashing, which converts data to
a number, which is then used inside of an array to locate indexes. It is useful
for when you need a (usually) O(1) lookup time for a given value, but it can be
a problem if your Hashtable has many collisions, even leading to a worst-case of
O(n). However, rehashing and a smart load-factor can usually help out with this
problem quite a bit.

To deal with collisions, however, this implementation of a Hashtable uses
open-addressing. Open-addressing is a technique in which when a collision is
detected, (collision referring to two values hashing to the same value), it
will search for the next open slot.
"""

from typing import Tuple, Any

# State constants
TOMBSTONE = 0
FILLED = 1
UNFILLED = 2
conversion = {
    0: "TOMBSTONE",
    1: "FILLED",
    2: "UNFILLED",
}


class Node():
    """A Node that represents both a Key, and a Value. Each node also has a
    state that describes whether it is filled, empty, or a tombstone.

    Tombstones and Filled nodes can be looped over, while searching stops at
    empty Nodes.
    """

    def __init__(self, key: any = None, value: any = None):
        self.key = key
        self.value = value
        self.state = UNFILLED

    def _set(self, key: any, value: any):
        self.key = key
        self.value = value
        self.state = FILLED

    def __repr__(self) -> str:
        return str(self.value)


class HashTable():
    def __init__(self, *kv_pairs: Tuple[Any, Any], t_min: float = 0.2,
                 t_max: float = 0.7, initial_size: int = 10,
                 growth_factor: callable = lambda n: n * 2):

        self.min_threshold = t_min
        self.max_threshold = t_max
        self.logical_size = 0
        self.physical_size = initial_size
        self.growth_factor = growth_factor
        self.nodes = [Node() for n in range(initial_size)]

        # Fill up nodes.
        for key, value in kv_pairs:
            self[key] = value

    def __setitem__(self, key: Any, value: Any):
        """This "inserts" a new entry into the Hashtable. Every spot in this
        Hashtable is filled with a Node, however the state of the Node is
        unfilled by default. To deal with collisions, this uses linear-probing
        to implement open-addressing. This is achieved by constantly shifting
        the key_index variable forward (with a modulo operator) until a Node is
        found that is unfilled.

        This algorithm will always find an empty spot (even if every Node ahead
        of the starting index is filled), because each time a new item is
        inserted into the Hashtable, the table is rehashed and resized if the
        new load factor with the new entry added is above the threshold of
        the Hashtable.
        """

        self._rehash()
        key_index: int = hash(key) % self.physical_size
        node = self._get_node(key_index)

        # Keep updating key_index until an unfilled Node is found.
        while node.key != key and node.state != UNFILLED:
            key_index = ((key_index + 1) % self.physical_size)
            node = self._get_node(key_index)

        # Whether or not this added a new node.
        if node.key != key:
            self.logical_size += 1

        node._set(key, value)

    def __getitem__(self, key: Any) -> Any:
        key_index: int = hash(key) % self.physical_size
        node = self.nodes[key_index]

        # No key exists with this value. (If this does not raise, the key
        # exists *somewhere* in the Hashtable. Just not necessarily at first
        # hash index.)
        if node.state == UNFILLED:
            raise KeyError(f"{key} is not inside this Hashtable.")

        # Keep updating value until an unfilled node is reached.
        # This is done through linear probing, which keeps going until
        # a node with the same key is found, or an unfilled 
        while node.key != key and node.state in [TOMBSTONE, FILLED]:
            key_index = ((key_index + 1) % self.physical_size)
            node = self.nodes[key_index]

        return node

    def __len__(self) -> int:
        return self.logical_size

    def __iter__(self):
        self._last_index = 0
        return self

    def __next__(self):
        while True:
            if self._last_index == len(self.nodes):
                raise StopIteration

            node = self._get_node(self._last_index)
            self._last_index += 1

            if node.state == FILLED:
                return node.key, node.value

    def get_load_factor(self) -> float:
        """Returns the load factor of the Hashtable.
        """

        return self.logical_size / self.physical_size

    def _get_node(self, index: int) -> Node:
        if index >= 0 and index < self.physical_size:
            return self.nodes[index]
        else:
            raise IndexError(index)

    def _rehash(self):
        """Rehashes the Hashtable, removing Tombstones and resizes the table
        based off the load factor.

        If the load factor is below t_min, then it will be shrunk. Leaving only
        a few empty nodes at the end. However, if it is larger than the t_max,
        then the Hashtable is resized, adding more entries based off the growth
        factor function.
        """

        if self.get_load_factor() > self.max_threshold:
            new_size = self.growth_factor(self.logical_size)
            new_hashtable = HashTable(initial_size=new_size)
            self.logical_size = 0

            print("Expanding.")
            for node in filter(lambda n: n.state == FILLED for n in self.nodes):
                new_hashtable[key] = value
                self.logical_size += 1

            self.nodes = new_hashtable.nodes
            self.physical_size = new_size
            del new_hashtable

        elif self.get_load_factor() < self.min_threshold:
            print("Shrinking.")

    def _visualize(self):
        for n in range(self.physical_size):
            node = self.nodes[n]
            print(node.key, node.value, conversion[node.state])


my_hashtable = HashTable((1, 2), (6, 5))
my_hashtable["bar"] = 1
my_hashtable["foo"] = 4
my_hashtable["qaz"] = 3
