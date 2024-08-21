#ifndef _HASH_TABLE_H_
#define _HASH_TABLE_H_

#include <stdbool.h>


typedef struct {
    int *array;
    int size;
    int capacity;
    float coeff_filling;
} hash_table_t;

hash_table_t* new_hash_table();

void free_hash_table(hash_table_t*);

void hash_table_insert(int, hash_table_t*);

bool hash_table_delete(int, hash_table_t*);

bool hash_table_search(int, hash_table_t*);

#endif // _HASH_TABLE_H_
