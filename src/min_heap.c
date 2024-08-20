#include "../include/min_heap.h"

#include <stdlib.h>


static void sift_up(int, min_heap_t*);
static void sift_down(int, min_heap_t*);
static inline int left_child_idx(int);
static inline int right_child_idx(int);
static inline int parent_idx(int);
static int find_idx(int, min_heap_t*);

static inline int left_child_idx(int i) {
    return 2 * i + 1;
}


static inline int right_child_idx(int i) {
    return 2 * i + 2;
}

static inline int parent_value(int i) {
    return (i - 1) / 2;
}


static void sift_up(int val, min_heap_t* mih) {
    int i = mih->size;

    while(i > 0 && mih->array[parent_value(i)] > val) {
        mih->array[i] = mih->array[parent_value(i)];
        i = (i - 1) / 2;
    }

    mih->array[i] = val;
}

static void sift_down(int i, min_heap_t* mih) {

    int max_child;

    if(left_child_idx(i) < mih->size && mih->array[left_child_idx(i)] > mih->array[i])
        max_child = left_child_idx(i);
    else
        max_child = i;

    if(right_child_idx(i) < mih->size && mih->array[right_child_idx(i)] > mih->array[max_child])
        max_child = right_child_idx(i);

    if (max_child != i) {
        int tmp = mih->array[i];
        mih->array[i] = mih->array[max_child];
        mih->array[max_child] = tmp;
        sift_down(max_child, mih);
    }

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
    mih->capacity = 2 * mih->capacity;
    sift_up(val, mih);
}

bool min_heap_search(int val, min_heap_t * mih) {

    for(int i = 0; i < mih->size - 1; ++i) 
        if(mih->array[i] == val)
            return true;
    return false;
}

static int find_idx(int val, min_heap_t* mih) {
    for(int i = 0; i < mih->size; ++i)
        if(mih->array[i] == val)
            return i;
    return -1;
}

bool min_heap_delete(int val, min_heap_t * mih) {

    int del_idx = find_idx(val, mih);
    if(del_idx == -1)
        return false;
    
    mih->array[del_idx] = mih->array[mih->size - 1];

    mih->size--;

    sift_down(del_idx, mih);
    return true;
}

int min_heap_extract(min_heap_t* mih) {
    if(mih->size == 0)
        return -1;

    int min = mih->array[0]; 
    mih->array[0] = mih->array[mih->size - 1];

    mih->size--;
    sift_down(0, mih);

    return min;    
}
