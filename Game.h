#include <SDL2/SDL_image.h>
#include "Setup.h"
#include "Letter.h"
#include "TextGenerator.h"
#include "Scoreboard.h"
#include "Character.h"
#include "Coworker.h"
#include "Boss.h"
#include "Screen.h"
#include "Level.h"
#include "Object.h"
#include "Trashcan.h"
#include "Fountain.h"
#include "Clock.h"
#include "Door.h"
#include "Menu.h"
#include "Scorer.h"
#include <vector>
#ifndef Game_h
#define Game_h


class Game
{
    public:
        Game(SDL_Renderer* renderer);
        
        ~Game();

        std::vector<Texture*> makeTextVector();

        std::vector<Texture*> populateTextVector();
        
        void displayTextVector();
        
        void displayLetterVector();	
        
        void displayDynamicLetters();       

        void displayScoreVector();

        void eventHandler();

        void processInput(char input);

        void collisionHandler();

        void slowDown();

        void speedUp();

        Level* newLevel(int levelNum);	

        SDL_Texture* loadBackground();	

        SDL_Texture* loadAnimationSheet();

        void start();

    private:
      Menu* mainMenu; 
      Scoreboard* scoreboard;	
      SDL_Renderer* renderer;
      SDL_Rect slowRect = {0,0,SCREEN_WIDTH, SCREEN_HEIGHT}; 
      int slowRectAlpha = 0; 
      std::vector<Texture*> textVector;
      std::vector<Letter*> letterVector;	
      std::vector<Scorer*> scoreVector; 
      std::string startWord = "START"; 
      bool quit;
      SDL_Event event;
      TextGenerator* textGenerator;
      Level* currentLevel;
      SDL_Texture* background = NULL;
      SDL_Texture* animationSheet = NULL;
      int delaySpeed = 0;
      bool slowTime = false;
      Character* mainCharacter = NULL;
      Coworker* worker = NULL; 
      Boss* boss = NULL; 
      Screen* screen = NULL;
      Trashcan* trashcan = NULL;
      Object* desk = NULL;
      Fountain* fountain = NULL;
      Clock* clock = NULL;
      Door* door = NULL; 
      bool startLevel = false;
      bool quitLevel = false; 
      bool screenDropped = false;
      bool screenRaised = false;	
      bool pauseLevel = false;
      int strikes = 0;
};

#endif
