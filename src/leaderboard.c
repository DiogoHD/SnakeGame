#include "../lib/leaderboard.h"

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
            printw("\n%dº | %d pontos | %d/%d/%d às %d:%d:%d", i+1, leaderboard[i].points, 
                leaderboard[i].date.tm_mday, leaderboard[i].date.tm_mon+1, leaderboard[i].date.tm_year+1900,
                leaderboard[i].date.tm_hour, leaderboard[i].date.tm_min, leaderboard[i].date.tm_sec);
        }
    }

    // Ending the print
    refresh();
    getch();
}

void order_leaderboard(rank_t leaderboard[], int size){
    bool unordered = true;
    rank_t temp;
    while (unordered){
        unordered = false;
        for (int i=0; i<size-1; i++){
            if (leaderboard[i].points < leaderboard[i+1].points){
                unordered = true;
                temp = leaderboard[i];
                leaderboard[i] = leaderboard[i+1];
                leaderboard[i+1] = temp;
            }
        }
    }
}

// Ads a rank to the leaderboard
void add_to_leaderboard(int points){
    // Open leaderboard binary file
    FILE *f;
    f = fopen("files/leaderboard.bin", "rb+");
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
 
    // Reads the leaderboard ands orders it
    rank_t* leaderboard = (rank_t*)malloc(size*(len+1));
    fread(leaderboard, size, len, f);
    leaderboard[len] = rank;
    order_leaderboard(leaderboard, len+1);
    rewind(f);

    // If the leaderboard is not full
    if (len+1 <= 10){
        fwrite(leaderboard, size, len+1, f);
    // If the leaderboard is full
    } else {
        fwrite(leaderboard, size, 10, f);
    }
    
    // End function
    fclose(f);
    free(leaderboard);
}