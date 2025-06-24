#ifndef LEADERBOARD_H
#define LEADERBOARD_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <ncursesw/ncurses.h>

// A struct tm é uma struct de time.h
typedef struct{
    int points;
    struct tm date;
} rank_t;

void order_leaderboard(rank_t leaderboard[], int size);
void load_leaderboard();
void add_to_leaderboard(int points);

#endif