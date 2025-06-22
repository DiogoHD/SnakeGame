#ifndef SNAKE_H
#define SNAKE_H

typedef struct snake_node{
    int x, y;
    struct snake_node *next;
} snake_node_t;

typedef struct{
    snake_node_t *head;
    snake_node_t *tail;
} snake_t;

void init(snake_t* snake);
int size(snake_t* snake);
void push(snake_t* snake, int line, int column);
void pop(snake_t* snake);

#endif