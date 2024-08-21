#ifndef _MAX_HEAP_H_
#define _MAX_HEAP_H_

#include <stdbool.h>

typedef struct {
    int size;
    int capacity;
    int *array;
} max_heap_t;

//TODO build_max_heap

max_heap_t* new_max_heap();
void free_max_heap(max_heap_t*);

void max_heap_insert(int, max_heap_t*);

bool max_heap_search(int, max_heap_t*);
bool max_heap_delete(int, max_heap_t*);

int max_heap_extract(max_heap_t*);


#endif // _MAX_HEAP_H_
