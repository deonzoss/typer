#include <stdio.h>
#include <SDL2/SDL.h>
#include <string>
#include <vector>
#include "Texture.h"


#ifndef TextGenerator_h
#define TextGenerator_h

class TextGenerator{

	public:
		TextGenerator(SDL_Renderer* renderer);

		~TextGenerator();

		std::string create();

		void readFile(std::string filename);
	private:
		std::vector<std::string> stringVector;
		int rand;
		SDL_Renderer* renderer;
		FILE* file;
};

#endif
