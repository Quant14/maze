#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "main.h"

#define CHARACTER_PATH "textures/character.png"
#define CHARACTER_TROPICAL_PATH "textures/character_tropical.png"
#define GROUND_PATH "textures/ground.png"
#define GROUND_TROPICAL_PATH "textures/ground_tropical.png"
#define WALL_PATH "textures/wall.png"
#define WALL_TROPICAL_PATH "textures/wall_tropical.png"

#define PIXELSIZE 16

void draw_default_field(struct maze_t* maze, SDL_Renderer* rend);

#endif