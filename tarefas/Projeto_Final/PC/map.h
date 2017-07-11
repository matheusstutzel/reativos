#ifndef MAPI
#define MAPI 10
#include "maze.h"
#include "assets.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
int **map;
void geraMap(SDL_Window* window, int cols, int rows, int tile);
void freeMap();
void drawMap(SDL_Window* window, SDL_Renderer*,int);
#endif 
