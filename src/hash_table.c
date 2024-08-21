#include "../include/hash_table.h"
#include <stdbool.h>
#include <stdlib.h>

static inline int hash_function(int, int);
static inline bool check_coeff_filling(hash_table_t*);
static inline int linear_probing(int, int, hash_table_t*);

static inline int hash_function(int x, int c) {
    return x % c;
}

static inline int linear_probing(int x, int i, hash_table_t* ht) {
    return (hash_function(x, ht->capacity) + i) % ht->capacity;
}

static inline bool check_coeff_filling(hash_table_t* ht) {
    if((float) ht->size / ht->capacity < ht->coeff_filling)
        return false;
    return true;
}

hash_table_t* new_hash_table() {
    hash_table_t* ht = (hash_table_t*) malloc(sizeof(hash_table_t));
    ht->size = 0;
    ht->capacity = 1;
    ht->coeff_filling = 0.6;

    ht->array = (int*) malloc(ht->capacity);

    return ht;
}

void free_hash_table(hash_table_t * ht) {
    free(ht->array);
    free(ht);
}

void hash_table_insert(int val, hash_table_t * ht) {

    if(ht->size == 0) {
        ht->array[0] = val;
        ht->size++;
        return;
    }

    if(check_coeff_filling(ht)) {
        ht->array = (int*) realloc(ht->array, 2 * ht->capacity);
        ht->capacity = 2 * ht->capacity;
    }

    int idx = 0;
    for(int i = 0;i < ht->capacity; ++i) {
        idx = linear_probing(val, i, ht);
        if(ht->array[idx] != 0 && ht->array[idx] != -1)
            continue;
        else {
            ht->array[idx] = val;
            ht->size++;
            return;
        } 
    }
}

bool hash_table_delete(int val, hash_table_t * ht) {

    int idx = 0;
    for(int i = 0; i < ht->capacity; ++i) {
        idx = linear_probing(val, i, ht);
        if(ht->array[idx] != val)
            continue;
        else {
            ht->array[idx] = -1;
            ht->size--;
            return true;
        }
    }
    return false;
}

bool hash_table_search(int val, hash_table_t * ht) {
    
    int idx = 0;
    for(int i = 0; i < ht->capacity; ++i) {
        idx = linear_probing(val, i, ht);
        if(ht->array[idx] == 0)
            return false;
        else if(ht->array[idx] == val)
                return true;
        else
            continue;
    }
    return false;
}
