#include "../lib/game_init.h"

map_t* create_map(int lines, int columns){
    map_t* output = (map_t*)malloc(sizeof(map_t));
    
    if (output == NULL){
        return NULL;
    } else {
        output->lines = lines;
        output->columns = columns;
        output->points = 0;
        output->skin = '1';

        // Alocar dinamicamente a memoria da matrix
        int** matrix;
        matrix = (int**)malloc(sizeof(int*)*lines);
        for (int l=0; l<lines; l++){
            matrix[l] = (int*)malloc(sizeof(int)*columns);
        }

        for (int l=0; l<lines; l++){
            for (int c=0; c<columns; c++){
                if (l == 0 || l == lines-1 || c == 0 || c == columns-1){
                    matrix[l][c] = 3;
                } else {
                    matrix[l][c] = 0;
                }
            }
        }
        output->matrix = matrix;
        return output;
    }
}

// Generates the apple in the map on a random position
void generate_apple(map_t* map){
    int line;
    int column;
    do {
        line = random_number(1, map->lines-1);
        column = random_number(1, map->columns-1);
    } while (map->matrix[line][column] == 1 || map->matrix[line][column] == 2);
    map->matrix[line][column] = 2;
}

// Generates the snake in the map on a random position
void generate_snake(map_t* map){
    int line;
    int column;
    do {
        line = random_number(1, map->lines-1);
        column = random_number(1, map->columns-1);
    } while (map->matrix[line][column] == 2);
    map->matrix[line][column] = 1;
}

// Creates the snake in the specified struct
void create_snake(snake_t* snake, map_t* map){
    init(snake);
    for (int l=0; l<map->lines; l++){
        for (int c=0; c<map->columns; c++){
            if (map->matrix[l][c] == 1){
                push(snake, l, c);
            }
        }
    }
}

// Starts the game
void start_game(map_t* map){
    bool is_there_apple = false, is_there_snake = false;
    for (int l=0; l<map->lines; l++){
        for (int c=0; c<map->columns; c++){
            if (map->matrix[l][c] == 1){
                is_there_snake = true;
            } else if (map->matrix[l][c] == 2) {
                is_there_apple = true;
            }
        }
    }
    // If this elements are not yet on the map, generates them
    if (!is_there_snake) generate_snake(map);
    if (!is_there_apple) generate_apple(map);
}