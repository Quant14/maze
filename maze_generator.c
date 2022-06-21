#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "list.h"
#include "set.h"



struct list_node_t* find_neighbours(int start_x, int start_y, int height, int width)
{
	struct list_node_t* list = NULL;
	if (start_x - 1 >= 0)
		list = add_to_list(list, ((start_x - 1) * 3) + start_y);
	if (start_x + 1 < width)
		list = add_to_list(list, ((start_x + 1) * 3) + start_y);
	if (start_y - 1 >= 0)
		list = add_to_list(list, ((start_y - 1) * 3) + start_x);
	if (start_y + 1 < height)
		list = add_to_list(list, ((start_y + 1) * 3) + start_x);
	return list;
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
	int neighbours = find_neighbours_count(start_x, start_y, height, width);
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
			grid[(int)cpy_neighbours->value] = 0;
			generate_maze(grid, height, width, (int)cpy_neighbours->value / 3, (int)cpy_neighbours->value % 3);
		}
	}

	return grid;
}

void print_grid(int* grid, int width, int height)
{
	for (int i = 0; i < width; i++)
	{
		for (int z = 0; z < height; z++)
		{
			if (grid[i * 3 + z] == 1)
				printf("#");
			else
				printf("  ");
		}
	}
}

//3*реда + колоната = мястото в едномерния масив
//3*1+2 = 5

int main()
{
	int width = 3, height = 3;
	int* grid = malloc(sizeof(int) * width * height);
	if (!grid) return 0;
	memset(grid, 1, sizeof(int) * width * height);

	srand((unsigned int)time((time_t*)NULL));

	int* res = generate_maze(grid, height, width, 0, 0);

	print_grid(grid, width, height);
	puts("");
	puts("");
	puts("");
	print_grid(res, width, height);

	return 0;
}
