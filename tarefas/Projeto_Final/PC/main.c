#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include "game.h"
#include "pre_game.h"

#define new_max(x,y) ((x) >= (y)) ? (x) : (y)
#define new_min(x,y) ((x) <= (y)) ? (x) : (y)


int main (int argc, char* args[])
{
	int rows = 630;
	int cols = 470;
	SDL_Renderer* renderer;
	SDL_Window* window = NULL;
	/* INITIALIZATION */
	int err = SDL_Init(SDL_INIT_EVERYTHING);
	TTF_Init();
	window = SDL_CreateWindow("Input",
	SDL_WINDOWPOS_UNDEFINED,
	SDL_WINDOWPOS_UNDEFINED,
	rows, cols, SDL_WINDOW_SHOWN);
	IMG_Init(IMG_INIT_PNG);
	srand(time(NULL));
	//Initialize SDL_mixer
	if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 ){
		printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
	}
	renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_SOFTWARE);
	setPath(args[1]);
	startSerial("/dev/ttyACM0");

	int aux =0;
	long record = -1;
	/* EXECUTION */
	while(0<1){
		pregame_Init(renderer,window,rows,cols,record);
		aux = run_Pre_Game();
		if(aux<0)break;
		game_Init(renderer,window,rows,cols);
		aux = run_Game();
		if(aux<0)break;

		if(record == -1) record = aux;
		else record = new_min(aux,record);


	}
	/* FINALIZATION */
	//myFree();
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;

}

