#include "graphics.h"

void draw_field(struct maze_t* maze, SDL_Renderer* rend, int theme, bool solved) {
	int w, h;
	SDL_Texture* ground_tex = NULL;
	SDL_Texture* wall_tex = NULL;
	SDL_Texture* solved_tex = NULL;

	if (theme == 0) {
		if (solved)
			solved_tex = IMG_LoadTexture(rend, SOLVED_PATH);
		ground_tex = IMG_LoadTexture(rend, GROUND_PATH);
		wall_tex = IMG_LoadTexture(rend, WALL_PATH);
	}
	else if (theme == 1) {
		if (solved)
			solved_tex = IMG_LoadTexture(rend, SOLVED_TROPICAL_PATH);
		ground_tex = IMG_LoadTexture(rend, GROUND_TROPICAL_PATH);
		wall_tex = IMG_LoadTexture(rend, WALL_TROPICAL_PATH);
	}
	else {
		if (solved)
			solved_tex = IMG_LoadTexture(rend, SOLVED_COWBOY_PATH);
		ground_tex = IMG_LoadTexture(rend, GROUND_COWBOY_PATH);
		wall_tex = IMG_LoadTexture(rend, WALL_COWBOY_PATH);
	}

	SDL_QueryTexture(ground_tex, NULL, NULL, &w, &h);
	SDL_QueryTexture(wall_tex, NULL, NULL, &w, &h);
	SDL_QueryTexture(solved_tex, NULL, NULL, &w, &h);

	float posX = 0, posY = 0;
	int pixel_size = PIXELSIZE * (WIND_W / (maze->width * PIXELSIZE));
	SDL_Rect rect = { (int)posX, (int)posY, pixel_size, pixel_size };

	for (int i = 0; i < maze->height; i++) {
		for (int j = 0; j < maze->width; j++) {
			if (maze->field[i * maze->width + j] == 1) {
				SDL_RenderCopy(rend, wall_tex, NULL, &rect);
			}
			else {
				SDL_RenderCopy(rend, ground_tex, NULL, &rect);
				if (maze->field[i * maze->width + j] == 6 && solved)
					SDL_RenderCopy(rend, solved_tex, NULL, &rect);
			}
			rect.x += rect.w;
		}
		rect.x = posX;
		rect.y += rect.h;
	}

	SDL_DestroyTexture(ground_tex);
	SDL_DestroyTexture(wall_tex);
	SDL_DestroyTexture(solved_tex);
}

void draw_character(SDL_Renderer* rend, SDL_Rect character, int theme) {
	int w = 0, h = 0;
	SDL_Texture* character_tex = NULL;

	if (theme == 0)
		character_tex = IMG_LoadTexture(rend, CHARACTER_PATH);
	else if (theme == 1)
		character_tex = IMG_LoadTexture(rend, CHARACTER_TROPICAL_PATH);
	else
		character_tex = IMG_LoadTexture(rend, CHARACTER_COWBOY_PATH);

	SDL_QueryTexture(character_tex, NULL, NULL, &w, &h);

	SDL_RenderCopy(rend, character_tex, NULL, &character);

	SDL_DestroyTexture(character_tex);
}