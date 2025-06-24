#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "game_structs.h"
#include "print.h"
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdbool.h>

int random_number(int min, int max);
bool move_snake(snake_t* snake, map_t* map, int input, int *last_move);

#endif