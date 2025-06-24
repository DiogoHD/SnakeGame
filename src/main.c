#include "../lib/map.h"
#include "../lib/snake.h"
#include "../lib/game_logic.h"
#include "../lib/game_init.h"
#include "../lib/file_manipulation.h"
#include <stdio.h>
#include <ctype.h>          // permite o toupper()
#include <stdlib.h>
#include <stdbool.h>        // permite o bool (TRUE/FALSE)
#include <time.h>           // permite o time(NULL)
#include <ncursesw/ncurses.h>
#include <locale.h>         // Permite o setlocale(LC_ALL, "")

int main(){
    setlocale(LC_ALL, "");  // Ativa o suporte a UTF-8 (emojis,...)
    initscr();              // Inicializa a biblioteca ncurses e prepara o terminal
    cbreak();               // Modo linha-a-linha: permite capturar teclas imediatamente sem esperar pelo Enter
    noecho();               // Não mostra no ecrã as teclas que o utilizador pressiona
    curs_set(FALSE);        // Não mostra o cursor no ecrã
    timeout(-1);            // Espera até que uma tecla seja digitada
    keypad(stdscr, TRUE);   // Permite usar teclas especiais (setas, F1, etc.)

    // Inicia o gerador de números aleatórios no início do programa
    srand(time(NULL));

    // Declara o mapa e a cobra
    map_t* map;
    snake_t snake;

    // Tela inicial
    char option;
    char skin = '0';
    char* skins[] = {"SNAKE", "DRAGON", "CAT", "RABBIT", "TIGER", "BEAR", "MONKEY", "FROG", "MOUSE"};
    do {
        clear();    // Limpa a tela do ncurses
        // Tela Inicial
        char* array[] = {"NEW GAME", "LOAD GAME", "SKINS", "LEADERBOARD"};
        int len = sizeof(array)/sizeof(array[0]);
        printw("JOGO DA COBRA\n");
        for (int i=0; i<len; i++){
            printw("%d - %s\n", i+1, array[i]);
        }
        refresh();  // Atualiza a tela do ncurses

        option = getch();   // Recebe um caracter do input
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
                    clear();    // Limpa a tela do ncurses
                    // Tela das Skins
                    printw("SKINS\n");
                    int len = sizeof(skins)/sizeof(skins[0]);
                    for (int i=0; i<len; i++){
                        printw("%d - %s\n", i+1, skins[i]);
                    }
                    refresh();  // Atualiza a tela do ncurses

                    skin = getch();     // Recebe um caracter do input;
                } while (skin < '1'&& skin > '8');
                break;
            case '4':
                load_leaderboard();
                getch();
                break;
            default:
                printf("Please choose a valid option.\n");
        }
    } while (option != '1' && option != '2');
    if (skin != '0'){
        map->skin = skin;
    }
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
    endwin();  // termina ncurses
    return 0;
}