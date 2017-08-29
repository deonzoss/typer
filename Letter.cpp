#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "Letter.h"
#include "Setup.h"
#include "math.h"
#include <stdlib.h>
#include <time.h>

Letter::Letter()
{
	angle = 10 + (rand()%30);	
	velocity = 1*SCALESIZE + (rand()%(3*(int)SCALESIZE));	
  randXChange = (rand()%((int)(.5*SCALESIZE))); 
	randGroundValue = GROUND_VALUE + (rand()%(3*(int)SCALESIZE));
}

Letter::~Letter()
{
	SDL_DestroyTexture(texture);
	SDL_DestroyTexture(shadowTexture);	
	TTF_CloseFont(font);
}

void Letter::move(){

	if(onGround){
		return;
	}	
	
	double radians = angle*PI/180.0;
	
  if(rate > -50){
    relY = (((abs(relX))*(tan(radians)))-(((GRAVITY)*(pow((abs(relX)),2)))/(2.0*(pow(velocity,2)*pow(cos(radians),2))))/10);	
    rate = 4*(relY-prevRelY);
    if(rate < -50)
      rate = -50; 
  } 
  
  
  prevRelY = relY;  
	relX -= (-5)/speedMult;
   
  yPos -= (rate/10)*SCALESIZE;
  if(angle%2){  
  	xPos += (-.4*SCALESIZE - randXChange)/speedMult;	
  }
  else{
    xPos -= (-.4*SCALESIZE - randXChange)/speedMult;
  }
  groundContact();
  return;
}

bool Letter::loadLetter(char letter, SDL_Renderer* renderer)
{
	font = TTF_OpenFont(CODE_FONT, TEXT_SIZE);
	if(font == NULL){
		printf("SDL_ttf error: %s\n", TTF_GetError());
	}


	if(!loadFromRenderedText(letter, CODE_COLOR, renderer)){
		printf("Failed to render letter\n");
		return false;
	}
	return true;
} 
bool Letter::loadFromRenderedText(char letter, SDL_Color letterColor, SDL_Renderer* renderer)
{
	char letterArray[2];
	letterArray[0] = letter;	
	letterArray[1] = '\0';	
	SDL_Surface* letterSurface = TTF_RenderText_Solid(font, letterArray, CODE_COLOR);
	SDL_Surface* shadowSurface = TTF_RenderText_Solid(font, letterArray, SHADOW_COLOR); 
	this->letter = letter;
	if(letterSurface == NULL){
		printf("SDL_ttf Error: %s\n", TTF_GetError());
	}
	else{
		texture = SDL_CreateTextureFromSurface(renderer, letterSurface);
		shadowTexture = SDL_CreateTextureFromSurface(renderer, shadowSurface);
		if(texture == NULL){
			printf("SDL error: %s\n", SDL_GetError());
		}
		else{
			width = letterSurface->w;
			height = letterSurface->h;
		}

	SDL_FreeSurface(letterSurface);
	SDL_FreeSurface(shadowSurface);
	}
	return texture!=NULL;	
}

void Letter::render(double x, double y,SDL_Renderer* renderer, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip)
{
	if(onGround){	
		SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
		SDL_SetTextureAlphaMod(texture, alpha);

		SDL_SetTextureBlendMode(shadowTexture, SDL_BLENDMODE_BLEND);
		SDL_SetTextureAlphaMod(shadowTexture, alpha);
	}	
	
	SDL_Rect renderQuad = {x+.3*SCALESIZE,y+.3*SCALESIZE,width,height};

	SDL_RenderCopyEx(renderer, shadowTexture, clip, &renderQuad, angle, center, flip);
	
	renderQuad = {x,y,width,height};

	SDL_RenderCopyEx(renderer, texture, clip, &renderQuad, angle, center, flip);
}

void Letter::fade()
{
  if(alpha < 10){
    alpha = 0;
    return;  
  } 
  alpha-=10;
}

double Letter::getSpeed(){
  return speedMult;
}

void Letter::setSpeed(double value){
  this->speedMult = value;
}

void Letter::setX(double x)
{
	xPos = x;
}

void Letter::setY(double y)
{
	yPos = y;
}

Uint8 Letter::getAlpha()
{
		return alpha;
}

Uint32 Letter::getLifetime()
{
	return SDL_GetTicks()-lifetime;
}

double Letter::getX()
{
	return xPos;
}

double Letter::getY()
{
	return yPos;
}

bool Letter::getOnGround(){
  return onGround;
}

void Letter::setOnGround(bool value)
{
  onGround = value;
  if(onGround)
    lifetime = SDL_GetTicks();
}

void Letter::setDynamic(int value){
  dynamic = value;
}

int Letter::getDynamic(){
  return dynamic;
}

bool Letter::offScreen()
{
	if(yPos > SCREEN_HEIGHT){
		return true;
	}

	return false;
}

bool Letter::groundContact()
{
	if(yPos >= randGroundValue){ 
		yPos = randGroundValue; 
		onGround = true;	
	  lifetime = SDL_GetTicks();	
    return onGround;
	}
	return false;
}

