#include "Setup.h"

bool init(){

	if (SDL_Init(SDL_INIT_VIDEO) < 0){
		printf("SDL_Error: %s\n", SDL_GetError());
		return false;	
	}
	if(!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")){
		printf("Warning: Linear texture filtering not enabled!\n");
	}	
	

	int imgFlags = IMG_INIT_PNG;
	if(!(IMG_Init(imgFlags)&imgFlags)){
		printf("SDL_image error: %s\n", IMG_GetError());
		return false;	
	}

	if(TTF_Init() == -1){
		printf("SDL_ttf Error: %s\n", TTF_GetError());
		return false;
	}
	
	return true;
}



bool loadMedia()
{
	return true;
}

void close(SDL_Window *window, SDL_Renderer *renderer)
{
	SDL_DestroyRenderer(renderer);	
	SDL_DestroyWindow(window);
	
	window = NULL;
	renderer = NULL;
	
	SDL_Quit();
	IMG_Quit();

}

bool setup(){
	if(!init()){
		printf("Failed to initialize!");
		return false;
	}
	if(!loadMedia()){
		return false;
	}
}

