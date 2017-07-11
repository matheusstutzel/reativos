#ifndef PLAYER
#define PLAYER 10
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include "enemy.h"
#include "assets.h"

void movePlayer(int Dx,int Dy);
void getPosPlayer(int *x,int *y);
void drawPlayer(SDL_Renderer* renderer, SDL_Window* window, int tile);
void drawPlayerView(SDL_Window* window,int tile,int w,int h, int vision);
void combat(enemy *e);
void playerInit(SDL_Window* window);
#endif 
