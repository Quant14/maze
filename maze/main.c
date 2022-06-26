#include "main.h"
#include "save.h"
#include "read.h"
#include "graphics.h"
#include "maze_generator.h"
#include "frenski.h"
#include "solve.h"

struct maze_t* copy_maze(struct maze_t* maze) {
	struct maze_t* res = malloc(sizeof * res);
	res->field = malloc(sizeof(int) * maze->height * maze->width);

	res->height = maze->height;
	res->width = maze->width;

	for (int i = 0; i < maze->height * maze->width; i++)
	{
		res->field[i] = maze->field[i];
	}

	return res;
}

void print_menu(unsigned int selected) {
	char* options[8] = { "Generate maze", "Read from file", "Save to file", "Solve manually", "Solve with A*", "Solve with wall hugging", "Cycle themes", "Quit"};
	system("cls");
	for (int i = 0; i < 8; i++) {
		if (i == selected)
			printf("> ");
		printf("%s\n", options[i]);
	}
}

int main(int argc, char* argv[]) {
	
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		return -1;
	}

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

	print_menu(0);

	SDL_Event event;

	unsigned int selected = 0;
	bool running = true;
	int theme = 0;
	bool solved = 0;
	bool playing = 0;
	struct maze_t* maze = malloc(sizeof *maze);
	maze = 0;

	int frenski_pos = 0;
	int old_pos = 0;
	SDL_Rect frenski = { 0, 0, PIXELSIZE, PIXELSIZE };

	while (running) {
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
				case SDL_QUIT:
					running = false;
					break;
				case SDL_KEYUP:
					switch (event.key.keysym.sym) {
						case SDLK_DOWN:
							if (selected < 7) {
								selected++;
								print_menu(selected);
							}
							break;
						case SDLK_UP:
							if (selected > 0) {
								selected--;
								print_menu(selected);
							}
							break;
						case SDLK_RETURN:
							switch (selected) {
							case 0:
								maze = generate();
								frenski.x = frenski.y = 0;
								frenski.h = frenski.w = PIXELSIZE * (WIND_W / (maze->width * PIXELSIZE));
								solved = 0;
								draw_field(maze, rend, theme, solved);
								break;
							case 1:
								maze = read_file();
								frenski.h = frenski.w = PIXELSIZE * (WIND_W / (maze->width * PIXELSIZE));
								solved = 0;
								draw_field(maze, rend, theme, solved);
								break;
							case 2:
								solved = 0;
								draw_field(maze, rend, theme, solved);
								save_to_file(maze);
								break;
							case 3:
								if (maze) {
									solved = 0;
									frenski.x = frenski.y = 0;
									draw_field(maze, rend, theme, solved);
									draw_character(rend, frenski, theme);
									playing = 1;
								}
								break;
							case 4:
								if (maze) {
									solved = 1;
									struct maze_t* copy = copy_maze(maze);
									draw_field(copy, rend, theme, solved);
									SDL_RenderPresent(rend);
									find_shortest_path_a_star(copy, rend, theme, 1, &frenski);
									draw_field(copy, rend, theme, solved);
								}
								break;
							case 5: 
								if (maze) {
									solved = 1;
									struct maze_t* copy = copy_maze(maze);
									solve_maze(copy, rend, theme, &frenski);
									draw_field(copy, rend, theme, solved);
								}
								break;
							case 6:
								theme++;
								if (theme > 2) theme = 0;
								if (maze) {
									draw_field(maze, rend, theme, solved);
									if (playing)
										draw_character(rend, frenski, theme);
								}
								break;
							case 7:
								running = false;
								break;
							}
							break;
						case SDLK_w:
							if (playing) {
								old_pos = frenski_pos;
								frenski_pos = move(maze, frenski_pos, 3);
								if (frenski_pos != old_pos) frenski.y -= frenski.h;
								draw_field(maze, rend, theme, 0);
								draw_character(rend, frenski, theme);
							}
							break;
						case SDLK_s:
							if (playing) {
								old_pos = frenski_pos;
								frenski_pos = move(maze, frenski_pos, 1);
								if (frenski_pos != old_pos) frenski.y += frenski.h;
								draw_field(maze, rend, theme, 0);
								draw_character(rend, frenski, theme);
							}
							break;
						case SDLK_d:
							if (playing) {
								old_pos = frenski_pos;
								frenski_pos = move(maze, frenski_pos, 0);
								if (frenski_pos != old_pos) frenski.x += frenski.w;
								draw_field(maze, rend, theme, 0);
								draw_character(rend, frenski, theme);
							}
							break;
						case SDLK_a:
							if (playing) {
								old_pos = frenski_pos;
								frenski_pos = move(maze, frenski_pos, 2);
								if (frenski_pos != old_pos) frenski.x -= frenski.w;
								draw_field(maze, rend, theme, 0);
								draw_character(rend, frenski, theme);
							}
							break;
					}
			}
		}
		SDL_RenderPresent(rend);
		SDL_Delay(50);
	}
	SDL_DestroyRenderer(rend);
	SDL_DestroyWindow(wind);
	SDL_Quit();

	return 0;
}