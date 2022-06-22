#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "list.h"
#include "set.h"

int check_neighbour(int* grid, int x, int y, int prev_x, int prev_y)
{
	int curr_x = 0, curr_y = 0;
	curr_x = x - 1;
	curr_y = y - 1;
	for (int z = 0; z < 3; z++)
	{
		curr_x = x - 1;
		curr_y = y - 1 + z;
		for (int i = 3; i > 0; i--)
		{
			if (grid[(curr_x * 3) + curr_y] == 0 && curr_x != prev_x && curr_y != prev_y && curr_x != x && curr_y != y)
				return 0;
			curr_x++;
		}
	}
	return 1;
}

int* find_neighbours(int* grid, int x, int y, int height, int width, int neighbours)
{
	int* res = malloc(sizeof(int) * neighbours);

	//обикалям всичко около точката и ако има отворена клетка значи не може тази точка да е от лабиринта
	//освен само предишната клетка, която е от пътя
	if (x - 1 >= 0 && grid[(x - 1) * 3 + y] == 1)
	{
		if (grid[(x - 1) * 3 + (y - 1)] == 0 || grid[(x - 1) * 3 + (y + 1)] == 0)
			;
	}
	if (x + 1 < width)
	{

	}
	if (y - 1 >= 0)
	{

	}
	if (y + 1 < height)
	{

	}
	return res;
}

int find_neighbours_count(int start_x, int start_y, int height, int width)
{
	int index = 0;
	if (start_x - 1 >= 0)
		index++;
	if (start_x + 1 < width)
		index++;
	if (start_y - 1 >= 0)
		index++;
	if (start_y + 1 < height)
		index++;
	return index;
}

int* generate_maze(int* grid, int height, int width, int start_x, int start_y)
{
	grid[(start_x * 3) + start_y] = 0;
	if ((start_x + start_y) == (height + width))
		return grid;
	int neighbours = find_neighbours_count(start_x, start_y, height, width);
	if (neighbours == 0)
		return grid;
	struct list_node_t* neighbours_ = find_neighbours(start_x, start_y, height, width);
	struct list_node_t* neighbours_indexes = NULL;
	for (int i = 0; i < neighbours; i++)
	{
		int res = rand() % neighbours;
		if (has_in_list(neighbours_indexes, res) == 0)
		{
			struct list_node_t* cpy_neighbours = neighbours_;
			for (int i = 0; i < res; i++)
				cpy_neighbours = cpy_neighbours->next;
			neighbours_indexes = add_to_list(neighbours_indexes, grid[(int)cpy_neighbours->value]);
			if (grid[(int)cpy_neighbours->value] == 0)
				continue;
			grid = generate_maze(grid, height, width, (int)cpy_neighbours->value / 3, (int)cpy_neighbours->value % 3);
		}
	}

	return grid;
}

int* generate_maze1(int* grid, int height, int width, int start_x, int start_y)
{
	grid[(start_x * 3) + start_y] = 0;
	if ((start_x + start_y + 2) == (height + width))
		return grid;
	int neighbours = find_neighbours_count(start_x, start_y, height, width);
	if (neighbours == 0)
		return grid;
	struct list_node_t* neighbours_ = find_neighbours(start_x, start_y, height, width);
	for (int i = 0; i < 4; i++)
	{
		int res = rand() % 4;
		if (res == 0)
		{
			if (start_x - 1 >= 0)
			{
				grid = generate_maze1(grid, height, width, start_x - 1, start_y);
				return grid;
			}
		}
		else if (res == 1)
		{
			if (start_x + 1 >= 0)
			{
				grid = generate_maze1(grid, height, width, start_x + 1, start_y);
				return grid;
			}
		}
		else if (res == 2)
		{
			if (start_y - 1 >= 0)
			{
				grid = generate_maze1(grid, height, width, start_x, start_y - 1);
				return grid;
			}
		}
		else
		{
			if (start_y + 1 >= 0)
			{
				grid = generate_maze1(grid, height, width, start_x, start_y + 1);
				return grid;
			}
		}
	}
	return grid;
}

void print_grid(int* grid, int width, int height)
{
	for (int i = width * 8; i > 0; i--)
		printf("-");
	printf("\n");
	for (int i = 0; i < width; i++)
	{
		for (int z = 0; z < height; z++)
		{
			if (grid[i * 3 + z] == 1)
				printf("# ");
			else
				printf("  ");
		}
		printf("\n");
	}
	for (int i = width * 8; i > 0; i--)
		printf("-");
}

//3*реда + колоната = мястото в едномерния масив
//3*1+2 = 5

int main()
{
	int width = 5, height = 5;
	int* grid = malloc(sizeof(int) * width * height);
	if (!grid) return 0;
	for (int i = 0; i < (width * height); i++)
		grid[i] = 1;

	print_grid(grid, height, width);

	srand((unsigned int)time((time_t*)NULL));

	int* res = generate_maze1(grid, height, width, 0, 0);

	puts("");
	print_grid(grid, width, height);
	/*
	puts("");
	puts("");
	print_grid(res, width, height);
	*/
	return 0;
}
