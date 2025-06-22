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