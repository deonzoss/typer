#include <SDL2/SDL.h>
#include <stdio.h>
#include <string>
#include <sstream>
#include "Window.h"
#include "Setup.h"

Window::Window()
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

bool Window::init()
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

void Window::handleEvent(SDL_Event& e)
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

void Window::focus()
{
	if(!shown){
		SDL_ShowWindow(window);
	}

	SDL_RaiseWindow(window);
}


void Window::render()
{
	if( !minimized )
	{	
	
	}
}

void Window::free()
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

double Window::getWidth()
{
	return width;
}

double Window::getHeight()
{
	return height;
}

bool Window::hasMouseFocus()
{
	return mouseFocus;
}

bool Window::hasKeyboardFocus()
{
	return keyboardFocus;
}

bool Window::isMinimized()
{
	return minimized;
}

bool Window::isShown()
{
	return shown;
}

SDL_Window* Window::getWindow(){
	return window;
}

SDL_Renderer* Window::getRenderer(){
	return renderer;
}
