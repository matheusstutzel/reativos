#include "game.h"
#define ENEMYSIZE 5
int tile = 10; 
enemy es[ENEMYSIZE];

SDL_Event e;

int visi =10;

int rows;
int cols;
SDL_Renderer* renderer;
SDL_Window* window = NULL;
Mix_Music *gMusic = NULL;
int r;
TTF_Font* font;
Uint32 now,start,diff;
SDL_Texture *texture = NULL;
char timer[50];
int testMap(int dx,int dy){
    int x; int y;

    getPosPlayer(&x,&y);

    x+=dx;

    y+=dy;
    //!pode andar retorna
    if(map[y][x])return !map[y][x];
    //pode andar....
    for(int i=0;i<ENEMYSIZE;i++){
        if(es[i].x==x && es[i].y==y){
            //tem monstro ataca
            combat(&es[i]);
            //matou? anda...
            return(es[i].hp<=0);
        }
    }
    //!tem monstro anda...
    return 0<1;//true
}


void trataKey(int code){
if(code==4)if(testMap(-1,0))movePlayer(-1,0);
if(code==3)if(testMap(1,0))movePlayer(1,0); 
if(code==1)if(testMap(0,-1))movePlayer(0,-1); 
if(code==2)if(testMap(0,1))movePlayer(0,1);
}
void updateEnemies(){
	for(int i=0;i<ENEMYSIZE;i++)updateEnemy(es[i]);
}

void drawEnemies(){
    for(int i=0;i<ENEMYSIZE;i++){
            drawEnemy(es[i],renderer,window,tile);
    }
}



void draw_background(SDL_Renderer* render ){
    SDL_SetRenderDrawColor(renderer,0xFF,0xFF,0xFF,0x00);
    SDL_RenderFillRect(renderer, NULL);
}

void drawTimer(SDL_Window* window,int tile,int w){
	now = SDL_GetTicks();
	diff = now - start;
//	printf("Time: %"PRIu32"\n",diff);
	long s,m,h;
	s = diff /1000;
	m = s / 60;
	h = m / 60;
	m %=60;
	s%=60;

	sprintf(timer,"%02ld:%02ld:%02ld",h,m,s);


	SDL_Color White = {255, 0, 0}; 
	SDL_Surface* surfaceMessage = TTF_RenderText_Solid(font, timer, White);
	SDL_Rect Message_rect = {w-120,0,100,100} ;
	SDL_BlitSurface(surfaceMessage, NULL, SDL_GetWindowSurface(window), &Message_rect);
	SDL_FreeSurface(surfaceMessage);
}
void draw(){
    draw_background(renderer);
    drawMap(window, renderer,tile);
    drawEnemies();
    drawPlayer(renderer, window, tile);
    drawPlayerView(window,tile,rows,cols, visi);
    drawTimer(window,tile,rows);   
}


int keyEvent(){

  if(SDL_PollEvent(&e)!=0){
    switch(e.type){
      case SDL_QUIT: {
        return 1;
      }
      case SDL_KEYDOWN:
        switch (e.key.keysym.sym)
        {
          case SDLK_LEFT:  trataKey(4); break;
          case SDLK_RIGHT: trataKey(3);break;
          case SDLK_UP:    trataKey(1);break;
          case SDLK_DOWN:  trataKey(2);break;
        }
        break;
    }
  }
  return 0;
}



void geraEnemy(){
	int x,y,achou,count;
	count =0;
	if(map[2][1])
        spawnEnemy(&es[count++],2,1,10,window);
    else
        spawnEnemy(&es[count++],1,2,10,window);
	while(count < ENEMYSIZE){
		achou = 0!=0;
		while(!achou){
			x = rand() %(rows/tile);
			y = rand() %(cols/tile);
			achou = !map[y][x];
		}
		for(int i =0;i<count;i++)if(es[i].x==x && es[i].y==y)	achou = 0!=0;
		if(achou){
			spawnEnemy(&es[count++],x,y,10,window);
		}
  	}
}


void myFree(){
  freeMap();
}

int loop(){
	if( Mix_PlayingMusic() == 0 )
	{
		Mix_PlayMusic( gMusic, -1 );
	}
	updateEnemies();
	draw();
	if(keyEvent())return 0;

	r = readSerial();
	if(r>0)visi=r*3/tile +1;
	else if(r<0) {trataKey(-r);}

	SDL_UpdateWindowSurface( window );

	return 1;

}


void game_Init(SDL_Renderer* r, SDL_Window *w,int ro, int co){
	font = TTF_OpenFont("font.ttf", 24); 
	renderer = r;
	window = w;
	rows = ro;
	cols = co;
	texture = IMG_LoadTexture(renderer, "grass.png");
	geraMap(window, rows, cols,tile);
	playerInit(window);
	gMusic = Mix_LoadMUS( getFile("music.wav") );
	geraEnemy();
}
int testaFim(){
	for(int i =0;i<ENEMYSIZE;i++)if(es[i].hp>0)return 0;
	return diff;
}
void closeGame(){
	Mix_HaltMusic();
	TTF_CloseFont(font);
}
int run_Game(){
	start = SDL_GetTicks();
	int resultado;
	while (loop()){
		resultado = testaFim();
		if(resultado>0){closeGame();return resultado;}
	}
	return -1;
}
