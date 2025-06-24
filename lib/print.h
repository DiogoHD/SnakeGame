#ifndef PRINT_H
#define PRINT_H

#include "map.h"
#include "snake.h"
#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>

char* choose_char(int number, char skin);
char* choose_head(char skin);
int print_skins_menu();
int print_main_menu();
void print_game(map_t* map, snake_t* snake);

#endif