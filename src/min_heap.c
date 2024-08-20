#include "../include/min_heap.h"

#include <stdlib.h>


static void sift_up(int, min_heap_t*);
static void sift_down(int, min_heap_t*);
static inline int left_child_value(int, int*);
static inline int right_child_value(int, int*);
static inline int parent_value(int, int*);

static inline int left_child_value(int i, int* arr) {
    return arr[2 * i + 1];
}


static inline int right_child_value(int i, int* arr) {
    return arr[2 * i + 2];
}

static inline int parent_value(int i, int* arr) {
    return arr[(i - 1) / 2];
}


static void sift_up(int val, min_heap_t* mih) {
    int i = mih->size;

    while(i > 0 && parent_value(i, mih->array) > val) {
        mih->array[i] = parent_value(i, mih->array);
        i = (i - 1) / 2;
    }

    mih->array[i] = val;
}

static void sift_down(int val, min_heap_t* mih) {


}

min_heap_t* new_min_heap() {
   min_heap_t* min_heap = (min_heap_t*) malloc(sizeof(min_heap_t)); 
    
    min_heap->size = 0;
    min_heap->capacity = 1;
    min_heap->array = (int*) malloc(min_heap->capacity * sizeof(int));

    return min_heap;
}

void free_min_heap(min_heap_t * mih) {
    free(mih->array);
    free(mih);
}

void min_heap_add(int val, min_heap_t * mih) {

    mih->size++;
    if(mih->size == mih->capacity)
        mih->array = (int*) realloc(mih->array, 2 * mih->capacity);
    sift_up(val, mih);
}
