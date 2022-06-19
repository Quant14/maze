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

struct cell* find_neighbours(struct cell** grid, int start_x, int start_y, int height, int width)
{
	struct cell* res = malloc(sizeof(struct cell) * 4);
	if (!res) return 0;
	int index = 0;
	if (start_x - 1 >= 0)
	{
		res[index] = grid[start_x - 1][start_y];
		index++;
	}
	if (start_x + 1 < width)
	{
		res[index] = grid[start_x + 1][start_y];
		index++;
	}
	if (start_y - 1 >= 0)
	{
		res[index] = grid[start_x][start_y - 1];
		index++;
	}
	if (start_y + 1 < height)
	{
		res[index] = grid[start_x][start_y + 1];
		index++;
	}
	return res;
}

struct cell** generate_maze(struct cell** grid, int height, int width, int start_x, int start_y)
{
	//struct cell** res = grid;
	//return res;

	struct cell* neighbours = find_neighbours(grid, start_x, start_y, height, width);
	for (int i = 0; neighbours[i].data == 0; i++)
	{
		//???
		// Проверявам всеки един от съседите на текущата клетка.
		// Проверявам всеки от съседите дали е видян преди това.
		// Когато съседът не е видян по-рано чрез рекурсия викам отново тази функция
		// И това се повтаря докато не стигнем някакво дъно - видян съсед или границите на лабиринта
		// Когато нямам повече съседи се връщам назад и довършвам със същите неща останалите съседи
		// Така се гарантира, че всички клетки от лабиринта ще са видяни
		// И когато една клетка се доближи до друга видяна клетка се поставя стена
		// Така се образува лабиринта
		// Това е и идеята по образуването на лабиринта
		// Поради изключително малкото време между НВО-то и 19 юни не съм успял да довърша този алогритъм
		// 
	}
	return grid;
}

int main()
{
	int width = 4, height = 4;
	struct cell** grid = malloc(sizeof(struct cell) * width * height);

	srand((unsigned int)time((time_t*)NULL));

	//struct cell** res = generate_maze(grid, height, width);
	generate_maze(grid, height, width, 0, 0);

	return 0;
}
