/* Implementation of a Linked List. A datastructure that "links" values
 * rather than having them be side by side in memory.
*/ 

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "linked-list.h"

// Constructors
Node* node_create(NODE_TYPE value) {
    /*
     * Initializes a new Node
     * @param value: the value this node should hold
    */ 

    Node* new_node = malloc(sizeof(Node));
    new_node->value = value;
    new_node->next_node = NULL;

    return new_node;
}

LinkedList* linked_create(int list_length, ...) {
    /*
     * Initializes a Linked List.
     * @param list_length: the size of the list
     * @param ...: the entries to initialize with
    */ 

    LinkedList* new_list = malloc(sizeof(LinkedList));
    new_list->head = NULL;
    new_list->tail = NULL;
    new_list->length = list_length;

    // A size of 0 means no values to initialize.
    if (list_length > 0) {
        va_list varadic;
        va_start(varadic, list_length);

        // Load up the head node.
        new_list->head = node_create(va_arg(varadic, NODE_TYPE));
        new_list->tail = new_list->head;

        // Load up the remaining nodes
        for (int i = 1; i < list_length; i++) {
            new_list->tail->next_node = node_create(va_arg(varadic, NODE_TYPE));
            new_list->tail = new_list->tail->next_node;
        }
    }

    return new_list;
}

// Methods
Node* linked_index(LinkedList* l, NODE_TYPE i) {
    /*
     * Returns the node at a given index, null if it does not exist
     * @param l: pointer to the Linked List
     * @param i: index to retrieve
     * @returns: pointer to a Node, or NULL if it does not exist
    */

    // Makes sure i is is not out of range
    if (i < 0 || i >= l->length) {
        return NULL;
    }

    Node* current_node = l->head;

    // Keep updating current_node until the index is reached.
    for (int j = 0; j < i; j++) {
        current_node = current_node->next_node;
    }
    
    return current_node;
}

NODE_TYPE linked_find(LinkedList* l, NODE_TYPE f) {
    /*
     * Finds the index of the first occurance of a value in a Linked List
     * if it does not exist
     * @param l: pointer to the Linked List
     * @returns: the index of the value
    */

    int index = -1;
    Node* current_node = l->head;

    while (current_node != NULL) {
        index += 1;
        current_node = current_node->next_node;
    };

    return index;
}

NODE_TYPE linked_pop(LinkedList* l, Node* n) {
    /*
     * Removes a Node from a Linked List and returns it's value
     * @param l: pointer to the Linked List
     * @param n: pointer to the Node
    */

    Node* previous_node = NULL;
    Node* current_node = l->head;
    NODE_TYPE original_val = current_node->value;

    // Traverse the Linked List until the node to remove is found.
    while (current_node != n && current_node != NULL) {
        previous_node = current_node;
        current_node = current_node->next_node;
    }

    if (current_node == n) {
        Node* after_node = current_node->next_node;

        // If the previous node is NULL, the Node is the head.
        if (previous_node == NULL) {
            l->head = after_node;
            l->tail = after_node;
        }
        else {
            previous_node->next_node = after_node;
        }
        
        free(current_node);
    }

    return original_val;
}

int linked_get_index(LinkedList* l, Node* n) {
    /*
     * Retrieves the index of a given node
     * @param l: pointer to the Linked List
     * @param n: pointer to the Node
     * @returns: the index of the Node
    */

    int current_index = -1;
    Node* current_node = l->head;

    // Keep shifting the current node until it is found.
    while (current_node != NULL && current_node != n) {
        current_index++;
        current_node = current_node->next_node;
    }

    return current_index;
}

void linked_insert(Node* n, NODE_TYPE v) {
    /*
     * Inserts a value after a node
     * @param l: pointer to the Node
     * @param v: the value to insert
    */

    Node* new_next = node_create(v);
    new_next->next_node = n->next_node;
    n->next_node = new_next;
}

int linked_index_insert(LinkedList* l, int i, NODE_TYPE v) {
    /*
     * Inserts a value at a given index
     * @param l: pointer to the Linked List 
     * @param i: the index to insert at 
     * @param v: the value to insert
    */


    // O(1) Append and Prepend
    if (i == 0) {
        linked_prepend(l, v);
        return 0;
    }
    else if (i == l->length) {
        linked_append(l, v);
        return 0;
    }
    // Index is out of range
    else if (i < 0 || i >= l->length) {
        return 1;
    }

    Node* new_next = node_create(v);
    Node* previous_node = NULL;
    Node* current_node = l->head;
    
    // Find the node at this index
    for (int j = 0; j < i; j++) {
        previous_node = current_node;
        current_node = current_node->next_node;
    }

    // Inserting at start of the list
    previous_node->next_node = new_next;
    new_next->next_node = current_node;

    return 0;
}

void linked_remove(LinkedList* l, Node* n) {
    /*
     * Removes a Node from the Linked List
     * @param l: pointer to the Linked List 
     * @param n: pointer to the Node 
    */

    Node* previous_node = NULL;
    Node* current_node = l->head;

    // Traverse the Linked List until the node to remove is found.
    while (current_node != n && current_node != NULL) {
        previous_node = current_node;
        current_node = current_node->next_node;
    }

    if (current_node == n) {
        Node* after_node = current_node->next_node;

        // If the previous node is NULL, the Node is the head.
        if (previous_node == NULL) {
            l->head = after_node;
            l->tail = after_node;
        }
        else {
            previous_node->next_node = after_node;
        }
        
        free(current_node);
    }
}

void linked_append(LinkedList* l, NODE_TYPE v) {
    /*
     * Appends a value onto a Linked List
     * @param l: pointer to the Linked List
     * @param v: the value to append
    */

    Node* n = node_create(v);

    // Tail and head need to be redefined
    if (l->head == NULL) {
        l->head = n;
        l->tail = n;
    }
    else {
        l->tail->next_node = n;
    }
}

void linked_prepend(LinkedList* l, NODE_TYPE v) {
    /*
     * Prepends a value onto a Linked List
     * @param l: pointer to the Linked List
     * @param v: the value to append
    */

    Node* n = node_create(v);

    // Tail and head need to be redefined
    if (l->head == NULL) {
        l->head = n;
        l->tail = n;
    }
    else {
        l->head->next_node = n;
    }
}

// Iteration
Node* linked_begin(LinkedList* l) {
    /*
     * Begins the iteration of a LinkedList.
     * @param l: the Linked List to retrieve the head from
     * @returns: the head of the Linked List
    */ 

    return l->head;
}

Node* linked_next(Node* n) {
    /*
     * Returns the next Node of a LinkedList.
     * @param n: the previous node 
     * @returns: the next node 
    */ 
    
    return n->next_node;
}

