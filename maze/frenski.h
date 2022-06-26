#pragma once
#include "main.h"
#include "solve.h"

int move(struct maze_t* maze, int pos, int direction);
int draw_frenski(struct maze_t* maze, SDL_Rect* character, SDL_Renderer* rend, int theme, int frenski_pos);