#pragma once
#include <stdio.h>
#include <malloc.h>


struct maze_t
{
    int* field;
    int width;
    int height;
};


struct move
{
    int el_num;
    char direction;
};

struct astar_node_t
{
    int value;
    struct maze_t* board;
    int visited;
    float weight;
    float heuristic;
    struct astar_node_t* prev;
    struct move* prev_move;
};

struct priority_list
{
    struct priority_list_node* list;
    int count;
};

struct priority_list_node
{
    struct astar_node_t data;
    struct priority_list_node* next;
};

struct priority_list* priority_init(struct priority_list* list);

struct priority_list* priority_add(struct priority_list* list, float item, int value);

struct priority_list* remove_list(struct priority_list* list, int value);


void print_priority_list(struct priority_list* list);

struct priority_list* pop(struct priority_list* list, int* res);