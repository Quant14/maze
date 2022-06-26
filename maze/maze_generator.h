#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include "main.h"
#include <string.h>
#include <time.h>

#include "graph.h"
#include "list.h"
#include "priority_list.h"
#include "set.h"
#include "solve.h"

// Print grid with lines
void print_grid(struct maze_t* grid);

// Print grid
void print_grid2(struct maze_t* grid);

// Checks for one neighbour
int check(struct maze_t* grid, int x, int y, int prev_x, int prev_y);

// Find all valid neighbours of a cell
int* find_neighbours(struct maze_t* grid, int x, int y);

// Recursive generate the maze
struct maze_t* generate_maze(struct maze_t* grid, int x, int y, int prev_x, int prev_y);

// General function to generate the maze
struct maze_t* generate();