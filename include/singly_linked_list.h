#ifndef _LINKED_LIST_H_
#define _LINKED_LIST_H_

#include <stdbool.h>

typedef struct node {
    int data;
    struct node* next;
} node_t;

typedef struct {
    node_t* head;
} singly_linked_list_t;

singly_linked_list_t* new_sll();
void free_sll(singly_linked_list_t*);

bool sll_delete(int, singly_linked_list_t*);
bool sll_search(int, singly_linked_list_t*);

void sll_insert_after(int, singly_linked_list_t*);

#endif // _LINKED_LIST_H_
