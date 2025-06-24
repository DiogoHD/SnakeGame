#include "../lib/map.h"
#include "../lib/snake.h"
#include "../lib/game_logic.h"
#include "../lib/game_init.h"
#include "../lib/save.h"
#include "../lib/leaderboard.h"
#include <stdio.h>
#include <ctype.h>          // permite o toupper()
#include <stdlib.h>
#include <stdbool.h>        // permite o bool (TRUE/FALSE)
#include <time.h>           // permite o time(NULL) and localtime
#include <ncursesw/ncurses.h>
#include <locale.h>         // Permite o setlocale(LC_ALL, "")

int main(){
    // Initializing ncurses
    setlocale(LC_ALL, "");  // Ativa o suporte a UTF-8 (emojis,...)
    initscr();              // Inicializa a biblioteca ncurses e prepara o terminal
    cbreak();               // Modo linha-a-linha: permite capturar teclas imediatamente sem esperar pelo Enter
    noecho();               // Não mostra no ecrã as teclas que o utilizador pressiona
    curs_set(FALSE);        // Não mostra o cursor no ecrã
    timeout(-1);            // Espera até que uma tecla seja digitada
    keypad(stdscr, TRUE);   // Permite usar teclas especiais (setas, F1, etc.)

    // Inicia o gerador de números aleatórios no início do programa
    srand(time(NULL));

    // Initializing and declaring variables and arrays
    map_t* map;
    snake_t snake;
    bool playing = true;
    char option;
    char skin = '0';

    while (playing){

        // Inicial Menu
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
                    } while (skin < '1' || skin > '9');
                    break;
                case '4':
                    load_leaderboard();
                    break;
                case '5':
                    playing = false;
                    break;
            }
        } while (option != '1' && option != '2' && option != '5');

        // If the user choose to exit, the program ends
        if (!playing) break;

        // If the user chooses a skin
        if (skin != '0') map->skin = skin;

        print_game(map, &snake);

        int input = 1;      // Declara como int para permitir KEY_ARROW
        int last_move = 1;
        bool game_lost = false;
        timeout(250);        // Espera 0.25 segundos por uma tecla

        while (input != '0' && !game_lost){
            input = getch();
            if (input == ERR){
                input = last_move;
            }
            game_lost = move_snake(&snake, map, input, &last_move);
            print_game(map, &snake);

            // Updating the leaderboard
            if (game_lost){
                add_to_leaderboard(map->points);
            }
        }

        timeout(-1);        // Espera indefenidamente por uma tecla
        if (game_lost){
            printw("A tua cobra bateu! Perdeste o jogo!\n");
        } else {
            printw("Jogo salvo!\n");
        }
        refresh();
        printw("Pressiona qualquer tecla para sair...\n");
        refresh();

        save_game(&snake, map);

        getch();   // espera por tecla antes de fechar
    }

    endwin();  // termina ncurses
    return 0;
}