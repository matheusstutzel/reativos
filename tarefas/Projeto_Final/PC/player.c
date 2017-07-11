#include "player.h"
#define new_max(x,y) ((x) >= (y)) ? (x) : (y)
#define new_min(x,y) ((x) <= (y)) ? (x) : (y)
int x;
int y;
int atk;
int def;
int hp;
float HPMAX;
int rv;
SDL_Surface* playerSurface = NULL;
SDL_Surface* bgSurface = NULL;
Mix_Chunk *battleSound = NULL;

void playerInit(SDL_Window* window){
    x = 1;
    y = 1;
    atk = 10;
    def = 10;
    hp = 100;
    HPMAX =100.0;
    rv = 10;
    playerSurface = loadPlayerSurface(window);
    bgSurface = loadBGSurface(window);
    battleSound = loadBattleSound();
}

void movePlayer(int Dx,int Dy){
    x+=Dx;
    y+=Dy;
}

void getPosPlayer(int *px,int *py){
    *px = x;
    *py = y;
}

void drawPlayer(SDL_Renderer* renderer, SDL_Window* window, int tile){
    SDL_Rect rect = {0,0,tile,tile};
    rect.x=x*tile;
    rect.y=y*tile;
    SDL_BlitSurface(playerSurface, NULL, SDL_GetWindowSurface(window), &rect);
}
void drawPlayerView(SDL_Window* window,int tile,int w,int h, int vision){
    rv = vision;
    SDL_Rect rect = {0,0,tile,tile};
    //SDL_SetRenderDrawColor(renderer,0,0,0,0x00);
    for(int i = 0; i < w/tile; i++)for(int j = 0; j < h/tile; j++){
        rect.x=i*tile;
        rect.y=j*tile;
        if(!((i-x)*(i-x) +(j - y)*(j - y) < rv * rv)){
	  	SDL_BlitSurface(bgSurface, NULL, SDL_GetWindowSurface(window), &rect);
                //SDL_RenderFillRect(renderer,&rect);
        }
    }
}

void combat(enemy *e){
	if(e->hp>0){
        Mix_PlayChannel( -1, battleSound, 0 );
        //printf("COMbATEU %d %d\n",hp,e->hp);
        e->hp=-1;
        //hp-= new_max(10,def-e->atk);
	}
}
