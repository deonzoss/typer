#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
//#include <SDL2/SDL_ttf.h>
//#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string>
#include <stdlib.h>
#include <time.h>
#include <math.h>
//#include <iostream>
//#include "Texture.h"
#include "Setup.h"
#include "Game.h"
#include "SdlWindow.h"
#include "Level.h"
//#include "Scoreboard.h"
//#include "Character.h"
//#include "Screen.h"
//#include "TextGenerator.h"

int main(int argc, char* args[])
{
	srand(time(NULL));
	setup();
	SdlWindow* window = new SdlWindow();	
	window->init();	
	Game* newGame = new Game(window->getRenderer());
	newGame->start();

	//	close(window, renderer);

	return 0;
}
