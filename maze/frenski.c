#include "frenski.h"

int move(struct maze_t* maze, int pos, int direction) {
	int movements[4] = { 1,maze->width,-1,-maze->width };
	
	if (!validate_move(pos + movements[direction], pos, maze)) return pos;

	return pos + movements[direction];
}

int draw_frenski(struct maze_t* maze, SDL_Rect* character, SDL_Renderer* rend, int theme, int frenski_pos) {
	if (frenski_pos == -1)
		frenski_pos = get_player_pos(maze);
	character->x = frenski_pos % maze->width * character->w;
	character->y = frenski_pos / maze->width * character->h;
	draw_character(rend, *character, theme);
}