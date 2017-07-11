#ifndef PREGAME 
#define PREGAME 10 
#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
void pregame_Init(SDL_Renderer* renderer, SDL_Window *window,int rows, int cols,long r);
int run_Pre_Game();
#endif 
