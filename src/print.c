#include "../lib/print.h"

// Chooses the character to be printed
char* choose_char(int number, Skin skin){
    switch (number){
        // Prints empty spaces on the map
        case 0:
            return "  ";
        // Prints the snake
        case 1: 
            switch (skin){
                case SNAKE:
                case DRAGON:
                case FROG:
                    return "🟩";
                case CAT:
                    return "🟨";
                case RABBIT:
                case MOUSE:
                    return "⬜";
                case TIGER:
                    return "🟧";
                case BEAR:
                case MONKEY:
                    return "🟫";
                default:
                    return "00";
            }
        // Prints the apple
        case 2:
            return "🍎";
        // Prints the walls
        case 3: 
            return "██";
        // To see if there's an error with the printing
        default:
            return "00";
    }
}

// Chooses the skin's head
char* choose_head(Skin skin){
    switch (skin){
        case SNAKE:
            return "🐍";
        case DRAGON:
            return "🐲";
        case CAT: 
            return "🐱";
        case RABBIT:
            return "🐰";
        case TIGER: 
            return "🐯";
        case BEAR:
            return "🐻";
        case MONKEY:
            return "🐵";
        case FROG:
            return "🐸";
        case MOUSE:
            return "🐭";
        default:
            return "00";
    }
}

// Prints the skins menu
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

    int option = getch() - '0';   // Receives a character from an input ('1'-'9') and turns it into a number (1-9)
    return option;     
}

// Prints the main menu
int print_main_menu(){
    char* menu[] = {"NEW GAME", "LOAD GAME", "SKINS", "LEADERBOARD", "EXIT"};

    clear();    // Cleans ncurses console
    // Main Menu
    int len = sizeof(menu)/sizeof(menu[0]);
    printw("SNAKE GAME\n");
    for (int i=0; i<len; i++){
        printw("%d - %s\n", i+1, menu[i]);
    }
    refresh();  // Refresh ncurses console

    int option = getch();   // Recebe um caracter do input
    return option;
}

// Prints the game
void print_game(map_t* map, snake_t* snake){
    clear();    // Cleats ncurses console
    mvprintw(0, 0, "POINTS: %d\n", map->points);    // Prints the points in the first line
    for (int l=0; l<map->lines; l++){
        move(l+1, 0);       // Moves the cursor to the next line
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

// Prints the messages when you loose or save the game
void print_end_screen(map_t* map, snake_t* snake, bool game_lost){
    timeout(-1);        // Waits indefinitely for a key
    // End screen
    if (game_lost){
        printw("Your snake hit a wall! You lost!\n");
    } else {
        printw("Game Saved!\n");
        save_game(snake, map);
    }
    printw("Press any key to leave...\n");
    refresh();
    napms(2000);    // Waits for 2 seconds before allowing to press a key
    getch();        // Waits for a key before closing
    flushinp();     // Cleans the buffer    
}