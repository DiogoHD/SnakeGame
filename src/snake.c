#include "../lib/game_structs.h"

void init(snake_t *snake){
    snake->head = NULL;
    snake->tail = NULL;
}

int size(snake_t *snake){
    int output = 0;
    snake_node_t* temp = snake->head;

    while (temp != NULL){
        output++;
        temp = temp->next;
    }
    return output;
}

void push(snake_t *snake, int line, int column){
    snake_node_t *new_node = (snake_node_t*)malloc(sizeof(snake_node_t));

    if (new_node != NULL){
        new_node->x = line;
        new_node->y = column;
        new_node->next = NULL;
        if (snake->head == NULL){
            snake->head = new_node;
        } else {
            snake->tail->next = new_node;
        }
        snake->tail = new_node;
    }
}

void pop(snake_t *snake){
    snake_node_t *temp;

    if (snake->head != NULL){
        temp = snake->head;
        snake->head = snake->head->next;
        free(temp);
        
        if (snake->head == NULL){
            snake->tail = NULL;
        }
    }
}
