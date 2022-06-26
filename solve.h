#pragma once
#include "set.h"
#include "graph.h"
#include "maze_generator.h"
#include "main.h"
#include "graphics.h"
#include "frenski.h"

enum directions
{
    r = 2, d, l, u
};

int validate_move(int new_pos, int prev_pos, struct maze_t* maze);

void solve_maze(struct maze_t* maze, SDL_Renderer* rend, int theme, SDL_Rect* character);

int get_player_pos(struct maze_t* maze);

int eval_pos(struct maze_t* maze);

struct astar_node_t* astar_find_in_set(struct set_t* set, void* value);

void print_path(struct set_t* all_nodes, int value, struct maze_t* maze, SDL_Renderer* rend, int theme, SDL_Rect* character);
int find_shortest_path_a_star(
    struct maze_t* maze,
    SDL_Renderer* rend,
    int theme,
    bool print,
    SDL_Rect* character
);