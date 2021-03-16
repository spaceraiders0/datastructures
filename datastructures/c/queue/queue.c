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
    /*
     * Adds a new entry to the end of the Queue.
     * @param q: the queue to enqueue into
     * @param value: the value to enqueue.
    */ 

    Node* new_tail = node_create(value);

    // A null head calls for special behavior
    if (q->head == NULL) {
        q->head = new_tail;
        q->tail = new_tail;
    }
    else {
        q->tail->next_node = new_tail;
        q->tail = new_tail;
    }

    q->size++;
}


void queue_print(Queue* q) {
    /*
     * Prints every value in the Queue.
     * @param q: the Queue to display
    */ 

    for (queue_iter(n, q)) {
        printf("%i\n", n->value);
    }
}

int queue_in(Queue* q, int find) {
    /*
     * Returns whether or not the value is inside the Queue.
     * @param find: the value to find
     * @returns: whether or not value is inside the Queue
    */ 

    for (queue_iter(n, q)) {
        if (n->value == find) {
            return 1;
        }
    }

    return 0;
}

Node* queue_dequeue(Queue* q) {
    /*
     * Removes an entry from the front of the Queue. 
     * @param q: the queue to enqueue into
     * @returns: a pointer to the removed Node
    */ 

    Node* dequed_node;

    // If the size is 0, then there is nothing to remove.
    if (q->size == 0) {
        dequed_node = NULL;
    }
    // Size of 1 should set both the head and tail to NULL
    else if (q->size == 1) {
        dequed_node = q->head;

        q->head = NULL;
        q->tail = NULL;
        q->size--;
    }
    else {
        dequed_node = q->head;
        q->head = dequed_node->next_node;
        q->size--;
    }


    return dequed_node;
}

Node* queue_peek(Queue* q) {
    /*
     * Returns the front node without dequing it.
     * @param q: the Queue to peek
    */ 
    
    return q->head;
} 

// Iteration
Node* queue_begin(Queue* q) {
    /*
     * Returns the start of the Queue for iteration.
     * @param q: the Queue to retrieve the beginning of.
     * @returns: the head of the Queue
    */ 

    return q->head;
}

Node* queue_next(Node* n) {
    /*
     * Returns the next node in the Queue.
     * @param n: the previous node
     * @returns: the next node
    */ 

    return n->next_node;
}
