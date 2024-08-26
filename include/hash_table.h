#ifndef _CHOPPER_HASHTAB_H_
#define _CHOPPER_HASHTAB_H_

#include <stdbool.h>

typedef unsigned long (*table_hash_function) (const char*);

struct chpr_hash_tab_entry {
    struct chpr_hash_tab_entry* next;
    unsigned long hash;
    const char* string;
    bool deleted;
};

struct chpr_hash_tab {
    struct chpr_hash_tab_entry** table;
    table_hash_function hash_func;
    unsigned int ent_size;
    unsigned int size;
    unsigned int count;
};

bool new_chpr_hash_table(struct chpr_hash_tab*);
bool new_chpr_hash_table_n(struct chpr_hash_tab*, unsigned int, table_hash_function);
void free_chpr_hash_table(struct chpr_hash_tab*);
void insert_chpr_hash_table(struct chpr_hash_tab*, const char*);
struct chpr_hash_tab_entry* search_chpr_hash_table(struct chpr_hash_tab*, const char*);
bool delete_chpr_hash_table(struct chpr_hash_tab*, const char*);

#endif // _CHOPPER_HASHTAB_H_
