#include "../include/avl.h"

int main() {
    
    avl_tree_t* avl = new_avl_tree();

    avl_insert(100, avl);
    avl_insert(200, avl);
    avl_insert(75, avl);
    avl_insert(300, avl);
    avl_insert(150, avl);
    avl_insert(125, avl);

    free_avl_tree(avl);

    return 0;
}
