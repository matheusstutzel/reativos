#ifndef TESTE 
#define TESTE 10 
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>

SDL_Surface* loadGrass(SDL_Window* window);
SDL_Surface* loadObstacle(SDL_Window* window);
SDL_Surface* loadPlayerSurface(SDL_Window* window);
Mix_Chunk * loadBattleSound();
SDL_Surface* loadEnemySurface(SDL_Window* window);
char* getFile(char* filename);
SDL_Surface* loadBGSurface(SDL_Window* window);
void setPath(char* path);


#endif 
