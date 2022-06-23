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

enum Bool { false, true };

// Raboti
enum Bool check(int* grid, int height, int width, int x, int y, int prev_x, int prev_y)
{
	if (y - 1 >= 0)
	{
		if ((grid[x + ((y - 1) * width)] == 0) && (x != prev_x) && ((y - 1) != prev_y))
			return false;
	}
	if (y + 1 < height)
	{
		if ((grid[x + ((y + 1) * width)] == 0) && (x != prev_x) && ((y + 1) != prev_y))
			return false;
	}
	if (x + 1 >= 0)
	{
		if ((grid[x + 1 + (y * width)] == 0) && ((x + 1) != prev_x) && (y != prev_y))
			return false;
	}
	if (x - 1 >= 0)
	{
		if ((grid[x - 1 + (y * width)] == 0) && (((x - 1) != prev_x) && (y != prev_y)))
			return false;
	}
	return true;
}

int* find_neighbours(int* grid, int x, int y, int height, int width, int prev_x, int prev_y)
{
	int* res = malloc(sizeof(int) * 4);
	if (!res) return 0;
	int index = 0;

	//обикалям всичко около точката и ако има отворена клетка значи не може тази точка да е от лабиринта
	//освен само предишната клетка, която е от пътя

	if (x - 1 >= 0)
	{
		if (check(grid, height, width, x - 1, y, prev_x, prev_y) == 1)
			res[index++] = 0; // lqvo - 0
	}
	if (x + 1 < width)
	{
		if (check(grid, height, width, x + 1, y, prev_x, prev_y) == 1)
			res[index++] = 2; // dqsno - 2
	}
	if (y - 1 >= 0)
	{
		if (check(grid, height, width, x, y - 1, prev_x, prev_y) == 1)
			res[index++] = 1; // gore - 1
	}
	if (y + 1 < height)
	{
		if (check(grid, height, width, x, y + 1, prev_x, prev_y) == 1)
			res[index++] = 3; // dolu - 3
	}
	if (index < 4)
		for (; index < 4; index++)
			res[index] = -1;
	return res;
}

// Raboti
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
	grid[x + (y * width)] = 0;
	if ((x + y + 2) == (height + width))
		return grid;
	int neighbours = find_neighbours_count(x, y, height, width);
	if (neighbours == 0)
		return grid;
	int* n_directions = find_neighbours(grid, x, y, height, width, prev_x, prev_y); // neighbours directions
	for (int i = 0; i < neighbours; i++)
	{
		int res = rand() % neighbours;
		if (n_directions[res] != -1)
		{
			int curr_x = x, curr_y = y;
			if (n_directions[res] == 0)
				curr_x--;
			else if (n_directions[res] == 2)
				curr_x++;
			else if (n_directions[res] == 1)
				curr_y--;
			else if (n_directions[res] == 3)
				curr_y++;
			grid = generate_maze1(grid, height, width, curr_x, curr_y, x, y);
			//return grid;
			n_directions[res] = -1;
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
	return generate_maze1(grid, height, width, 0, 0, 0, 0);
}

// Raboti
void print_grid(int* grid, int width, int height)
{
	for (int i = width * 4; i > 0; i--)
		printf("-");
	printf("\n");
	for (int i = 0; i < height; i++)
	{
		for (int z = 0; z < width; z++)
		{
			if (grid[i + (z * width)] == 1)
				printf("# ");
			else
				printf("  ");
		}
		printf("|\n");
	}
	for (int i = width * 2; i > 0; i--)
		printf("-");
}

/*
	int index = 0;
	int sbor = width * height;
	for (int i = 0; i < sbor; i++)
	{
		if (grid[i] == 1)
			printf("# ");
		else
			printf("  ");
		index++;
		if (index == width)
		{
			printf("\n");
			index = 0;
		}
	}*/

//3*реда + колоната = мястото в едномерния масив
//3*1+2 = 5

int main()
{
	int width = 4, height = 4;
	//int grid1[4][4];
	int* grid = malloc(sizeof(int) * width * height);
	if (!grid) return 0;
	for (int i = 0; i < (width * height); i++)
		grid[i] = 1;

	/*grid[0] = 0, grid[1] = 0;
	grid[4] = 0;
	printf("%d\n", check(grid, 4, 4, 1, 1, 1, 0));*/

	print_grid(grid, width, height);

	srand((unsigned int)time((time_t*)NULL));

	int* res = generate(height, width);

	puts("");
	print_grid(res, width, height);

	return 0;
}
