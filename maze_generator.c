#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

enum directions { N = 1, E, S, W };

struct cell
{
	int wall_direction;
	int visited;
	int data;
};

void shuffle_array(int* array, int size)
{
	for (int i = 0; i < (size - 1); i++)
	{
		int r = i + (rand() % (size - i));
		int temp = array[i];
		array[i] = array[r];
		array[r] = temp;
	}
}

struct cell** generate_maze(struct cell** grid, int height, int width)
{
	//struct cell** res = grid;
	//return res;



	return grid;
}

int main()
{
	int width = 4, height = 4;
	struct cell** grid = malloc(sizeof(struct cell) * width * height);

	srand((unsigned int)time((time_t*)NULL));

	//struct cell** res = generate_maze(grid, height, width);
	generate_maze(grid, height, width);

	return 0;
}
