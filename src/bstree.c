#include "../include/bstree.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>

static node_t* minimum(node_t*);

static node_t* maximum(node_t*);

static node_t* find(int, bstree_t*);

static void replace(node_t*, node_t*, bstree_t*);

static void free_bstree_helper(node_t*);

bstree_t* new_bstree() {
  bstree_t * b = (bstree_t*)malloc(sizeof(bstree_t));
  b->root = NULL;
  return b;
}

void free_bstree(bstree_t * b) {

  free_bstree_helper(b->root);
  free(b);
}


void bstree_add(int val, bstree_t * b) {
  node_t *newNode = (node_t*) malloc(sizeof(node_t));
  newNode->left = NULL;
  newNode->right = NULL;
  newNode->parent = NULL;
  newNode->data = val;

  node_t * tmp = b->root;
  node_t * prev = NULL;

  while (tmp != NULL) {
    prev = tmp; 

    if(val < tmp->data)
      tmp = tmp->left;
    else if (val > tmp->data)
      tmp = tmp->right;
  }

  if(val < prev->data)
    prev->left = newNode;
  else if (val > prev->data)
    prev->right = newNode;

  newNode->parent = prev;
}

bool bstree_delete(int val, bstree_t * b) {
  
  node_t * del = find(val, b);

  if(del == NULL)
    return false;

  if(!del->left)
    replace(del, del->right, b);
  else if(!del->right)
    replace(del, del->left, b);
  else {
    node_t * min = minimum(del->right);

    if(min->parent != del) {
      replace(min, min->right, b);
      min->right = del->right;
      min->right->parent = min;
    }

    replace(del, min, b);
    min->left = del->left;
    min->left->parent = min;
  }

  return true;
}

bool bstree_search(int val, bstree_t * b) {
  if(find(val, b) != NULL)
    return true;
  return false;
}

static void free_bstree_helper(node_t* node) {
  if (!node)
    return;

  free_bstree_helper(node->left);
  free_bstree_helper(node->right);

  free(node);
}

static void replace(node_t * p, node_t * c, bstree_t * b) {
  if(!p->parent)
    b->root = c;
  else if(p == p->parent->left)
    p->parent->left = c;
  else if (p == p->parent->right)
    p->parent->right = c;

  if(c)
    c->parent = p->parent;
}

static node_t* minimum(node_t* n) {
  while(n->left != NULL)
    n = n->left;
  return n;
}

static node_t* maximum(node_t* n) {
  while(n->right != NULL)
    n = n->right;
  return n;
}

static node_t* find(int val, bstree_t* b) {

  node_t * tmp = b->root;

  while(tmp != NULL) {
    if(val < tmp->data)
      tmp = tmp->left;
    else if(val > tmp->data)
      tmp = tmp->right;
    else if(val == tmp->data)
        return tmp;
  }

  return NULL;
}


