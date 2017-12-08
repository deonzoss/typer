#include <SDL2/SDL.h>
#include <stdio.h>
#include <string>
#include <sstream>
#include "SdlWindow.h"
#include "Setup.h"


SdlWindow::SdlWindow()
{
	window = NULL;
	renderer = NULL;

	mouseFocus = false;
	keyboardFocus = false;
	fullScreen = false;
	shown = false;
	windowID = -1;

	width = 0;
	height = 0;
}

bool SdlWindow::init()
{
	window = SDL_CreateWindow("typer", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);

	if(window){
		mouseFocus = true;
		keyboardFocus = true;
		width = SCREEN_WIDTH;
		height = SCREEN_HEIGHT;

		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
		if(!renderer){
			printf("SDL Error: %s\n", SDL_GetError());
			SDL_DestroyWindow(window);
			window = NULL;
		}
		else{
			SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
		  SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "0");	
      windowID = SDL_GetWindowID(window);
			shown = true;
		}
	}
	else{
		printf("SDL Error: %s\n", SDL_GetError());
	}

	return window != NULL && renderer != NULL;
}

void SdlWindow::handleEvent(SDL_Event& e)
{
	if(e.type == SDL_WINDOWEVENT && e.window.windowID == windowID){

		switch(e.window.event)
		{

			case SDL_WINDOWEVENT_SHOWN:
				shown = true;
				break;

			case SDL_WINDOWEVENT_HIDDEN:
				shown = false;
				break;

			case SDL_WINDOWEVENT_SIZE_CHANGED:
				width = e.window.data1;
				height = e.window.data2;
				SDL_RenderPresent(renderer);
				break;

			case SDL_WINDOWEVENT_EXPOSED:
				SDL_RenderPresent(renderer);
				break;

			case SDL_WINDOWEVENT_ENTER:
				mouseFocus = true;
				break;

			case SDL_WINDOWEVENT_LEAVE:
				mouseFocus = true;
				break;

			case SDL_WINDOWEVENT_FOCUS_GAINED:
				keyboardFocus = true;
				break;

			case SDL_WINDOWEVENT_FOCUS_LOST:
				keyboardFocus = false;
				break;

			case SDL_WINDOWEVENT_MINIMIZED:
				minimized = true;
				break;

			case SDL_WINDOWEVENT_MAXIMIZED:
				minimized = false;
				break;

			case SDL_WINDOWEVENT_RESTORED:
				minimized = false;
				break;

			case SDL_WINDOWEVENT_CLOSE:
				SDL_HideWindow(window);
				break;
		}

	}
}

void SdlWindow::focus()
{
	if(!shown){
		SDL_ShowWindow(window);
	}

	SDL_RaiseWindow(window);
}


void SdlWindow::render()
{
	if( !minimized )
	{	
	
	}
}

void SdlWindow::free()
{
	if( window != NULL )
	{
		SDL_DestroyWindow( window );
	}

	mouseFocus = false;
	keyboardFocus = false;
	width = 0;
	height = 0;
}

double SdlWindow::getWidth()
{
	return width;
}

double SdlWindow::getHeight()
{
	return height;
}

bool SdlWindow::hasMouseFocus()
{
	return mouseFocus;
}

bool SdlWindow::hasKeyboardFocus()
{
	return keyboardFocus;
}

bool SdlWindow::isMinimized()
{
	return minimized;
}

bool SdlWindow::isShown()
{
	return shown;
}

SDL_Window* SdlWindow::getWindow(){
	return window;
}

SDL_Renderer* SdlWindow::getRenderer(){
	return renderer;
}
