#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "main.h"

#define CHARACTER_PATH "textures/character.png"
#define CHARACTER_TROPICAL_PATH "textures/character_tropical.png"
#define CHARACTER_COWBOY_PATH "textures/character_cowboy.png"
#define GROUND_PATH "textures/ground.png"
#define GROUND_TROPICAL_PATH "textures/ground_tropical.png"
#define GROUND_COWBOY_PATH "textures/ground_cowboy.png"
#define WALL_PATH "textures/wall.png"
#define WALL_TROPICAL_PATH "textures/wall_tropical.png"
#define WALL_COWBOY_PATH "textures/wall_cowboy.png"
#define SOLVED_PATH "textures/solved.png"
#define SOLVED_TROPICAL_PATH "textures/solved_tropical.png"
#define SOLVED_COWBOY_PATH "textures/solved_cowboy.png"

#define DRAW_MAZE maze->field[get_player_pos(v->board)] = 6;\
draw_field(maze, rend, theme, 1);\
draw_frenski(v->board, character, rend, theme, -1);\
SDL_RenderPresent(rend);\
SDL_Delay(300);\

#define PIXELSIZE 18

void draw_field(struct maze_t* maze, SDL_Renderer* rend, int theme, bool solved);
void draw_character(SDL_Renderer* rend, SDL_Rect character, int theme);

#endif