#include "main.h"
#include "save.h"
#include "read.h"
#include "graphics.h"

void update(unsigned int selected, SDL_Renderer* rend) {
	print_menu(selected);
}

/*char* generate_string(unsigned int selected) {
	char* options[6] = { "Generate maze\n", "Read from file\n", "Save to file\n", "Solve manually\n", "Solve automatically\n", "Quit\n" };
	static char res_str[95];

	for (int i = 0; i < 6; i++) {
		if (i == selected)
			strcat(res_str, "> ");
		strcat(res_str, options[i]);
	}

	return res_str;
}*/

void print_menu(unsigned int selected) {
	char* options[6] = { "Generate maze", "Read from file", "Save to file", "Solve manually", "Solve automatically", "Quit" };
	system("cls");
	for (int i = 0; i < 6; i++) {
		if (i == selected)
			printf("> ");
		printf("%s\n", options[i]);
	}
	/* SDL_TTF - not working
	char* str = generate_string(selected);

	SDL_Surface* surface = TTF_RenderText_Solid(font, str, color);
	SDL_Texture* tex = SDL_CreateTextureFromSurface(rend, surface);
	int texW = 0, texH = 0;
	SDL_QueryTexture(tex, NULL, NULL, &texW, &texH);
	SDL_Rect dstrect = { 50, 50, texW, texH };

	SDL_RenderCopy(rend, tex, NULL, &dstrect);

	SDL_DestroyTexture(tex);
	SDL_FreeSurface(surface);*/
}

int main(int argc, char* argv[]) {
	
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		return -1;
	}

	//TTF_Init();

	SDL_Window* wind = SDL_CreateWindow("Maze explorer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIND_W, WIND_H, 0);
	if (!wind) {
		printf("Error creating window: %s\n", SDL_GetError());
		SDL_Quit();
		return 0;
	}

	SDL_Renderer* rend = SDL_CreateRenderer(wind, -1, SDL_RENDERER_ACCELERATED);
	if (!rend)
	{
		printf("Error creating renderer: %s\n", SDL_GetError());
		SDL_DestroyWindow(wind);
		SDL_Quit();
		return 0;
	}

	//TTF_Font* font = TTF_OpenFont("opensans.ttf", 25);
	//SDL_Color color = { 255, 255, 255 };
	print_menu(0);

	SDL_Event event;

	unsigned int selected = 0;
	bool running = true;
	struct maze_t* maze = malloc(sizeof *maze);

	while (running) {
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
				case SDL_QUIT:
					running = false;
					break;
				case SDL_KEYUP:
					switch (event.key.keysym.sym) {
						case SDLK_DOWN:
							if (selected < 5) {
								selected++;
								update(selected, rend);
							}
							break;
						case SDLK_UP:
							if (selected > 0) {
								selected--;
								update(selected, rend);
							}
							break;
						case SDLK_RETURN:
							switch (selected) {
							case 0:
								//generate maze func
								break;
							case 1:
								maze = read_file();
								draw_field(maze, rend);
								break;
							case 2:
								draw_field(maze, rend);
								save_to_file(maze);
								break;
							case 3:
								//solve manually func
								break;
							case 4:
								//solve automatically func
								break;
							case 5:
								running = false;
								break;
							}
							break;
					}
			}
			
		}
		SDL_RenderPresent(rend);
		SDL_Delay(1000 / 60);
		/* console menu system
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
		} while (true);*/
	}
	SDL_DestroyRenderer(rend);
	SDL_DestroyWindow(wind);
	//TTF_CloseFont(font);
	//TTF_Quit();
	SDL_Quit();

	return 0;
}
