#include "pre_game.h"


SDL_Event e;
int rows;
int cols;
SDL_Renderer* re;
SDL_Window* wi = NULL;
TTF_Font* font;
long record;
char text[50];

int keyEvent_pre(){

  if(SDL_PollEvent(&e)!=0){
    switch(e.type){
      case SDL_QUIT: {
        return 1;
      }
      case SDL_KEYDOWN:
        switch (e.key.keysym.sym)
        {
          case SDLK_RIGHT:  return 2;
        }
        break;
    }
  }
  return 0;
}

void draw_background_pre(SDL_Renderer* render ){
	SDL_SetRenderDrawColor(render,0xFF,0xFF,0xFF,0x00);
	SDL_RenderFillRect(render, NULL);
}


void draw_text(){
	sprintf(text,"Pressione -> para iniciar");


	SDL_Color White = {255, 0, 0}; 
	SDL_Surface* surfaceMessage = TTF_RenderText_Solid(font, text, White);
	SDL_Rect Message_rect = {100,100,100,100} ;
	SDL_BlitSurface(surfaceMessage, NULL, SDL_GetWindowSurface(wi), &Message_rect);
	SDL_FreeSurface(surfaceMessage);

	if(record>0){
		long s,m,h;
		s = record /1000;
		m = s / 60;
		h = m / 60;
		m %=60;
		s%=60;

		sprintf(text,"Record atual: %02ld:%02ld:%02ld",h,m,s);

	 	surfaceMessage = TTF_RenderText_Solid(font, text, White);
		Message_rect.y = 200;
		SDL_BlitSurface(surfaceMessage, NULL, SDL_GetWindowSurface(wi), &Message_rect);
		SDL_FreeSurface(surfaceMessage);
	}
}
void draw_pre(){
	draw_background_pre(re);
	draw_text();
	SDL_UpdateWindowSurface( wi );
}

int loop_pre(){
	draw_pre();
	return keyEvent_pre();
}

void pregame_Init(SDL_Renderer* r, SDL_Window *w,int ro, int co,long rec){
	re = r;
	wi = w;
	cols = co;
	rows = ro;
	record = rec;
	font = TTF_OpenFont("font.ttf", 24);
}

int run_Pre_Game(){
	int res;
	while ((res = loop_pre())==0);
	
	return res-2;
}
