"""An implementation of a Tree datastructure.
"""

import copy


class Node():
    def __init__(self, value, parent=None, depth=0, allowed_nodes=-1):
        self.value = value
        self.parent = parent
        self._children = []
        self.allowed_nodes = allowed_nodes
        self.depth = depth

    def _get_children(self):
        """A generator that yields each child node.
        """

        for child in self._children:
            yield child

    def _add_child(self, value):
        """Adds a new child to this node. Also checks if there
        are too many nodes if an N-Tree is preferable.

        :param value: the value to add. if it's not a node, it
                will be converted into one
        :type value: Node, any

        :raises ValueError:
        """

        if not isinstance(value, Node):
            value = Node(value)

        # -1 means that this can have an arbitary amount of nodes,
        # while anything above 0 must have a number of nodes less than
        # the number of allowed nodes.
        if self.allowed_nodes == -1 or len(self) < self.allowed_nodes:
            self._children.append(value)
        else:
            raise ValueError("Node is full!")

    def get_parents(self):
        """Yields each of this node's parents.

        :returns: a Node in the parent tree 
        :rtype: Node 
        """
    
        parents = []
        next_parent = self.parent

        while next_parent is not None:
            parents.append(next_parent)
            next_parent = next_parent.parent

        return parents

    def __repr__(self):
        return str(self.value)

    def __str__(self):
        return str(self.value)

    def __len__(self):
        return len(self._children)


class Tree():
    """A general-purpose tree with N-Tree / M-ary tree capabilities.
    The Tree is iterated breadth-first.

    :param source: the source to build the tree from
    :type source: dict
    :param allowed_nodes: the number of sub-nodes each node is allowed
            to have. used for n-trees.
    :type allowed_nodes: int
    """

    def __init__(self, source: dict, allowed_nodes: int = -1):
        self._allowed_nodes = allowed_nodes

        # Certain numbers of subnodes arent allowed.
        if allowed_nodes == 0 or allowed_nodes <= -2:
            raise ValueError("Number of allowed nodes must be -1, or above 0!")

        try:
            # Grab the first key from the dictionary
            self._root_node = Node(next(iter(source)), allowed_nodes=allowed_nodes)
            self._walk(self._root_node, source[self._root_node.value])
        except StopIteration:
            self._root_node = None

    def _walk(self, parent_node: Node, walk_source: dict, depth=1):
        """Recursively builds the tree from a source dictionary.

        :param parent_node: the node these nodes descend from
        :type parent_node: Node
        :param walk_source: the dictionary to build from
        :type walk_source: dict
        """

        for value, children in walk_source.items():
            new_child = Node(value, parent_node, depth, self._allowed_nodes)
            parent_node._add_child(new_child)
            self._walk(new_child, walk_source[value], depth=depth + 1)

    def __iter__(self):
        self._node_queue = [self._root_node]

        return self

    def __next__(self):
        if len(self._node_queue) == 0 or self._root_node is None:
            raise StopIteration
 
        next_node: Node = self._node_queue.pop(0)
        self._node_queue += next_node._get_children()

        return next_node

    def __contains__(self, contains_value) -> bool:
        for node in self:
            if node.value == contains_value:
                return True
        else:
            return False

    def rfold(self, accumulator, callback):
        """Folds the Tree with the accumulator being on the right.
        """

        new_accumulator = copy.copy(accumulator)

        for node in self:
            new_accumulator = callback(node.value, new_accumulator)

        return new_accumulator

    def lfold(self, accumulator, callback):
        """Folds the Tree with the accumulator being on the left.
        """

        new_accumulator = copy.copy(accumulator)

        for node in self:
            new_accumulator = callback(new_accumulator, node.value)

        return new_accumulator

    def find(self, value_to_find) -> Node:
        """Finds the Node that holds a value.

        :param value_to_find: the value to find in a node.
        :type value_to_find: any
        :returns: the node that old this value
        :rtype: Node, None
        """

        for node in self:
            if node.value == value_to_find:
                return node
        else:
            return None

    def lowest_common_ancestor(self, node_a: Node, node_b: Node):
        """Finds the first parent that both nodes share. This is done by
        collecting all the parents of the node closest to the top, and pops
        off the first n elements of the list, where n is the difference between
        the depth of the first node, and second node. This is done because if
        one node is beneath the other (it almost always will be), then there is
        always a few nodes that will NEVER be parents of both.

        :param node_a: the first node to check
        :type node_a: Node
        :param node_b: the second node to check
        :type node_b: Node
        """

        # Finds the node of the smallest depth.
        depths = (node_a.depth, node_b.depth)
        highest = node_a
        lowest = node_b

        if node_a.depth > node_b.depth:
            highest = node_b
            lowest = node_a
        else:
            highest = node_a
            lowest = node_b

        highest_parents = list(highest.get_parents())

        # A single parent means that this node is a direct child of
        # the root node, and each node shares a common ancestor with
        # the root node.
        if len(highest_parents) == 1:
            return self._root_node
        elif len(highest_parents) == 0:
            return None

        for lowest_parent in lowest.get_parents():
            if lowest_parent in highest_parents:
                return lowest_parent
