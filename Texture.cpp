#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <iostream>
#include "Texture.h"
#include "Setup.h"

Texture::Texture(){
	xPos = SCREEN_WIDTH;
}

Texture::~Texture(){
	free();
}

bool Texture::offScreen()
{
	if(xPos < (0-((TEXT_SIZE/2)*length()))){
		return true;
	}

	return false;
}

int Texture::popFront(){
	loadFromRenderedText(text.erase(0,1));
	return xPos;
}

bool Texture::loadText(std::string text)
{

	free();	

	originalText = text;

	gFont = TTF_OpenFont(CODE_FONT, TEXT_SIZE);
	if(gFont == NULL){
		printf("SDL_ttf error: %s\n", TTF_GetError());
	}

	if(!loadFromRenderedText(text)){
			printf("Failed to render text texture\n");
			return false;
	}

	xPos = SCREEN_WIDTH;
	return true;
}



bool Texture::loadFromRenderedText(std::string textureText)
{	
	SDL_Surface* textSurface = TTF_RenderText_Solid(gFont, textureText.c_str(), CODE_COLOR);	
	
	
	SDL_Surface* shadowSurface = TTF_RenderText_Solid(gFont, textureText.c_str(), SHADOW_COLOR);
	
	
	text = textureText;	
	if(textSurface == NULL){
		printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
	}
	else{
		mTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
		shadowTexture = SDL_CreateTextureFromSurface(renderer, shadowSurface);
		if(mTexture == NULL){
			printf("Unable to render texture from rendered text, SDL Error: %s\n", SDL_GetError());
		}
		else{
			mWidth = textSurface->w;
			mHeight = textSurface->h;
			shadowWidth = shadowSurface->w;
			shadowHeight = shadowSurface->h;	
		}

		SDL_FreeSurface(textSurface);
		SDL_FreeSurface(shadowSurface);	
	}

	return mTexture != NULL & shadowTexture != NULL;
}


void Texture::render(double x, double y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip)
{
	SDL_Rect renderQuad = {x+.3*SCALESIZE,y+.3*SCALESIZE,shadowWidth, shadowHeight};

	SDL_RenderCopyEx(renderer, shadowTexture, clip, &renderQuad, angle, center, flip);
	
	renderQuad = {x,y,mWidth, mHeight};

	SDL_RenderCopyEx(renderer, mTexture, clip, &renderQuad, angle, center, flip);
}

void Texture::free()
{
	if(mTexture != NULL){	
		SDL_DestroyTexture(mTexture);
		mTexture = NULL;
		mWidth = 0;
		mHeight= 0;
	}

	if(shadowTexture != NULL)
		SDL_DestroyTexture(shadowTexture);

	TTF_CloseFont(gFont);
}


void Texture::move(){
	xPos -= speed;
}

bool Texture::hasText(){
	if(!text.empty()){
		return true;
	}
	else{
		return false;
	}
}


int Texture::length(){
	return text.length();
}

double Texture::getWidth(){
	return mWidth;
}

double Texture::getHeight(){
	return mHeight;
}

std::string Texture::getText(){
	return text;
}

void Texture::setFont(TTF_Font *gFont){
	this->gFont = gFont;
}

void Texture::setRenderer(SDL_Renderer* renderer){
	this->renderer = renderer;
}

void Texture::setSpeed(double value){
  this->speed = value;
}

double Texture::getSpeed(){
  return speed;
}

SDL_Renderer* Texture::getRenderer(){
	return renderer;
}

double Texture::getXPos(){
	return xPos;
}

void Texture::setXPos(double x){
	xPos = x;
}

std::string Texture::getOriginalText()
{
	return originalText;
}

void Texture::setOriginalText(std::string originalText)
{
	this->originalText = originalText;
}

