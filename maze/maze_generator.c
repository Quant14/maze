#define _CRT_SECURE_NO_WARNINGS

#include "maze_generator.h"
#include "graph.h"
#include "list.h"
#include "priority_list.h"
#include "set.h"
#include "solve.h"

// Print grid with lines
void print_grid(struct maze_t* grid)
{
	printf("\t|");
	for (int i = grid->width * 2; i > 0; i--)
		printf("-");
	printf("|\n\t|");

	int index = 0;
	int multiplicated = grid->width * grid->height;
	for (int i = 0; i < multiplicated; i++)
	{
		if (grid->field[i] == 1)
			printf("#|");
		else
			printf(" |");
		index++;
		if (index == grid->width)
		{
			printf("|\n\t|");
			index = 0;
		}
	}

	for (int i = grid->width * 2; i > 0; i--)
		printf("-");
	printf("|");
}

// Print grid
void print_grid2(struct maze_t* grid)
{
	printf("\t|");
	for (int i = grid->width; i > 0; i--)
		printf("-");
	printf("|\n\t|");

	int index = 0;
	int multiplicated = grid->width * grid->height;
	for (int i = 0; i < multiplicated; i++)
	{
		if (grid->field[i] == 1)
			printf("#");
		else
			printf(" ");
		index++;
		if (index == grid->width)
		{
			printf("|\n\t|");
			index = 0;
		}
	}

	for (int i = grid->width; i > 0; i--)
		printf("-");
	printf("|");
}

// Make checks if one neighbour can be neighbours in our grid
int check(struct maze_t* grid, int x, int y, int prev_x, int prev_y)
{
	if (grid->field[x + (y * grid->width)] == 0)
		return 0;
	if (prev_x == x && prev_y == y)
		return 0;

	if (y - 1 >= 0)
	{
		if ((grid->field[x + ((y - 1) * grid->width)] == 0) && (x != prev_x) && ((y - 1) != prev_y))
			return 0;
	}
	if (y + 1 < grid->height)
	{
		if ((grid->field[x + ((y + 1) * grid->width)] == 0) && (x != prev_x) && ((y + 1) != prev_y)) //  && (((grid.width * grid.width) - 1) != ((y - 1) * x))
			return 0;
	}
	if (x + 1 < grid->width)
	{
		if ((grid->field[x + 1 + (y * grid->width)] == 0) && ((x + 1) != prev_x) && (y != prev_y))
			return 0;
	}
	if (x - 1 >= 0)
	{
		if ((grid->field[x - 1 + (y * grid->width)] == 0) && (((x - 1) != prev_x) && (y != prev_y)))
			return 0;
	}
	return 1;
}

// Find all the neighbours of a cell
int* find_neighbours(struct maze_t* grid, int x, int y)
{
	int* res = malloc(sizeof(int) * 5);
	if (!res) return 0;
	int index = 1, cnt = 0;

	//обикалям всичко около текущата клетка и ако има отворена клетка значи не може тази точка да е от лабиринта
	//освен само предишната клетка, която е от пътя

	if (x - 1 >= 0)
	{
		if (check(grid, x - 1, y, x, y) == 1) // vmesto x i y -> prev_x, prev_y
			res[index++] = 0, cnt++; // left - 0
	}
	if (x + 1 < grid->width)
	{
		if (check(grid, x + 1, y, x, y) == 1)
			res[index++] = 2, cnt++; // right - 2
	}
	if (y - 1 >= 0)
	{
		if (check(grid, x, y - 1, x, y) == 1)
			res[index++] = 1, cnt++; // up - 1
	}
	if (y + 1 < grid->height)
	{
		if (check(grid, x, y + 1, x, y) == 1)
			res[index++] = 3, cnt++; // down - 3
	}

	// Fill the space in array with -1
	res[0] = cnt;
	if (index < 5)
		for (; index < 5; index++)
			res[index] = -1;
	return res;
}

// Generate the maze recursively
struct maze_t* generate_maze(struct maze_t* grid, int x, int y, int prev_x, int prev_y)
{
	grid->field[x + (y * grid->width)] = 0;

	// Check if we are at the end of the maze
	if ((x + y + 2) == (grid->height + grid->width))
		return grid;

	int* neigh_directions = find_neighbours(grid, x, y); // neighbours directions

	int neighbours_cnt = neigh_directions[0];
	if (neighbours_cnt == 0)
		return grid;
	
	int rnd = 0;

	for (int i = 0; i < neighbours_cnt; i++)
	{
		// Ignore neigh_directions[0] - this is the count of the neighbours
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

			grid = generate_maze(grid, curr_x, curr_y, x, y);

			// Find new valid neighbours
			neigh_directions[rnd] = -1;
			neigh_directions = find_neighbours(grid, x, y);
		}
	}
	return grid;
}

// Function to call recursive generating the maze

struct maze_t* generate()
{
	int height, width, seed, from_scanf = 0;

	do {
		printf("Enter valid height, width and seed.\n");
		from_scanf = scanf("%d %d %d", &height, &width, &seed);
	} while (height < 3 || width < 3);

	system("cls");
	print_menu(0);

	// We do not have seed so we do not need it
	if (seed == -1)
		srand((unsigned int)time((time_t*)NULL));
	else
		srand(seed);

	struct maze_t* grid = malloc(sizeof(struct maze_t));
	if (!grid) return 0;
	grid->field = malloc(sizeof(int) * width * height);
	if (!grid->field) return 0;
	grid->height = height, grid->width = width;

	do
	{
		for (int i = 0; i < (width * height); i++)
			grid->field[i] = 1;

		// Generate the maze
		grid = generate_maze(grid, 0, 0, 0, 0);
		grid->field[0] = 2;

		if (grid->field[(width * height) - 1] == 1)
			grid->field[(width * height) - 1] = 0;

		// Check if we can solve the maze
		if (find_shortest_path_a_star(grid, 0, 0, 0, 0) != 0)
			break;
		else
			if (seed != -1)
				seed++;
	} while (1);

	return grid;
}
