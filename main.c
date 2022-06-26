#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "maze_generator.h"

//реда + колоната*ширината = мястото в едномерния масив
//2 + 1*3 = 5

int main()
{
	struct maze_t* res = generate();

	puts("");
	puts("");
	puts("");
	print_grid(res);

	puts("");
	puts("");
	print_grid2(res);

	return 0;
}