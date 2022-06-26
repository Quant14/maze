#include "read.h"

struct maze_t* read_file() {
	char filename[100];
	char value = NULL;
	FILE* file;
	struct maze_t* maze = (struct maze_t*)malloc(sizeof * maze);
	if (maze == NULL) return NULL;

	int i = 0;

	printf("Enter file name: ");
	scanf("%s", filename);
	file = fopen(filename, "r");

	while (filename[0] == 0 || file == NULL) {
		printf("Invalid file name. Enter valid file name: ");
		scanf("%s", filename);
		file = fopen(filename, "r");
	}

	system("cls");
	print_menu(1);

	fscanf(file, "%d ", &maze->height);
	fscanf(file, "%d ", &maze->width);

	maze->field = malloc(sizeof(int) * maze->width * maze->height);
	if (maze->field == NULL) return NULL;

	while (value != EOF) {
		value = fgetc(file);
		maze->field[i] = value - '0';
		i++;
	}

	fclose(file);

	return maze;
}