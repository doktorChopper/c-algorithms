
#include "../include/hash_table.h"

int main() {

    struct chpr_hash_tab ht;

    new_chpr_hash_table(&ht);

    insert_chpr_hash_table(&ht, "dsada");
    insert_chpr_hash_table(&ht, "medusalolfh");
    insert_chpr_hash_table(&ht, "dsada");
    insert_chpr_hash_table(&ht, "kak");
    insert_chpr_hash_table(&ht, "kak");
    insert_chpr_hash_table(&ht, "kak");
    insert_chpr_hash_table(&ht, "dsada");

    delete_chpr_hash_table(&ht, "kak");

    free_chpr_hash_table(&ht);

    return 0;
}

