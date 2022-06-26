#pragma once
#include<stdio.h>
#include "set.h"
#include "graph.h"
#include "maze_generator.h"

enum directions
{
    r = 2, d, l, u
};
void print_maze(struct maze_t* maze);
int validate_move(int new_pos, int prev_pos, struct maze_t* maze);

void solve_maze(struct maze_t* maze);

int get_player_pos(struct maze_t*maze);

int eval_pos(struct maze_t*maze);

struct astar_node_t* astar_find_in_set(struct set_t* set, void* value);

void print_path(struct set_t* all_nodes, int value, struct maze_t* maze);
int find_shortest_path_a_star(
    struct maze_t* maze
);