#pragma once

struct list_node_t {
	void* value;
	struct list_node_t* next;
};

struct list_node_t* init_list_node(void* value);

struct list_node_t* add_to_list(struct list_node_t* list, void* value);

struct list_node_t* add_to_end_of_list(struct list_node_t* list, void* value);

int has_in_list(struct list_node_t* list, void* value);

struct list_node_t* remove_from_list(struct list_node_t* list, void* value);