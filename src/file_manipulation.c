#include "../lib/file_manipulation.h"

void save_game(snake_t* snake, map_t* map){
    FILE *f;
    f = fopen("files/save.txt", "w");
    if (f == NULL){
        printw("Erro ao abrir o ficheiro\n");
        exit(1);
    }

    // Save the number of lines, columns, ponts and the skin being used
    fprintf(f, "Lines: %d\nColumns: %d\nPoints: %d\nSkin: %c\n", map->lines, map->columns, map->points, map->skin);

    // Save apple position
    for (int l=0; l<map->lines; l++){
        for (int c=0; c<map->columns; c++){
            if (map->matrix[l][c] == 2){
                fprintf(f, "Apple: (%d, %d)\n", l, c);
            }
        }
    }

    // Save snake position in order
    fprintf(f, "Snake:");
    while (snake->head != NULL){
        fprintf(f, "\n(%d, %d)", snake->head->x, snake->head->y);
        pop(snake);
    }
    fclose(f);
}

map_t* load_game(snake_t* snake){
    FILE *f;
    f = fopen("files/save.txt", "r");
    if (f == NULL){
        printw("Erro ao abrir o ficheiro\n");
        exit(1);
    }

    // Create map
    map_t* map;
    int lines, columns, points;
    char skin;
    fscanf(f, "Lines: %d\nColumns: %d\nPoints: %d\nSkin: %c\n", &lines, &columns, &points, &skin);
    map = create_map(lines, columns);
    map->points = points;
    map->skin = skin;

    // Save apple position
    int x, y;
    fscanf(f, "Apple: (%d, %d)\n", &x, &y);
    map->matrix[x][y] = 2;

    // Create snake
    init(snake);
    fscanf(f, "Snake:");
    while (fscanf(f, "\n(%d, %d)", &x, &y) != EOF){
        push(snake, x, y);
        map->matrix[x][y] = 1;
    }
    fclose(f);
    return map;
}

// Loads the leaderboard to an array
void load_leaderboard(){
    // Open leaderboard binary file
    FILE *f;
    f = fopen("files/leaderboard.bin", "rb");
    if (f == NULL){
        printw("Erro ao abrir a leaderboard.\n");
        refresh();
        exit(1);
    }

    // Find the lenght of the file
    fseek(f, 0, SEEK_END);
    long int bytes = ftell(f);
    rewind(f);
    int size = sizeof(rank_t);
    int len = bytes / size;

    clear();
    if (len == 0){
        fclose(f);
        printw("A leaderboad está vazia.\n");
    } else {
        // Save the file in an array
        rank_t leaderboard[len];
        fread(&leaderboard, size, len, f);
        fclose(f);
        
        // Print the leaderboard
        printw("LEADERBOARD");
        for (int i=0; i<len; i++){
            printw("\n%dº | %d pontos | %d/%d/%d às %d:%d:%d\n", i+1, leaderboard[i].points, 
                leaderboard[i].date.tm_mday, leaderboard[i].date.tm_mon+1, leaderboard[i].date.tm_year+1900,
                leaderboard[i].date.tm_hour, leaderboard[i].date.tm_min, leaderboard[i].date.tm_sec);
        }
    }

    refresh();
}

// Ads a rank to the leaderboard
void add_to_leaderboard(int points){
    // Open leaderboard binary file
    FILE *f;
    f = fopen("leaderboard.bin", "rb+");
    if (f == NULL){
        printw("Erro ao abrir a leaderboard.\n");
        exit(1);
    }

    // Find the lenght of the file
    fseek(f, 0, SEEK_END);
    long int bytes = ftell(f);
    rewind(f);
    int size = sizeof(rank_t);
    int len = bytes / size;

    // Creating the new classification to be added
    time_t seconds_now = time(NULL);
    struct tm date_now = *localtime(&seconds_now);
    rank_t rank = {.points = points, .date = date_now};

    // If there's nothing on the leadeboard
    if (len == 0){
        rewind(f);
    // If the leaderboard is not full
    } else if (len <= 10){
        fseek(f, 0, SEEK_END);
    // If the leaderboard is full
    } else {
        fseek(f, 0, SEEK_SET);
        rank_t temp;
        do {
            fread(&temp, size, 1, f);
        } while (temp.points > points);
        fseek(f, -size, SEEK_CUR);
    }
    fwrite(&rank, size, 1, f);
    fclose(f);
}