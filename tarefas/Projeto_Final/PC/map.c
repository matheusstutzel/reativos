#include "map.h"

int __mapc,__mapr;
SDL_Surface* grassSurface = NULL;
SDL_Surface* obstacleSurface = NULL;



void geraMap(SDL_Window* window, int cols, int rows, int tile){
    grassSurface = loadGrass(window);
    obstacleSurface = loadObstacle(window);
    cols = cols/tile;
    rows = rows/tile;
    __mapc=cols;
    __mapr=rows;
    Node *n = createMaze(cols,rows);
    //drawMaze(n,cols,rows);
    map = (int **)malloc(rows * sizeof(int*));
    for(int i = 0; i < rows; i++){
            map[i] = (int *)malloc(cols * sizeof(int));
    }
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            map[i][j]= (n[j + i * cols].c ==' ')?0:1;
        }
    }
    free(n);
}

void freeMap(){
    for(int i = 0; i < __mapr; i++) free(map[i]);
    free(map);
}

void convertTile(SDL_Window* window, SDL_Renderer* renderer,int code, SDL_Rect* dest){
    if(code==0){
            SDL_BlitSurface(grassSurface, NULL, SDL_GetWindowSurface(window), dest);
    }else if(code==1){
        SDL_BlitSurface(obstacleSurface, NULL, SDL_GetWindowSurface(window), dest);
    }
}

void drawMap(SDL_Window* window, SDL_Renderer* renderer, int tile){
    SDL_Rect rect = {0,0,tile,tile};
    for(int i = 0; i < __mapr; i++){
        for(int j = 0; j < __mapc; j++){
            rect.x=j*tile;
            rect.y=i*tile;
            convertTile(window,renderer,map[i][j],&rect);
        }
    }
}
