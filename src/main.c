#include "../lib/game_structs.h"
#include "../lib/game_logic.h"
#include "../lib/game_init.h"
#include "../lib/save.h"
#include "../lib/leaderboard.h"
#include <stdio.h>
#include <ctype.h>          // Allows toupper()
#include <stdlib.h>
#include <stdbool.h>        // Allows bool (true/false)
#include <time.h>           // Allows time(NULL) and localtime
#include <ncursesw/ncurses.h>
#include <locale.h>         // Allows setlocale(LC_ALL, "")

int main(){
    // Initializing ncurses
    setlocale(LC_ALL, "");  // Allows UTF-8 support (emojis,...)
    initscr();              // Inicializes the ncurses screen
    cbreak();               // Mode line by line: allows the keys to be captured witouth enter
    noecho();               // Doesn't show the keys that the user presses on the screen
    curs_set(FALSE);        // Doesn't show the cursor on the screen
    timeout(-1);            // Waits until a key is pressed
    keypad(stdscr, TRUE);   // Allow the use of special keys (arrows, F1, etc.)

    srand(time(NULL));      // Inicalizes the random number generator

    // Initializing and declaring variables and arrays
    map_t* map;
    snake_t snake;
    bool playing = true;
    char option;
    Skin skin = INVALID;

    while (playing){

        // Main Menu
        do {
            option = print_main_menu();
            switch (option){
                case '1':
                    map = create_map(12, 22);
                    start_game(map);
                    create_snake(&snake, map);
                    break; 
                case '2':
                    map = load_game(&snake);
                    start_game(map);
                    break;
                case '3':
                    do {
                        skin = print_skins_menu();
                    } while (skin == INVALID);
                    break;
                case '4':
                    load_leaderboard();
                    break;
                case '5':
                    playing = false;
                    break;
            }
        } while (option != '1' && option != '2' && option != '5');

        
        if (!playing) break;                // If the user choose to exit, the program ends
        if (skin != '0') map->skin = skin;  // If the user chooses a skin

        print_game(map, &snake);

        int input = 1;      // This is declared as an int to allow KEY_ARROW
        int last_move = 1;
        bool game_lost = false;
        timeout(250);        // Waits 0.25 seconds for a key

        // Gameplay
        while (input != '0' && !game_lost){
            input = getch();
            if (input == ERR) input = last_move;                // If there's no input, the snake keeps going
            game_lost = move_snake(&snake, map, input, &last_move);
            print_game(map, &snake);

            if (game_lost) update_leaderboard(map->points);     // Updates the leaderboard
        }

        print_end_screen(map, &snake, game_lost);       // Prints end screen
    }

    endwin();  // Ends ncurses
    return 0;
}