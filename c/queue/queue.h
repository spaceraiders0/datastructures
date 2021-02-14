/*
 * An implementation of a Queue. A datastructure that enforces FIFO order, and
 * fast O(1) enqueue and dequeue operations.
*/ 

#ifndef QUEUE_HEADER 
#define QUEUE_HEADER 

#define queue_iter(n, q) Node* n = queue_begin(q); n != NULL; n = queue_next(n)

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


Queue* queue_create(int count, ...);
void queue_enqueue(Queue* q, int value);
void queue_print(Queue* q);
int queue_in(Queue* q, int value);
Node* node_create(int new_value);
Node* queue_dequeue(Queue* q);
Node* queue_peek(Queue* p);
Node* queue_begin(Queue* q);
Node* queue_next(Node* n);

#endif
