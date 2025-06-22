#ifndef GAME_INIT_H
#define GAME_INIT_H

#include "snake.h"
#include "map.h"
#include "game_logic.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

map_t* create_map(int lines, int columns);
void generate_snake(map_t* map);
void generate_apple(map_t* map);
void create_snake(snake_t* snake, map_t* map);
void start_game(map_t* map);

#endif