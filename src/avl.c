#include "../include/avl.h"

#include <stdbool.h>
#include <stdlib.h>
#include <stddef.h>

static inline int balance_factor(node_t*);
static inline node_t* rotate_left(node_t*);
static inline node_t* rotate_right(node_t*);
static inline void fix_height(node_t*);
static node_t* minimum(node_t*);
static node_t* maximum(node_t*);
static node_t* find(int, node_t*);
static node_t* balance(node_t*);
static void free_avl_tree_helper(node_t*);
static inline int node_height(node_t*);
static node_t* avl_insert_helper(int, node_t*);

static node_t* minimum(node_t* n) {
    while(n->left != NULL) 
        n = n->left;
    return n;
}

static node_t* maximum(node_t* n) {
    while (n->right != NULL) 
        n = n->right;
    return n;
}

static node_t* find(int val, node_t* root) {

    while(root != NULL) {
        if(val < root->data)
            root = root->left;
        else if(val > root->data)
            root = root->right;
        else if(val == root->data)
                return root;
    }

    return NULL;
}

static node_t* balance(node_t* n) {

    fix_height(n);

    if(balance_factor(n) == 2) {
        if(balance_factor(n->right) < 0)
            n->right = rotate_right(n->right);
        return rotate_left(n);
    } else if (balance_factor(n) == -2) {
        if(balance_factor(n->left) > 0)
            n->left = rotate_left(n->left);
        return rotate_right(n);
    }

    return n;
    
}

static inline int node_height(node_t* n) {
    if(n == NULL)
        return 0;
    return n->height;
}

static inline int balance_factor(node_t* n) {
    return node_height(n->right) - node_height(n->left);
}


static inline void fix_height(node_t* n) {
    if(node_height(n->left) > node_height(n->right))
        n->height = node_height(n->left) + 1;
    else
        n->height = node_height(n->right) + 1;
}

static inline node_t* rotate_left(node_t* n) {
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

    fix_height(n);
    fix_height(child);

    return child;
}

static inline node_t* rotate_right(node_t* n) {
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

    fix_height(n);
    fix_height(child);

    return child;
}

avl_tree_t* new_avl_tree() {
    avl_tree_t* avl = (avl_tree_t*) malloc(sizeof(avl_tree_t));
    avl->root = NULL;
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


bool avl_search(int val, avl_tree_t * avl) {
    node_t* retval = find(val, avl->root);
    if(retval == NULL)
        return false;
    return true;
}

bool avl_delete(int val, avl_tree_t * avl) {
    
    node_t* del = find(val, avl->root);
    if(del == NULL) 
        return false;

    //TODO
    return true;
}

static node_t* avl_insert_helper(int val, node_t* n) {

    if(n == NULL) {
        n = (node_t*) malloc(sizeof(node_t));
        n->data = val;
        n->height = 1;
        n->left = NULL;
        n->right = NULL;
        n->parent = NULL;
        return n;
    }

    if(val < n->data) {
        n->left = avl_insert_helper(val, n->left);
        n->left->parent = n;
    } else if(val > n->data) {
        n->right = avl_insert_helper(val, n->right);
        n->right->parent = n;
    } 

    return balance(n);
}

void avl_insert(int val, avl_tree_t * avl) {
    avl->root = avl_insert_helper(val, avl->root);
}

