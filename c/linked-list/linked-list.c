/*
 * Implementation of a Linked List. A datastructure that "links" values
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

LinkedList* linked_create(int list_size, ...) {
    /*
     * Initializes a Linked List.
     * @param list_size: the size of the list
     * @param ...: the entries to initialize with
    */ 

    LinkedList* new_list = malloc(sizeof(LinkedList));
    new_list->head = NULL;
    new_list->tail = NULL;
    new_list->size = list_size;

    // A size of 0 means no values to initialize.
    if (list_size > 0) {
        va_list varadic;
        va_start(varadic, list_size);

        // Load up the head node.
        new_list->head = node_create(va_arg(varadic, NODE_TYPE));
        new_list->tail = new_list->head;

        // Load up the remaining nodes
        for (int i = 1; i < list_size; i++) {
            new_list->tail->next_node = node_create(va_arg(varadic, NODE_TYPE));
            new_list->tail = new_list->tail->next_node;
        }
    }

    return new_list;
}

// Iteration
Node* list_begin(LinkedList* l) {
    /*
     * Begins the iteration of a LinkedList.
     * @param l: the Linked List to retrieve the head from
     * @returns: the head of the Linked List
    */ 

    return l->head;
}

Node* list_next(Node* n) {
    /*
     * Returns the next Node of a LinkedList.
     * @param n: the previous node 
     * @returns: the next node 
    */ 
    
    return n->next_node;
}
