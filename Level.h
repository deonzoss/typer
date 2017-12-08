#include <SDL2/SDL.h>
#include "Setup.h"
#include <SDL2/SDL_ttf.h>
#ifndef level_h
#define level_h

class Level
{
	public:
		Level(int rate, double speed, int num, SDL_Renderer* renderer);
		~Level();
    void free();
		int getWordRate();
		double getSpeed();	
    int getLifetime();
    void setLevelNum(int value);
    int getLevelNum();
    void loadFont(double fontsize);
    void loadFromRenderedText();
    void render();
	  int getRand();
	private:
    SDL_Renderer* renderer = NULL;
    SDL_Texture* levelTexture = NULL;
    SDL_Texture* shadowTexture = NULL;
    TTF_Font* font;
    double width = 0;
    double height = 0;
    double shadowWidth = 0;
    double shadowHeight= 0;
    double xPos = 10*SCALESIZE;
    double yPos = 10*SCALESIZE;
    int shadowOffset = .5*SCALESIZE;
    double fontSize = 10*SCALESIZE; 
    char levelString[30];
		int wordRate;
		double masterSpeed;
    int levelNumber = 0;
    int levelLifetime = 0;
    bool incSpeed = false;
    bool incRate = false;
};


#endif


