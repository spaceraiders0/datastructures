/*
 * Implementation of a Linked List. A datastructure that "links" values
 * rather than having them be side by side in memory.
*/ 

#include <stdlib.h>

#define NODE_TYPE int 
#define linked_iter(n, linked) Node* n = linked_begin(linked); n != NULL; n = linked_next(n)
#define linked_range(i, linked) int i = 0; i < linked->length; i++

typedef struct Node {
    NODE_TYPE value;

    struct Node* next_node;
} Node;


typedef struct LinkedList {
    int length;

    struct Node* head;
    struct Node* tail;
} LinkedList;


LinkedList* linked_create(int last_size, ...);
NODE_TYPE linked_find(LinkedList* l, NODE_TYPE f);
NODE_TYPE linked_pop(LinkedList*, Node* n);
Node* linked_index(LinkedList* l, NODE_TYPE i);
Node* linked_begin(LinkedList* l);
Node* linked_next(Node* n);
void linked_insert(Node* n, NODE_TYPE v);
void linked_remove(LinkedList* l, Node* n);
void linked_append(LinkedList* l, NODE_TYPE v);
void linked_prepend(LinkedList* l, NODE_TYPE v);
int linked_get_index(LinkedList* l, Node* n);
int linked_index_insert(LinkedList* l, int i, NODE_TYPE v);
