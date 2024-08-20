#include "../include/avl.h"
#include <stdio.h>
#include <stdlib.h>

#define SIZE 100

void gen(int* arr, int size) {

    int n = 0;
    for(int i = 0; i < size; ++i) {
        n = rand() % 1000;
        arr[i] = n;
    }

}

int main() {
    
    avl_tree_t* avl = new_avl_tree();

    int arr[SIZE] = {0};

    gen(arr, sizeof(arr) / sizeof(int));

    for(int i = 0; i < SIZE; ++i) {
        avl_insert(arr[i], avl);
    }

    printf("%lu\n", sizeof(arr) / sizeof(int));

    free_avl_tree(avl);

    return 0;
}
