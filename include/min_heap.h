#ifndef _MIN_HEAP_H_
#define _MIN_HEAP_H_

typedef struct {
    int size;
    int capacity;
    int* array;
} min_heap_t;

min_heap_t* new_min_heap();
void free_min_heap(min_heap_t*);

void min_heap_add(int, min_heap_t*);

bool min_heap_search(int, min_heap_t*);

bool min_heap_delete(int, min_heap_t*);

int min_heap_extract(min_heap_t*);

#endif // _MIN_HEAP_H_
