#ifndef SAVE_H
#define SAVE_H

#include "main.h"
#include<string.h>

void save_to_file(struct maze_t* maze);
void write_file(char* name, struct maze_t* maze);

#endif