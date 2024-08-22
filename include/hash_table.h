#ifndef _CHOPPER_HASHTAB_H_
#define _CHOPPER_HASHTAB_H_

#include <stdbool.h>

struct chpr_hash_tab_entry {
    struct chpr_hash_tab_entry* next;
    const char* string;
    unsigned long hash;
};

struct chpr_hash_tab {
    struct chpr_hash_tab_entry** table;
    unsigned int ent_size;
    unsigned int size;
    unsigned int count;
};

bool new_chpr_hash_table(struct chpr_hash_tab*, unsigned int);
bool new_chpr_hash_table_n(struct chpr_hash_tab*,unsigned int, unsigned int);

#endif // _CHOPPER_HASHTAB_H_
