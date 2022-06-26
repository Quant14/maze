#include "set.h"

struct set_t* init_set() {
    struct set_t* new_set = malloc(sizeof(struct set_t));

    new_set->head = NULL;
    new_set->count = 0;

    return new_set;
}

void add_to_set(struct set_t* set, void* value) {
    if (has_in_set(set, value)) return;

    set->head = add_to_list(set->head, value);
    set->count++;
}

int has_in_set(struct set_t* set, void* value) {
    return has_in_list(set->head, value);
}

void remove_from_set(struct set_t* set, void* value) {
    if (set->count <= 0) return;
    if (!has_in_set(set, value)) return;

    set->head = remove_from_list(set->head, value);
    set->count--;
}
