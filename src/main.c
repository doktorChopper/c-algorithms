#include "../include/splay.h"

int main() {
    
    splay_tree_t * spl = new_splay_tree();

    spl_insert(100, spl);
    spl_insert(200, spl);
    spl_insert(50, spl);
    spl_insert(300, spl);
    spl_insert(150, spl);
    spl_insert(75, spl);

    spl_delete(150, spl);
    spl_delete(50, spl);
    spl_delete(100, spl);
    spl_delete(300, spl);
    spl_delete(200, spl);
    spl_delete(75, spl);

    free_splay_tree(spl);

    return 0;
}
