#include "../lib/print.h"

char* choose_char(int number, char skin){
    switch (number){
        case 0:
            return "  ";
        case 1: 
            switch (skin){
                case '1':
                case '2':
                case '8':
                    return "🟩";
                case '3':
                    return "🟨";
                case '4':
                case '9':
                    return "⬜";
                case '5':
                    return "🟧";
                case '6':
                case '7':
                    return "🟫";
                default:
                    return "00";
            }
        case 2:
            return "🍎";
        case 3: 
            return "██";
        default:
            return "00";
    }
}

char* choose_head(char skin){
    switch (skin){
        case '1':
            return "🐍";
        case '2':
            return "🐲";
        case '3': 
            return "🐱";
        case '4':
            return "🐰";
        case '5': 
            return "🐯";
        case '6':
            return "🐻";
        case '7':
            return "🐵";
        case '8':
            return "🐸";
        case '9':
            return "🐭";
        default:
            return "00";
    }
}

int print_skins_menu(){
    char* skins[] = {"SNAKE", "DRAGON", "CAT", "RABBIT", "TIGER", "BEAR", "MONKEY", "FROG", "MOUSE"};

    clear();    // Clears ncurses console
    // Skins Menu
    printw("SKINS\n");
    int len = sizeof(skins)/sizeof(skins[0]);
    for (int i=0; i<len; i++){
        printw("%d - %s\n", i+1, skins[i]);
    }
    refresh();  // Refresh ncurses console

    int option = getch();   // Receives a character from an input
    return option;     
}

int print_main_menu(){
    char* menu[] = {"NEW GAME", "LOAD GAME", "SKINS", "LEADERBOARD", "EXIT"};

    clear();    // Limpa a tela do ncurses
    // Tela Inicial
    int len = sizeof(menu)/sizeof(menu[0]);
    printw("JOGO DA COBRA\n");
    for (int i=0; i<len; i++){
        printw("%d - %s\n", i+1, menu[i]);
    }
    refresh();  // Atualiza a tela do ncurses

    int option = getch();   // Recebe um caracter do input
    return option;
}

void print_game(map_t* map, snake_t* snake){
    clear();    // Limpa a tela do ncurse
    mvprintw(0, 0, "Pontos: %d\n", map->points);    // Imprime os pontos na primeira linha 
    for (int l=0; l<map->lines; l++){
        move(l+1, 0);       // Move o cursor para a linha seguinte
        for (int c=0; c<map->columns; c++){
            if (l == snake->tail->x && c == snake->tail->y){
                printw("%s", choose_head(map->skin));
            } else {
                printw("%s", choose_char(map->matrix[l][c], map->skin));
            }
        }
    }
    addch('\n');
    refresh();
}