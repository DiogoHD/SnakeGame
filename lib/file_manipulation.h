#ifndef FILE_MANIPULATION_H
#define FILE_MANIPULATION_H

#include "snake.h"
#include "map.h"
#include "game_init.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct{
    int day, month, year;
} date_t;

void save_game(snake_t* snake, map_t* map);
map_t* load_game(snake_t* snake);

#endif