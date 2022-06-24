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

// Raboti
// dobavi cqlostnite proverki na edna kletka !!!!!!!!!!!!!!!!
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
		if ((grid.field[x + ((y + 1) * grid.width)] == 0) && (x != prev_x) && ((y + 1) != prev_y))
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
int* find_neighbours(struct maze_t grid, int x, int y, int prev_x, int prev_y, int neighbours)
{
	int* res = malloc(sizeof(int) * neighbours);
	if (!res) return 0;
	int index = 0;

	//обикалям всичко около точката и ако има отворена клетка значи не може тази точка да е от лабиринта
	//освен само предишната клетка, която е от пътя

	if (x - 1 >= 0)
	{
		if (check(grid, x - 1, y, prev_x, prev_y) == 1)
			res[index++] = 0; // lqvo - 0
	}
	if (x + 1 < grid.width)
	{
		if (check(grid, x + 1, y, prev_x, prev_y) == 1)
			res[index++] = 2; // dqsno - 2
	}
	if (y - 1 >= 0)
	{
		if (check(grid, x, y - 1, prev_x, prev_y) == 1)
			res[index++] = 1; // gore - 1
	}
	if (y + 1 < grid.height)
	{
		if (check(grid, x, y + 1, prev_x, prev_y) == 1)
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
int* generate_maze1(struct maze_t grid, int x, int y, int prev_x, int prev_y)
{
	grid.field[x + (y * grid.width)] = 0;
	if ((x + y + 2) == (grid.height + grid.width))
		return grid.field;
	int neighbours = find_neighbours_count(x, y, grid.height, grid.width);
	if (neighbours == 0)
		return grid.field;
	int* n_directions = find_neighbours(grid, x, y, prev_x, prev_y, neighbours); // neighbours directions
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
			grid.field = generate_maze1(grid, curr_x, curr_y, x, y);
			//return grid;
			n_directions[res] = -1;
			n_directions = find_neighbours(grid, x, y, prev_x, prev_y, neighbours);
			//if (grid.field[(grid.width * grid.height) - 1] == 0)
				//return grid.field;
		}
	}
	return grid.field;
}

// Raboti pravilno veche
void print_grid(struct maze_t grid)
{
	printf("\t|");
	for (int i = grid.width; i > 0; i--)
		printf("-");
	printf("|\n\t|");
	int index = 0;
	int sbor = grid.width * grid.height;
	for (int i = 0; i < sbor; i++)
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
struct maze_t generate(int height, int width)
{
	struct maze_t grid;
	grid.field = malloc(sizeof(int) * width * height);
	grid.height = height, grid.width = width;
	for (int i = 0; i < (width * height); i++)
		grid.field[i] = 1;
	print_grid(grid);
	grid.field[(height * width) - 1] = 0;
	//napravi vinagi poslednata kletka da e prazna, za da moje da se nameri put do neq!!!!!!!!!!!!!!
	int* res = generate_maze1(grid, 0, 0, 0, 0);
	grid.field = res;
	return grid;
}

//реда + колоната*ширината = мястото в едномерния масив
//3*1+2 = 5

// Raboti
int main()
{
	int width = 4, height = 4, seed = 3;

	srand(seed); //(unsigned int)time((time_t*)NULL)

	struct maze_t res = generate(height, width);

	puts("");
	puts("");
	puts("");
	print_grid(res);

	return 0;
}
