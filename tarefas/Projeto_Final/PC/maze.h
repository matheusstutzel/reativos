#ifndef MAZE
#define MAZE 10
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

typedef struct{
    int x, y; //Node position - little waste of memory, but it allows faster generation
    void *parent; //Pointer to parent node
    char c; //Character to be displayed
    char dirs; //Directions that stil haven't been explored
} Node;
Node * createMaze( int width, int height );
void drawMaze(Node * nodes, int width, int height );
#endif 
