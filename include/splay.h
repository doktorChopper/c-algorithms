#ifndef _SPLAY_H_
#define _SPLAY_H_

#include "stdbool.h"

typedef struct node {
    int data;
    struct node* left;
    struct node* right;
    struct node* parent;
}node_t;

typedef struct {
    node_t* root;
} splay_tree_t;

splay_tree_t* new_splay_tree();

void free_splay_tree(splay_tree_t*);

void free_splay_tree(splay_tree_t*);

void spl_insert(int, splay_tree_t*);

bool spl_delete(int, splay_tree_t*);

bool spl_search(int, splay_tree_t*);

#endif // _SPLAY_H_
