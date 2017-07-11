#ifndef GAME 
#define GAME 10 
#include "enemy.h"
#include "player.h"
#include "map.h"
#include "MySerial.h"
#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
void game_Init(SDL_Renderer* renderer, SDL_Window *window,int rows, int cols);
int run_Game();
#endif 
