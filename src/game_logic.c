#include "../lib/game_logic.h"

// Generates a random number between a minimun (including) and a maximum (including)
int random_number(int min, int max){
    int output = min + rand() % (max - min);
    return output;
}

bool move_snake(snake_t* snake, map_t* map, int input, int *last_move){
    int x = snake->tail->x;
    int y = snake->tail->y;
    input = toupper(input);     // Função da biblioteca ctype, que transforma o caracter em maiuscula
    bool apple_eaten = false, game_lost = false;

    // Impedir movimento inverso
    if (((input == 'W' || input == KEY_UP) && (*last_move == 'S' || *last_move == KEY_DOWN)) ||
        ((input == 'S' || input == KEY_DOWN) && (*last_move == 'W' || *last_move == KEY_UP)) ||
        ((input == 'A' || input == KEY_LEFT) && (*last_move == 'D' || *last_move == KEY_RIGHT)) ||
        ((input == 'D' || input == KEY_RIGHT) && (*last_move == 'A' || *last_move == KEY_LEFT)))
    {
        return false;
    }


    // Decidir as coordenadas do próximo movimento, consoante a tecla digitada
    switch (input){
        case 'W':
        case KEY_UP:
            x--;
            break;
        case 'S':
        case KEY_DOWN:
            x++;
            break;
        case 'A':
        case KEY_LEFT:
            y--;
            break;
        case 'D':
        case KEY_RIGHT:
            y++;
            break;
        default:
            return false;
    }

    // Verificar se perdeu o jogo
    if (map->matrix[x][y] == 3 || map->matrix[x][y] == 1){
        game_lost = true;
    } else if (map->matrix[x][y] == 2){
        apple_eaten = true;
    }

    push(snake, x, y);          // Adiciona a nova cabeça

    // Aumentar consoante come ou não a maçã
    if (apple_eaten){
        generate_apple(map);    // Gera a maçã
        map->points++;          // Adiciona um ponto
    } else {
        pop(snake);             // Destrói a cauda
    }



    // Limpar a matriz
    for (int l=0; l<map->lines; l++){
        for (int c=0; c<map->columns; c++){
            if (map->matrix[l][c] == 1){
                map->matrix[l][c] = 0;
            }
        }
    }

    // Reinserir a cobra
    snake_node_t* temp = snake->head;
    while (temp != NULL){
        map->matrix[temp->x][temp->y] = 1;
        temp = temp->next;
    }
    *last_move = input;
    return game_lost;
}