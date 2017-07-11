#ifndef ENEMY
#define ENEMY 10
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <assets.h>
typedef struct{
	int x;
	int y;
	int r,g,b;
	int hp;
	int atk;
	int def;
	int speed;
	float HPMAX;
	int state;//0 ok 1 atk 2 persegue
}enemy;

void updateEnemy(enemy);
void drawEnemy(enemy e, SDL_Renderer* renderer, SDL_Window* window, int tile);

void spawnEnemy(enemy * e ,int x, int y,int level,SDL_Window* window);
void freeEnemy(enemy *e);
#endif
