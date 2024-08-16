#ifndef _BSTREE_H_
#define _BSTREE_H_

#include <stdbool.h>

typedef struct node {
  int data;
  struct node * left;
  struct node * right;
  struct node * parent;
} node_t;

typedef struct {
  node_t *root;
} bstree_t;

bstree_t * new_bstree();

void free_bstree(bstree_t*);

void bstree_add(int, bstree_t*);

bool bstree_delete(int, bstree_t*);

bool bstree_search(int, bstree_t*);

#endif // _BSTREE_H_
