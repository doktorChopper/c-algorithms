#ifndef _AVL_H_
#define _AVL_H_

#include "stdbool.h"

typedef struct node {
    int data;
    int height;
    struct node* left;
    struct node* right;
    struct node* parent;
} node_t;

typedef struct {
    node_t* root;
} avl_tree_t;


avl_tree_t* new_avl_tree();
void free_avl_tree(avl_tree_t*);

void avl_insert(int, avl_tree_t*);
bool avl_delete(int, avl_tree_t*);
bool avl_search(int, avl_tree_t*);

#endif // _AVL_H_
