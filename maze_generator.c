#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Raboti
int check(int* grid, int height, int width, int x, int y, int prev_x, int prev_y)
{
	if (y - 1 >= 0)
	{
		if ((grid[x + ((y - 1) * width)] == 0) && (x != prev_x) && ((y - 1) != prev_y))
			return 0;
	}
	if (y + 1 < height)
	{
		if ((grid[x + ((y + 1) * width)] == 0) && (x != prev_x) && ((y + 1) != prev_y))
			return 0;
	}
	if (x + 1 >= 0)
	{
		if ((grid[x + 1 + (y * width)] == 0) && ((x + 1) != prev_x) && (y != prev_y))
			return 0;
	}
	if (x - 1 >= 0)
	{
		if ((grid[x - 1 + (y * width)] == 0) && (((x - 1) != prev_x) && (y != prev_y)))
			return 0;
	}
	return 1;
}

// Raboti
int* find_neighbours(int* grid, int x, int y, int height, int width, int prev_x, int prev_y, int neighbours)
{
	int* res = malloc(sizeof(int) * neighbours);
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

// Raboti
int* generate_maze1(int* grid, int height, int width, int x, int y, int prev_x, int prev_y)
{
	grid[x + (y * width)] = 0;
	if ((x + y + 2) == (height + width))
		return grid;
	int neighbours = find_neighbours_count(x, y, height, width);
	if (neighbours == 0)
		return grid;
	int* n_directions = find_neighbours(grid, x, y, height, width, prev_x, prev_y, neighbours); // neighbours directions
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
			if (grid[(width * height) - 1] == 0)
				return grid;
		}
	}
	return grid;
}

// Raboti
void print_grid(int* grid, int width, int height)
{
	printf("\t");
	for (int i = width * 2; i > 0; i--)
		printf("-");
	printf("\n\t|");
	for (int i = 0; i < height; i++)
	{
		for (int z = 0; z < width; z++)
		{
			if (grid[i + (z * width)] == 1)
				printf("# ");
			else
				printf("  ");
		}
		printf("|\n\t|");
	}
	for (int i = width * 2; i > 0; i--)
		printf("-");
}

// Raboti
int* generate(int height, int width)
{
	int* grid = malloc(sizeof(int) * width * height);
	if (!grid) return 0;
	for (int i = 0; i < (width * height); i++)
		grid[i] = 1;
	print_grid(grid, width, height);
	return generate_maze1(grid, height, width, 0, 0, 0, 0);
}

//реда + колоната*ширината = мястото в едномерния масив
//3*1+2 = 5

// Raboti
int main()
{
	int width = 10, height = 10;
	
	srand((unsigned int)time((time_t*)NULL));

	int* res = generate(height, width);

	puts("");
	print_grid(res, width, height);

	return 0;
}
