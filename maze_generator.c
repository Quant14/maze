#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

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

int* find_neighbours(int* grid, int x, int y, int height, int width, int prev_x, int prev_y)
{
	int* res = malloc(sizeof(int) * 4);
	if (!res) return 0;
	int index = 0;

	//обикалям всичко около точката и ако има отворена клетка значи не може тази точка да е от лабиринта
	//освен само предишната клетка, която е от пътя

	if (x - 1 >= 0 && grid[(x - 1) * 3 + y] == 1)
	{
		if (check_neighbour(grid, x - 1, y, prev_x, prev_y) == 1)
			res[index++] = 0; // lqvo - 0
	}
	if (x + 1 < width)
	{
		if (check_neighbour(grid, x + 1, y, prev_x, prev_y) == 1)
			res[index++] = 2; // dqsno - 2
	}
	if (y - 1 >= 0)
	{
		if (check_neighbour(grid, x, y - 1, prev_x, prev_y) == 1)
			res[index++] = 1; // gore - 1
	}
	if (y + 1 < height)
	{
		if (check_neighbour(grid, x, y + 1, prev_x, prev_y) == 1)
			res[index++] = 3; // dolu - 3
	}
	if (index < 4)
		for (; index < 4; index++)
			res[index] = -1;
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

int* generate_maze1(int* grid, int height, int width, int x, int y, int prev_x, int prev_y)
{
	grid[(x * 3) + y] = 0;
	if ((x + y + 2) == (height + width))
		return grid;
	int neighbours = find_neighbours_count(x, y, height, width);
	if (neighbours == 0)
		return grid;
	int* neighbours_ = find_neighbours(grid, x, y, height, width, prev_x, prev_y);
	for (int i = 0; i < 4; i++)
	{
		int res = rand() % neighbours;
		if (neighbours_[res] != -1)
		{
			int curr_x = x, curr_y = y;
			if (neighbours_[res] == 0)
				curr_x--;
			else if (neighbours_[res] == 2)
				curr_x++;
			else if (neighbours_[res] == 1)
				curr_y--;
			else
				curr_y++;
			grid = generate_maze1(grid, height, width, curr_x, curr_y, x, y);
			//return grid;
			break;
		}
	}
	return grid;
}

int* generate(int height, int width)
{
	int* grid = malloc(sizeof(int) * width * height);
	if (!grid) return 0;
	for (int i = 0; i < (width * height); i++)
		grid[i] = 1;
	return generate_maze1(grid, height, width, 0, 0, -2, -2);
}

void print_grid(int* grid, int width, int height)
{
	for (int i = width * 4; i > 0; i--)
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
		printf("|\n");
	}
	for (int i = width * 4; i > 0; i--)
		printf("-");
}

//3*реда + колоната = мястото в едномерния масив
//3*1+2 = 5

int main()
{
	int width = 4, height = 4;
	int* grid = malloc(sizeof(int) * width * height);
	if (!grid) return 0;
	for (int i = 0; i < (width * height); i++)
		grid[i] = 1;

	print_grid(grid, height, width);

	srand((unsigned int)time((time_t*)NULL));

	int* res = generate(height, width);

	puts("");
	print_grid(res, width, height);

	return 0;
}
