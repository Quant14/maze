#ifndef MAIN_H
#define MAIN_H

#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

#define SDL_MAIN_HANDLED
#include<SDL.h>
#include<SDL_image.h>

//#include<SDL_ttf.h>

#define WIND_W 1280
#define WIND_H 720

struct maze_t {
	int* field;
	int width;
	int height;
};

void print_menu(unsigned int selected);

#endif
