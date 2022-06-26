#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "maze_generator.h"

// Raboti
void print_grid(struct maze_t grid)
{
	printf("\t|");
	for (int i = grid.width * 2; i > 0; i--)
		printf("-");
	printf("|\n\t|");

	int index = 0;
	int multiplicated = grid.width * grid.height;
	for (int i = 0; i < multiplicated; i++)
	{
		if (grid.field[i] == 1)
			printf("#|");
		else
			printf(" |");
		index++;
		if (index == grid.width)
		{
			printf("|\n\t|");
			index = 0;
		}
	}

	for (int i = grid.width * 2; i > 0; i--)
		printf("-");
	printf("|");
}

void print_grid2(struct maze_t grid)
{
	printf("\t|");
	for (int i = grid.width; i > 0; i--)
		printf("-");
	printf("|\n\t|");

	int index = 0;
	int multiplicated = grid.width * grid.height;
	for (int i = 0; i < multiplicated; i++)
	{
		if (grid.field[i] == 1)
			printf("#");
		else
			printf(" ");
		index++;
		if (index == grid.width)
		{
			printf("|\n\t|");
			index = 0;
		}
	}

	for (int i = grid.width; i > 0; i--)
		printf("-");
	printf("|");
}

// Raboti
int check(struct maze_t grid, int x, int y, int prev_x, int prev_y)
{
	if (grid.field[x + (y * grid.width)] == 0)
		return 0;
	if (prev_x == x && prev_y == y)
		return 0;

	if (y - 1 >= 0)
	{
		if ((grid.field[x + ((y - 1) * grid.width)] == 0) && (x != prev_x) && ((y - 1) != prev_y))
			return 0;
	}
	if (y + 1 < grid.height)
	{
		if ((grid.field[x + ((y + 1) * grid.width)] == 0) && (x != prev_x) && ((y + 1) != prev_y) && (((grid.width * grid.width) - 1) != ((y - 1) * x)))
			return 0;
	}
	if (x + 1 < grid.width)
	{
		if ((grid.field[x + 1 + (y * grid.width)] == 0) && ((x + 1) != prev_x) && (y != prev_y))
			return 0;
	}
	if (x - 1 >= 0)
	{
		if ((grid.field[x - 1 + (y * grid.width)] == 0) && (((x - 1) != prev_x) && (y != prev_y)))
			return 0;
	}
	return 1;
}

// Raboti
int* find_neighbours(struct maze_t grid, int x, int y)
{
	int* res = malloc(sizeof(int) * 5);
	if (!res) return 0;
	int index = 1, cnt = 0;

	//обикалям всичко около текущата клетка и ако има отворена клетка значи не може тази точка да е от лабиринта
	//освен само предишната клетка, която е от пътя

	if (x - 1 >= 0)
	{
		if (check(grid, x - 1, y, x, y) == 1) // vmesto x i y -> prev_x, prev_y
			res[index++] = 0, cnt++; // lqvo - 0
	}
	if (x + 1 < grid.width)
	{
		if (check(grid, x + 1, y, x, y) == 1)
			res[index++] = 2, cnt++; // dqsno - 2
	}
	if (y - 1 >= 0)
	{
		if (check(grid, x, y - 1, x, y) == 1)
			res[index++] = 1, cnt++; // gore - 1
	}
	if (y + 1 < grid.height)
	{
		if (check(grid, x, y + 1, x, y) == 1)
			res[index++] = 3, cnt++; // dolu - 3
	}

	res[0] = cnt;
	if (index < 5)
		for (; index < 5; index++)
			res[index] = -1;
	return res;
}

// Raboti
int* generate_maze(struct maze_t grid, int x, int y, int prev_x, int prev_y)
{
	grid.field[x + (y * grid.width)] = 0;

	// For tests
	/*puts("");
	puts("");
	print_grid(grid);*/

	if ((x + y + 2) == (grid.height + grid.width))
		return grid.field;

	int* neigh_directions = find_neighbours(grid, x, y); // neighbours directions

	int neighbours_cnt = neigh_directions[0];
	if (neighbours_cnt == 0)
		return grid.field;
	
	int rnd = 0;

	for (int i = 0; i < neighbours_cnt; i++)
	{
		// ignore neigh_directions[0] - this is the count of the neighbours
		if (neigh_directions[2] == -1 && neigh_directions[0] == 1)
			rnd = 0;
		else
			rnd = rand() % neighbours_cnt;
		rnd++;

		if (neigh_directions[rnd] != -1)
		{
			int curr_x = x, curr_y = y;
			if (neigh_directions[rnd] == 0)
				curr_x--;
			else if (neigh_directions[rnd] == 2)
				curr_x++;
			else if (neigh_directions[rnd] == 1)
				curr_y--;
			else if (neigh_directions[rnd] == 3)
				curr_y++;

			grid.field = generate_maze(grid, curr_x, curr_y, x, y);

			neigh_directions[rnd] = -1;
			neigh_directions = find_neighbours(grid, x, y);

			//neighbours_cnt = neigh_directions[0];
			//if (grid.field[(grid.width * grid.height) - 1] == 0)
				//return grid.field;
		}
	}
	return grid.field;
}

// Raboti
struct maze_t* generate()
{
	int height, width, seed, from_scanf = 0;
	from_scanf = scanf("%d %d %d", &height, &width, &seed);

	if (seed == -1) // we do not have seed so do not need it
		srand((unsigned int)time((time_t*)NULL));
	else
		srand(seed);

	struct maze_t* grid = malloc(sizeof(struct maze_t));
	if (!grid) return 0;
	grid->field = malloc(sizeof(int) * width * height);
	if (!grid->field) return 0;
	grid->height = height, grid->width = width;

	for (int i = 0; i < (width * height); i++)
		grid->field[i] = 1;

	print_grid2(*grid); // optional
	int* res = generate_maze(*grid, 0, 0, 0, 0);

	if (grid->field[(width * height) - 1] == 1)
		grid->field[(width * height) - 1] = 0;

	return grid;
}
