#include "../include/avl.h"

#include <stdlib.h>
#include <stddef.h>

static inline int balance_factor(node_t*);
static inline void rotate_left(node_t*);
static inline void rotate_right(node_t*);
static inline void fix_height(node_t*);
static void balance(node_t*);
static void free_avl_tree_helper(node_t*);

static void balance(node_t* n) {

    //TODO
    
}

static inline int balance_factor(node_t* n) {
    return n->right->height - n->left->height;
}


static inline void fix_height(node_t* n) {
    if(n->left->height > n->right->height)
        n->height = n->left->height + 1;
    else
        n->height = n->right->height + 1;
}

static inline void rotate_left(node_t* n) {
    node_t* child = n->right;

    child->parent = n->parent;
    if(n->parent != NULL) {
        if(n == n->parent->left) 
            n->parent->left = child;
        else
            n->parent->right = child;

    }

    n->right = child->left;
    if(child->left != NULL)
        child->left->parent = n;

    child->left = n;
    n->parent = child;
}

static inline void rotate_right(node_t* n) {
    node_t* child = n->left;

    child->parent = n->parent;
    if(n->parent != NULL) {
        if(n == n->parent->left) 
            n->parent->left = child;
        else
            n->parent->right = child;
    }

    n->left = child->right;
    if(child->right != NULL)
        child->right->parent = n;

    child->right = n;
    n->parent = child;
}

avl_tree_t* new_avl_tree() {
    avl_tree_t* avl = (avl_tree_t*) malloc(sizeof(avl_tree_t));
    return avl;
}

void free_avl_tree(avl_tree_t *avl) {

    free_avl_tree_helper(avl->root);
    free(avl);

}

static void free_avl_tree_helper(node_t *n) {
    if(n == NULL)
        return;
    free_avl_tree_helper(n->left);
    free_avl_tree_helper(n->right);

    free(n);
}



void avl_insert(int val, avl_tree_t * avl) {

    node_t* new_node = (node_t*) malloc(sizeof(node_t));
    new_node->data = val;
    new_node->height = 1;
    new_node->right = NULL;
    new_node->left = NULL;
    new_node->parent = NULL;

    if(avl->root == NULL) {
        avl->root = new_node;
        return;
    }

    node_t* tmp = avl->root;
    node_t* prv = NULL;

    while(tmp != NULL) {
        prv = tmp;
        if(val < tmp->data)
            tmp = tmp->left;
        else
            tmp = tmp->right;
    }

    if(val < prv->data)
        prv->left = new_node;
    else
        prv->right = new_node;

    new_node->parent = prv;

    // TODO balance
}
