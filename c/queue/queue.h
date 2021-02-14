/*
 * An implementation of a Queue. A datastructure that enforces FIFO order, and
 * fast O(1) enqueue and dequeue operations.
*/ 

#ifndef QUEUE_HEADER 
#define QUEUE_HEADER 

#define queue_iter(n, q) Node* n = queue_begin(my_queue); n != NULL; n = queue_next(n)

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
void queue_enqueue(Queue* q, int value);
Node* queue_dequeue(Queue* q);
Node* queue_begin(Queue* q);
Node* queue_next(Node* n);

#endif
