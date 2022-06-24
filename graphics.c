#include "graphics.h"

void draw_default_field(struct maze_t* maze, SDL_Renderer* rend) {
	int w, h;
	//SDL_Texture* character_tex = IMG_LoadTexture(rend, CHARACTER_PATH);
	//SDL_QueryTexture(character_tex, NULL, NULL, &w, &h);
	//SDL_Texture* character_tropical_tex = IMG_LoadTexture(rend, CHARACTER_TROPICAL_PATH);
	//SDL_QueryTexture(character_tropical_tex, NULL, NULL, &w, &h);
	SDL_Texture* ground_tex = IMG_LoadTexture(rend, GROUND_PATH);
	SDL_QueryTexture(ground_tex, NULL, NULL, &w, &h);
	//SDL_Texture* ground_tropical_tex = IMG_LoadTexture(rend, GROUND_TROPICAL_PATH);
	//SDL_QueryTexture(ground_tropical_tex, NULL, NULL, &w, &h);
	SDL_Texture* wall_tex = IMG_LoadTexture(rend, WALL_PATH);
	SDL_QueryTexture(wall_tex, NULL, NULL, &w, &h);
	//SDL_Texture* wall_tropical_tex = IMG_LoadTexture(rend, WALL_TROPICAL_PATH);
	//SDL_QueryTexture(wall_tropical_tex, NULL, NULL, &w, &h);

	float posX = 300, posY = 300;
	SDL_Rect rect = { (int)posX, (int)posY, PIXELSIZE, PIXELSIZE };

	for (int i = 0; i < maze->height; i++) {
		SDL_PumpEvents(); //potentially useless
		for (int j = 0; j < maze->width; j++) {
			if (maze->field[i * j + j] == 1) {
				SDL_RenderCopy(rend, wall_tex, NULL, &rect);
			}
			else {
				SDL_RenderCopy(rend, ground_tex, NULL, &rect);
			}
			posX += PIXELSIZE;
		}
		posX = 0;
		posY += PIXELSIZE;
	}

	SDL_DestroyTexture(ground_tex);
	SDL_DestroyTexture(wall_tex);
}