#include "save.h"

void save_to_file(struct maze_t* maze) {
	char filename[100];
	filename[0] = 0;

	do {
		scanf("%s", filename);
	} while (filename[0] == 0);

	write_file(filename, maze);
}

void write_file(char* name, struct maze_t* maze) {
	FILE* file;
	char* filename = malloc(strlen(name) + 4);
	if (filename == NULL) {
		printf("Failed to create file.");
		return;
	}

	strcpy(filename, name);
	strcat(filename, ".txt");

	file = fopen(filename, "w+");
	fprintf(file, "%d %d\n", maze->height, maze->width);

	for (int h = 0, i = 0; h < maze->height; h++) {
		for (int w = 0; w < maze->width; w++, i++) {
			fprintf(file, "%d ", maze->field[w * h + w]);
		}
	}

	fclose(file);
}