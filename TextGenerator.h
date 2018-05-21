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

    void setType(std::vector<int> levelType);
	private:
		std::vector<std::string> stringVector;
    std::vector<int> levelType;
		int rand;
		SDL_Renderer* renderer;
		FILE* file;
};

#endif
