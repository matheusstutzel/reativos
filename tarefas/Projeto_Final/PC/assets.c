#include "assets.h"
char dest[500];
char path[500];
SDL_Surface* eSurface=NULL;
SDL_Surface* gSurface = NULL;
SDL_Surface* oSurface = NULL;
SDL_Surface* pSurface = NULL;
SDL_Surface* bSurface = NULL;
Mix_Chunk *bSound = NULL;



SDL_Surface* load(SDL_Window* window,char* path){
    //Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load(getFile(path));
    SDL_Surface* screen = SDL_GetWindowSurface(window);


    if( loadedSurface == NULL ||screen == NULL){
        printf( "Unable to load image grass! SDL_image Error: %s\n", IMG_GetError() );
    }else{
	gSurface=loadedSurface;
        //Convert surface to screen format
        gSurface = SDL_ConvertSurface( loadedSurface, SDL_GetWindowSurface(window)->format, 0 );
        if( gSurface == NULL ){

            printf( "Unable to optimize image grass! SDL Error: %s\n", 	SDL_GetError() );

        }

        //Get rid of old loaded surface

        SDL_FreeSurface( loadedSurface );
    }

	return gSurface;
}

SDL_Surface* loadBGSurface(SDL_Window* window){
    return load(window,"black.png");
}

SDL_Surface* loadEnemySurface(SDL_Window* window){
	return load(window,"enemy.png");
}

SDL_Surface* loadGrass(SDL_Window* window){
	return load(window,"grass.png");
}

SDL_Surface* loadObstacle(SDL_Window* window){
    return load(window,"obstacle.png");
}

SDL_Surface* loadPlayerSurface(SDL_Window* window){
    return load(window,"hero.png");
}
Mix_Chunk * loadBattleSound(){
    //Load sound effects
    bSound = Mix_LoadWAV(getFile("sound.wav"));
    if( bSound == NULL )
    {
        printf( "Failed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
    }
	return bSound;
}

void setPath(char * p){
	strcpy(path,p);
	strcat(path, "/");
}
char* getFile(char* filename){
   	strcpy(dest, path);
	strcat(dest, filename);
	return dest;
}
