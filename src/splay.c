#include "../include/splay.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <time.h>


static void free_splay_tree_helper(node_t*);
static inline void zig(node_t*);
static void zag(node_t*);
static node_t* splay(node_t*);
static node_t* find(int, splay_tree_t*);
static node_t* minimum(node_t*);

static inline void zig(node_t* n) {
    node_t *child = n->left;
    child->parent = n->parent;

    if(n->parent != NULL){
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

static void zag(node_t* n) {
    node_t* child = n->right;
    child->parent = n->parent;

    if(n->parent != NULL){
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

static node_t* splay(node_t* n) {

    while(n->parent != NULL) {
        if(n == n->parent->left){
            if(n->parent->parent == NULL)
                zig(n->parent);
            else if(n->parent == n->parent->parent->left) {
                zig(n->parent->parent);
                zig(n->parent);
            } else {
                zig(n->parent);
                zag(n->parent);
            }
        } else {
            if(n->parent->parent == NULL)
                zag(n->parent);
            else if(n->parent == n->parent->parent->right) {
                zag(n->parent->parent);
                zag(n->parent);
            } else {
                zag(n->parent);
                zig(n->parent);
            }
        }

    }

    return n;

}

static node_t* find(int val, splay_tree_t* spl) {

    node_t* tmp = spl->root;
    node_t* prv = NULL;

    while(tmp != NULL) {
        prv = tmp;
        if(val < tmp->data)
            tmp = tmp->left;
        else if (val > tmp->data)
                tmp = tmp->right;
        else {
            spl->root = splay(tmp);
            return tmp;
        }
    }

    spl->root = splay(prv);
    return NULL;
}

splay_tree_t* new_splay_tree() {
    splay_tree_t* spl = (splay_tree_t*) malloc(sizeof(splay_tree_t));
    spl->root = NULL;
    return spl;
}

void free_splay_tree(splay_tree_t * spl) {

    free_splay_tree_helper(spl->root);
    free(spl);
}

static void free_splay_tree_helper(node_t * n) {
    if(!n)
        return;

    free_splay_tree_helper(n->left);
    free_splay_tree_helper(n->right);

    free(n);
}

void spl_insert(int val, splay_tree_t * spl) {

    node_t* new_node = (node_t*)malloc(sizeof(node_t));
    new_node->data = val;
    new_node->left = NULL;
    new_node->right = NULL;
    new_node->parent = NULL;

    if(spl->root == NULL){
        spl->root = new_node; 
        return;
    }

    node_t* tmp = spl->root;
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
    spl->root = splay(new_node);
}

static node_t* minimum(node_t* n) {
    while (n->left != NULL) 
        n = n->left;
   return n; 
}

bool spl_delete(int val, splay_tree_t * spl) {

    node_t * del = find(val, spl);

    if(del == NULL)
        return false;

    if(del->right == NULL)
        spl->root = del->left;
    else {
        node_t* min = minimum(del->right);
        del->right->parent = NULL;
        spl->root = splay(min);
        min->left = del->left;
        if(del->left)
            del->left->parent = min;
    }

    free(del);
    if(spl->root)
        spl->root->parent = NULL;

    return true;
}

bool spl_search(int val, splay_tree_t * spl) {

    node_t* tmp = spl->root;
    node_t* prv = NULL;

    while(tmp != NULL){
        if(val < tmp->data)
            tmp = tmp->left;
        else if(val > tmp->data)
            tmp = tmp->right;
        else {
            spl->root = splay(tmp);
            return true;
        }
    }

    spl->root = splay(prv);
    return false;
}
