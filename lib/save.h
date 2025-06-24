#ifndef SAVE_H
#define SAVE_H

#include "game_structs.h"
#include "game_init.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void save_game(snake_t* snake, map_t* map);
map_t* load_game(snake_t* snake);

#endif