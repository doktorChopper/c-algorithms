#include "../include/max_heap.h"
#include <stdbool.h>
#include <stdlib.h>

static inline int left_child_idx(int);
static inline int right_child_idx(int);
static inline int parent_idx(int);
static void sift_up(int, max_heap_t*);
static void sift_down(int, max_heap_t*);
static int find_idx(int, max_heap_t*);

static int find_idx(int val, max_heap_t* mah) {
    if(mah->size == 0)
        return -1;

    for(int i = 0; i < mah->size - 1; ++i)
        if(mah->array[i] == val)
            return i;
    return -1;
}

static inline int left_child_idx(int i) {
    return 2 * i + 1;
}

static inline int right_child_idx(int i) {
    return 2 * i + 1;
}

static inline int parent_idx(int i) {
    return (i - 1) / 2;
}

static void sift_up(int i, max_heap_t* mah) {

    int n = mah->size;
    while(n > 0 && mah->array[i] > mah->array[parent_idx(i)]) {
        int tmp = mah->array[i];
        mah->array[i] = mah->array[parent_idx(i)];
        mah->array[parent_idx(i)] = tmp;
        n = (n - 1) / 2;
    }
}

static void sift_down(int i, max_heap_t* mah) {

    int max_child;

    if(left_child_idx(i) < mah->size - 1 && mah->array[left_child_idx(i)] > mah->array[i])
        max_child = left_child_idx(i);
    else
        max_child = i;

    if(right_child_idx(i) < mah->size - 1 && mah->array[right_child_idx(i)] > mah->array[max_child])
        max_child = right_child_idx(i);

    if(max_child != i) {
        int tmp = mah->array[max_child];
        mah->array[max_child] = mah->array[i];
        mah->array[i] = tmp;
        sift_down(max_child, mah);
    }
}

max_heap_t* new_max_heap() {
   max_heap_t* mah = (max_heap_t*) malloc(sizeof(max_heap_t));
    mah->size = 0;
    mah->capacity = 1;
    mah->array = (int*) malloc(mah->capacity);

    return mah;
}

void free_max_heap(max_heap_t *mah) {
    free(mah->array);
    free(mah);
}

void max_heap_insert(int val, max_heap_t * mah) {

    mah->size++;
    if(mah->size == mah->capacity)
        mah->array = (int*) realloc( mah->array, 2 * mah->capacity);
    mah->capacity = 2 * mah->capacity;
    mah->array[mah->size - 1] = val;
    sift_up(mah->size - 1, mah);
}

bool max_heap_search(int val, max_heap_t * mah) {
    if(mah->size == 0) 
        return false;

    for(int i = 0; i < mah->size - 1; ++i)
        if(mah->array[i] == val)
            return true;
    return false;
}

bool max_heap_delete(int val, max_heap_t * mah) {
    int del_idx = find_idx(val, mah);
    if(del_idx == -1)
        return false;

    mah->array[del_idx] = mah->array[mah->size - 1];
    mah->size--;
    sift_down(del_idx, mah);
    return true;
}

int max_heap_extract(max_heap_t * mah) {
    if(mah->size == 0)
        return -1;

    int max = mah->array[0];
    mah->array[0] = mah->array[mah->size - 1];
    mah->size--;

    sift_down(0, mah);

    return max;
}




