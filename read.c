#include "read.h"

struct maze_t* read_file() {
	char filename[100];
	FILE* file;
	struct maze_t* maze = (struct maze_t*)malloc(sizeof * maze);
	if (maze == NULL)
		return NULL;
	int i = 0;

	printf("Enter file name: ");
	scanf("%s", filename);
	file = fopen(filename, "r");

	while (filename[0] == 0 || file == NULL) {
		printf("Invalid file name. Enter valid file name: ");
		scanf("%s", filename);
		file = fopen(filename, "r");
	}

	fscanf(file, "%d ", &maze->height);
	fscanf(file, "%d ", &maze->width);

	while (file) {
		fscanf(file, "%d ", &maze->field[i]);
		i++;
	}

	return maze;
}