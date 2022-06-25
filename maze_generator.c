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
void print_grid(struct maze_t grid)
{
	printf("\t|");
	for (int i = grid.width * 2; i > 0; i--)
		printf("-");
	printf("|\n\t|");
	int index = 0;
	int sbor = grid.width * grid.height;
	for (int i = 0; i < sbor; i++)
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

	//обикалям всичко около точката и ако има отворена клетка значи не може тази точка да е от лабиринта
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
int* generate_maze1(struct maze_t grid, int x, int y, int prev_x, int prev_y)
{
	grid.field[x + (y * grid.width)] = 0;
	//puts("");
	//puts("");
	//print_grid(grid);
	if ((x + y + 2) == (grid.height + grid.width))
		return grid.field;
	int* n_directions = find_neighbours(grid, x, y); // neighbours directions
	int neighbours = n_directions[0];
	if (neighbours == 0)
		return grid.field;
	for (int i = 0; i < neighbours; i++)
	{
		// ignore n_directions[0] - this is the count of the neighbours
		int res = rand() % neighbours;
		res++;
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
			n_directions = find_neighbours(grid, x, y);
			//if (grid.field[(grid.width * grid.height) - 1] == 0)
				//return grid.field;
		}
	}
	return grid.field;
}

// Raboti
struct maze_t generate(int height, int width)
{
	struct maze_t grid;
	grid.field = malloc(sizeof(int) * width * height);
	grid.height = height, grid.width = width;
	for (int i = 0; i < (width * height); i++)
		grid.field[i] = 1;
	print_grid2(grid); // optional
	int* res = generate_maze1(grid, 0, 0, 0, 0);
	grid.field = res;
	//if (grid.field[(width * height) - 1] == 1)
		//grid.field[(width * height) - 1] = 0;
	return grid;
}

//реда + колоната*ширината = мястото в едномерния масив
//3*1+2 = 5

// Raboti
int main()
{
	int width = 40, height = 30, seed = 15;

	if (seed == -1) // we do not have seed so do not need it
		srand((unsigned int)time((time_t*)NULL));
	else
		srand(seed);

	struct maze_t res = generate(height, width);

	puts("");
	puts("");
	puts("");
	print_grid(res);

	puts("");
	puts("");
	print_grid2(res);

	return 0;
}
