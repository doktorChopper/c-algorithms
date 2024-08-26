#include "../include/hash_table.h"
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define DEFAULT_SIZE 7

static unsigned int chpr_default_hash_table_size = DEFAULT_SIZE;

static inline unsigned long default_hash_func(const char*);
static unsigned long higher_prime_number(unsigned long);

static const unsigned long primes[] = {
    (unsigned long) 11,
    (unsigned long) 17,
    (unsigned long) 31,
    (unsigned long) 61,
    (unsigned long) 127,
    (unsigned long) 251,
    (unsigned long) 509
};

static unsigned long higher_prime_number(unsigned long n) {

    const unsigned long * low = &primes[0];
    const unsigned long * high = &primes[sizeof(primes) / sizeof(primes[0])];

    while(low != high) {
        const unsigned long * mid = low + (high - low) / 2;
        
        if(n >= *mid)
            low = mid + 1;
        else
            high = mid;
    }

    if(n >= *low)
        return 0;
    return *low;
}

static inline unsigned long default_hash_func(const char* string) {
    return strlen(string);
}

bool new_chpr_hash_table(struct chpr_hash_tab* table){
    return new_chpr_hash_table_n(table, chpr_default_hash_table_size, default_hash_func);
}

bool new_chpr_hash_table_n(struct chpr_hash_tab* table, unsigned int size, table_hash_function hash_func) {

    int alloc = size * sizeof(struct chpr_hash_tab_entry*);

    table->table = (struct chpr_hash_tab_entry**) malloc(alloc);
    if(table->table == NULL)
        return false;

    memset(table->table, 0, alloc);
    table->size = size;
    table->count = 0;
    table->hash_func = hash_func;
    return true;
}

void free_chpr_hash_table(struct chpr_hash_tab* table) {

    struct chpr_hash_tab_entry* tmp;

    for(int i = 0; i < table->size; ++i) {
        tmp = table->table[i];
        while(tmp != NULL) {
           tmp = tmp->next; 
            free(table->table[i]);
            table->table[i] = tmp;
        }
    }
    free(table->table);
}

struct chpr_hash_tab_entry* search_chpr_hash_table(struct chpr_hash_tab * table, const char * string) {
    unsigned int index;    
    unsigned long hash;

    hash = table->hash_func(string);
    index = hash % table->size;

    for(struct chpr_hash_tab_entry* tmp = table->table[index]; tmp; tmp = tmp->next) 
        if(tmp->hash == hash && strcmp(tmp->string, string) == 0) 
                return tmp;
    return NULL;
}

bool delete_chpr_hash_table(struct chpr_hash_tab * table, const char * string) {
    unsigned int index;    
    unsigned long hash;
    struct chpr_hash_tab_entry* del;
    struct chpr_hash_tab_entry* prev;

    hash = table->hash_func(string);
    index = hash % table->size;

    prev = table->table[index];
    for(del = table->table[index]; del; del = del->next) {
        if(del->hash == hash && strcmp(del->string, string) == 0) 
            break;
        prev = del;
    }
    
    if(del == NULL)
        return false;

    if(del == table->table[index])
        table->table[index] = del->next;
    else
        prev->next = del->next;
    free(del);
    del = NULL;
    table->count--;

    return true;
}

void insert_chpr_hash_table(struct chpr_hash_tab * table, const char * string) {
    unsigned int index;
    struct chpr_hash_tab_entry* ent;

    ent = (struct chpr_hash_tab_entry*) malloc(sizeof(struct chpr_hash_tab_entry));
    ent->string = string;
    ent->hash = table->hash_func(string);
    ent->deleted = false;
    
    index = ent->hash % table->size;

    ent->next = table->table[index];
    table->table[index] = ent;

    table->count++;

    if(table->count > table->size * 3 / 4) {

        struct chpr_hash_tab_entry ** new_table;  
        unsigned long new_size = higher_prime_number(table->size);

        unsigned long alloc = new_size * sizeof(struct chpr_hash_tab_entry*);
        
        new_table = (struct chpr_hash_tab_entry**) malloc(alloc);

        memset(new_table, 0, alloc);

        for(unsigned int i = 0; i < table->size; ++i) {
            while(table->table[i]) {
                struct chpr_hash_tab_entry* chain = table->table[i];
                struct chpr_hash_tab_entry* chain_end = chain;
     
                while (chain_end->next && chain_end->next->hash == chain->hash)
                    chain_end = chain_end->next;

                table->table[i] = chain_end->next;
                index = chain->hash % new_size;
                chain_end->next = new_table[index];
                new_table[index] = chain;
            }
        }

        free(table->table);

        table->table = new_table;
        table->size = new_size;
    }
}

