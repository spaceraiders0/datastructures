/*
 * An implementation of a Queue. A datastructure that enforces FIFO order, and
 * fast O(1) enqueue and dequeue operations.
*/ 

#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include "queue.h"


// Constructors
Node* node_create(int new_value) {
    /*
     * Creates a new Node object that holds a value.
     * @param value: the value to store
     * @returns: a pointer to the new Node.
    */ 

    Node* new_node = malloc(sizeof(Node));
    new_node->value = new_value;
    new_node->next_node = NULL;

    return new_node;
}

Queue* queue_create(int count, ...) {
    /*
     * A varadic function that creates a new Queue that is initialized
     * using passed values.
     * @param count: the number of entries for this Queue
     * @param ...: the entries to initialize this Queue with.
     * @returns: a pointer to the new Queue
    */ 

    Queue* new_queue = malloc(sizeof(Queue));

    new_queue->size = count;
    new_queue->head = NULL;
    new_queue->tail = NULL;

    // Create the head node if the length is valid.
    if (new_queue->size > 0) {
        va_list varadic;
        va_start(varadic, count); 

        // Load up a Head and Tail node.
        new_queue->head = node_create(va_arg(varadic, int));
        new_queue->tail = new_queue->head;

        // Finish by loading up each remaining value to initalize with.
        for (int i = 1; i < count; i++) {
            Node* new_node = node_create(va_arg(varadic, int));
            new_queue->tail->next_node = new_node;
            new_queue->tail = new_node;
        }

        va_end(varadic);
    }

    return new_queue;
}

// Operations
void queue_enqueue(Queue* q, int value) {

}
