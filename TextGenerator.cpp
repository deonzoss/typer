#include <stdio.h>
#include<SDL2/SDL.h>
#include<SDL2/SDL_ttf.h>
#include "TextGenerator.h"
#include "Setup.h"
#include <stdlib.h>
#include <time.h>


TextGenerator::TextGenerator(SDL_Renderer* renderer)
{
	rand = 0;
	this->renderer = renderer;
	readFile("samples/bashcommands.txt");	
}


std::string TextGenerator::create(){
	std::string text = stringVector[rand];	
	if(rand == stringVector.size()-1){
		rand = 0;
	}
	else{
		rand++;
	}	
	return text;
}

void TextGenerator::readFile(std::string filename){
	
	int i = 0;	
	file = fopen(filename.c_str(), "r");
	if(!file){
		printf("Error reading from file.\n");
		return;
	}
		
	char* line = (char*)malloc(sizeof(char)*MAX_TEXT_LENGTH);	
	while(fgets(line, MAX_TEXT_LENGTH, file)!=NULL){	
		if(feof(file)){
			return;
		}
		std::string str(line);	
		if(str.length() > 1){	
			str.pop_back();	
			stringVector.push_back(str);
			i++;
		}	
	}

}
