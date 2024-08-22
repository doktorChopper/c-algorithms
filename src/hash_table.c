#include "../include/hash_table.h"
#include <stdlib.h>
#include <string.h>

#define DEFAULT_SIZE 61

static unsigned int chpr_default_hash_table_size = DEFAULT_SIZE;

bool new_chpr_hash_table(struct chpr_hash_tab* table, unsigned int ent_size) {
    return new_chpr_hash_table_n(table, ent_size, chpr_default_hash_table_size);
}

bool new_chpr_hash_table_n(struct chpr_hash_tab* table, unsigned int ent_size, unsigned int size) {
    int alloc = size * sizeof(struct chpr_hash_tab_entry*);

    table->table = (struct chpr_hash_tab_entry**) malloc(alloc);
    if(table->table == NULL)
        return false;

    memset((void*) table->table, 0, alloc);
    table->size = size;
    table->ent_size = ent_size;
    table->count = 0;
    return true;
}
