/*
 * An implementation of a Queue. A datastructure that enforces FIFO order, and
 * fast O(1) enqueue and dequeue operations.
*/ 

#ifndef QUEUE_HEADER 
#define QUEUE_HEADER 


// Queue "object"
typedef struct Queue {
    int size;

    struct Node* head;
    struct Node* tail;
} Queue;

// Node "object"
typedef struct Node {
    int value;

    struct Node* next_node;
} Node;


struct Node* node_create(int new_value);
struct Queue* queue_create(int count, ...);

#endif
