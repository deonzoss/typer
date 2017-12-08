#include "Level.h"
#include <string>



Level::Level(int rate, double speed, int num, SDL_Renderer* renderer)
{
	this->wordRate = rate;
	this->masterSpeed = speed;
  this->levelNumber = num;
  this->renderer = renderer;
  if(levelNumber = 1){
    levelLifetime = 1000*6;
  }
  loadFont(fontSize);
  loadFromRenderedText();
}

Level::~Level()
{
  free();
}

void Level::free(){

}

void Level::loadFont(double size){
  font = TTF_OpenFont(CODE_FONT, size);
  if(font == NULL){
    printf("Error opening score font. TTF_Error: %n", TTF_GetError());
  }

}

int Level::getRand(){
  int randNum = rand()%2;
  if(randNum){
    incSpeed = true;
    incRate = false;
  }
  else{
    incSpeed = false;
    incRate = true;
  } 
  return randNum;
}


void Level::loadFromRenderedText()
{
  strcpy(levelString, "LEVEL: ");
  strcat(levelString, std::to_string(levelNumber).c_str());
  SDL_Surface* textSurface = TTF_RenderText_Solid(font, levelString, CODE_COLOR);
  SDL_Surface* shadowSurface = TTF_RenderText_Solid(font, levelString, SHADOW_COLOR);	
  if(!textSurface){
    printf("Error making score surface. TTF_Error: %n", TTF_GetError());
  }
  else{
    levelTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    shadowTexture = SDL_CreateTextureFromSurface(renderer, shadowSurface);
    if(!levelTexture){
      printf("Unable to render texture from rendered text, SDL Error: %s\n", SDL_GetError());
    }
    else{
      width = textSurface->w;
      height = textSurface->h;
      shadowWidth = shadowSurface->w;
      shadowHeight= shadowSurface->h;
    }

    SDL_FreeSurface(textSurface);
    SDL_FreeSurface(shadowSurface);
  }
      
}

void Level::render()
{
  SDL_Rect renderQuad = {xPos+shadowOffset,yPos+shadowOffset, shadowWidth, shadowHeight};

  if(SDL_RenderCopyEx(renderer, shadowTexture, NULL, &renderQuad, 0.0, NULL, SDL_FLIP_NONE)!=0){
    printf("%s\n", SDL_GetError());
  }
  
  renderQuad = {xPos,yPos, width, height};

  SDL_RenderCopyEx(renderer, levelTexture, NULL, &renderQuad, 0.0, NULL, SDL_FLIP_NONE);
  
			
}


int Level::getWordRate()
{
	return wordRate;
}

double Level::getSpeed()
{
	return masterSpeed;
}

int Level::getLifetime()
{
	return levelLifetime;
}

void Level::setLevelNum(int value)
{
  levelNumber = value;
  if(levelTexture){
    SDL_DestroyTexture(levelTexture);
    SDL_DestroyTexture(shadowTexture);
    loadFromRenderedText();
  }
}

int Level::getLevelNum()
{
  return levelNumber;
}
