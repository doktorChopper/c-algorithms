
#include "../include/hash_table.h"

int main() {

    int i = 0;
    i++;

    struct chpr_hash_tab ht;

    new_chpr_hash_table(&ht, 10);

    insert_chpr_hash_table(&ht, "dsada");
    insert_chpr_hash_table(&ht, "medusalol");
    insert_chpr_hash_table(&ht, "kak");
    insert_chpr_hash_table(&ht, "jfafja");

    free_chpr_hash_table(&ht);

    return 0;
}

