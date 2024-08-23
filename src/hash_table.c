#include "../include/hash_table.h"
#include <stdlib.h>
#include <string.h>

#define DEFAULT_SIZE 61

static unsigned int chpr_default_hash_table_size = DEFAULT_SIZE;

static inline unsigned long hash_func(const char*, unsigned int);
static unsigned long higher_prime_number(unsigned long);

static unsigned long higher_prime_number(unsigned long n) {
    static const unsigned long primes[] = {
      (unsigned long) 31,
      (unsigned long) 61,
      (unsigned long) 127,
      (unsigned long) 251,
      (unsigned long) 509
    };

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

static inline unsigned long hash_func(const char* string, unsigned int size) {
    return strlen(string) % size;
}

bool new_chpr_hash_table(struct chpr_hash_tab* table, unsigned int ent_size) {
    return new_chpr_hash_table_n(table, ent_size, chpr_default_hash_table_size);
}

bool new_chpr_hash_table_n(struct chpr_hash_tab* table, unsigned int ent_size, unsigned int size) {

    int alloc = size * sizeof(struct chpr_hash_tab_entry*);

    table->table = (struct chpr_hash_tab_entry**) malloc(alloc);
    if(table->table == NULL)
        return false;

    memset(table->table, 0, alloc);
    table->size = size;
    table->ent_size = ent_size;
    table->count = 0;
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

void insert_chpr_hash_table(struct chpr_hash_tab * table, const char * string) {
    unsigned int index;
    struct chpr_hash_tab_entry* ent;

    ent = (struct chpr_hash_tab_entry*) malloc(sizeof(struct chpr_hash_tab_entry));
    ent->string = string;
    ent->hash = hash_func(string, 127);
    
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

            }
        }

        table->table = new_table;
        table->size = new_size;
    }

}
