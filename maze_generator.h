#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Raboti pravilno veche
void print_grid(struct maze_t grid);

void print_grid2(struct maze_t grid);

int check(struct maze_t grid, int x, int y, int prev_x, int prev_y);
int* find_neighbours(struct maze_t grid, int x, int y, int prev_x, int prev_y, int neighbours);
int find_neighbours_count1(struct maze_t grid, int x, int y);
int* generate_maze1(struct maze_t grid, int x, int y, int prev_x, int prev_y);
struct maze_t generate(int height, int width);