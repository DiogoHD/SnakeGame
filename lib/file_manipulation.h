#ifndef FILE_MANIPULATION_H
#define FILE_MANIPULATION_H

#include "snake.h"
#include "map.h"
#include "game_init.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

typedef struct{
    int points;
    struct tm date;
} rank_t;
// A struct tm é uma struct de time.h


void save_game(snake_t* snake, map_t* map);
map_t* load_game(snake_t* snake);

void order_leaderboard(rank_t leaderboard[], int size);
void load_leaderboard();
void add_to_leaderboard(int points);

#endif