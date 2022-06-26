#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct maze_t
{
	int* field;
	int width;
	int height;
};

// Print grid with lines
void print_grid(struct maze_t grid);

// Print grid
void print_grid2(struct maze_t grid);

// Checks for one neighbour
int check(struct maze_t grid, int x, int y, int prev_x, int prev_y);

// Find all valid neighbours of a cell
int* find_neighbours(struct maze_t grid, int x, int y);

// Recursive generate the maze
int* generate_maze(struct maze_t grid, int x, int y, int prev_x, int prev_y);

// General function to generate the maze
struct maze_t generate(int height, int width, int seed);