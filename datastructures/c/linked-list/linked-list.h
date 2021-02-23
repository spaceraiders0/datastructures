/*
 * Implementation of a Linked List. A datastructure that "links" values
 * rather than having them be side by side in memory.
*/ 

#include <stdlib.h>

#define NODE_TYPE int 
#define list_iter(n, list) Node* n = list_begin(list); n != NULL; n = list_next(n)

typedef struct Node {
    NODE_TYPE value;

    struct Node* next_node;
} Node;


typedef struct LinkedList {
    int size;
    
    struct Node* head;
    struct Node* tail;
} LinkedList;

LinkedList* linked_create(int last_size, ...);
Node* list_begin(LinkedList* l);
Node* list_next(Node* n);

