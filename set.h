#pragma once

struct set_t;

struct set_t* init_set();

void add_to_set(struct set_t* set, void* value);

int has_in_set(struct set_t* set, void* value);

void remove_from_set(struct set_t* set, void* value);

void print_all_in_set(struct set_t* set);