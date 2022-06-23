#include "main.h"
#include "save.h"

int main() {
	char* options[6] = { "Generate maze", "Read from file", "Save to file", "Solve manually", "Solve automatically", "Quit"};
	char input = 0;
	unsigned int selected = 0;
	bool run = true;
	struct maze_t* maze = malloc(sizeof *maze);

	while (run) {
		do {
			system("cls");
			for (int i = 0; i < 6; i++) {
				if (i == selected)
					printf("> ");
				printf("%s\n", options[i]);
			}
			scanf("%c", &input);
			if (input == 'e') //enter
				break;
			if (input == 'w' && selected > 0)
				selected--;
			else if (input == 's' && selected < 5)
				selected++;
		} while (true);

		switch (selected) {
		case 0:
			//generate maze func
			break;
		case 1:
			//read file func
			break;
		case 2:
			save_to_file(maze);
			break;
		case 3:
			//solve manually func
			break;
		case 4:
			//solve automatically func
			break;
		case 5:
			run = false;
			break;
		}
	}

	return 0;
}
