#pragma once
#include "priority_list.h"

struct connection_t {
    int a, b;
    struct move move;
};

struct graph_t {
    struct set_t* nodes; // node_t
    struct set_t* connections; // struct connection_t
};

struct node_t
{
    struct board* board;
    int value;
};


struct node_t* find_node_in_set(struct set_t* set, void* value);

struct node_t* find_node_in_set_board(struct set_t* set, struct board* board);
struct astar_node_t* astar_find_node_in_set_board(struct set_t* set, struct board* board);
struct connection_t* find_connection_in_set(struct set_t* set, void* value);


struct connection_t* connect_nodes(struct graph_t* g, int a, int b, struct board b_a, struct board b_b, struct move m);

void print_graph(struct graph_t* graph);