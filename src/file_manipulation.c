#include "../lib/file_manipulation.h"

void save_game(snake_t* snake, map_t* map){
    FILE *f;
    f = fopen("save/save.txt", "w");
    if (f == NULL){
        printw("Erro ao abrir o ficheiro\n");
        exit(1);
    }

    // Salvar o número de linhas, colunas, pontos e a skin
    fprintf(f, "Lines: %d\nColumns: %d\nPoints: %d\nSkin: %c\n", map->lines, map->columns, map->points, map->skin);

    // Salvar a posição da maçã
    for (int l=0; l<map->lines; l++){
        for (int c=0; c<map->columns; c++){
            if (map->matrix[l][c] == 2){
                fprintf(f, "Apple: (%d, %d)\n", l, c);
            }
        }
    }

    // Salvar a posição da cobra por ordem
    fprintf(f, "Snake:");
    while (snake->head != NULL){
        fprintf(f, "\n(%d, %d)", snake->head->x, snake->head->y);
        pop(snake);
    }
    fclose(f);
}

map_t* load_game(snake_t* snake){
    FILE *f;
    f = fopen("save/save.txt", "r");
    if (f == NULL){
        printw("Erro ao abrir o ficheiro\n");
        exit(1);
    }

    // Criar o mapa
    map_t* map;
    int lines, columns, points;
    char skin;
    fscanf(f, "Lines: %d\nColumns: %d\nPoints: %d\nSkin: %c\n", &lines, &columns, &points, &skin);
    map = create_map(lines, columns);
    map->points = points;
    map->skin = skin;

    // Salvar a posição da maçã
    int x, y;
    fscanf(f, "Apple: (%d, %d)\n", &x, &y);
    map->matrix[x][y] = 2;

    // Criar a cobra
    init(snake);
    fscanf(f, "Snake:");
    while (fscanf(f, "\n(%d, %d)", &x, &y) != EOF){
        push(snake, x, y);
        map->matrix[x][y] = 1;
    }
    fclose(f);
    return map;
}

