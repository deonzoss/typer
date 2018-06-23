#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include "Setup.h"
#include "Letter.h"
#include "TextGenerator.h"
#include "Scoreboard.h"
#include "Character.h"
#include "Coworker.h"
#include "Boss.h"
#include "GameScreen.h"
#include "Level.h"
#include "Object.h"
#include "Mouse.h"
#include "Trashcan.h"
#include "Fountain.h"
#include "Clock.h"
#include "Door.h"
#include "Menu.h"
#include "Scorer.h"
#include "Trophy.h"
#include "TrophyFactory.h"
#include "Cabinet.h"
#include <vector>
#include <iostream>
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

        void loadSounds();

        void explodeTextVector();
        
        void displayDynamicLetters();       

        void displayScoreVector();

        void eventHandler();

        void processInput(char input);

        void collisionHandler(double x, double y);

        void setupTrophies();

        void dropTrophy();

        void slowDown();

        void speedUp();

        void newLevel();

        void showDemo(){
          showDemoBool = true;
        }

        void quitDemo(){
          showDemoBool = false;
        }

        bool getDemoBool(){
          return showDemoBool;
        }

        SDL_Texture* loadBackground();	

        SDL_Texture* loadAnimationSheet();

        void start();

        void playDemo();

    private:
      Menu* mainMenu; 
      Scoreboard* scoreboard;	
      SDL_Renderer* renderer;
      SDL_Rect slowRect = {0,0,SCREEN_WIDTH, SCREEN_HEIGHT}; 
      int slowRectAlpha = 0; 
      std::vector<Texture*> textVector;
      std::vector<Letter*> letterVector;	
      std::vector<Scorer*> scoreVector; 
      std::vector<Trophy*> trophyList;
      TrophyFactory* trophyFactory;
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
      GameScreen* screen = NULL;
      Trashcan* trashcan = NULL;
      Cabinet* cabinet = NULL;
      Object* desk = NULL;
      Fountain* fountain = NULL;
      Clock* clock = NULL;
      Door* door = NULL; 
      int levelNum = 1;
      Uint32 levelTime = 0;
      Uint32 trophyTime = 0;
      Uint32 soundTime = 0;
      Uint32 demoTypeTime = 0;
      bool demoWordTyped = false;
      int demoCurrentWord = 0;
      int trophyDropIndex = 0;
      bool startLevel = false;
      bool quitLevel = false; 
      bool screenDropped = false;
      bool screenRaised = false;	
      bool pauseLevel = false;
      bool renderLevelDisplay = false;
      bool showDemoBool = true;
      int typeSpeedLimit = 100;
      double scrollSpeed;
      double wordRate;
      int strikes = 0;
      Mix_Chunk *pop1 = NULL;
      Mix_Chunk *pop2 = NULL;
      Mix_Chunk *pop3 = NULL;
      Mix_Chunk *pop4 = NULL;
      Mix_Chunk *pop5 = NULL;
      Mix_Chunk *pop6 = NULL;
      Mix_Chunk *hit1 = NULL;
      Mix_Chunk *hit2 = NULL;
      Mix_Chunk *hit3 = NULL;
      Mix_Chunk *hit4 = NULL;
      Mix_Chunk *hit5 = NULL;
      Mix_Chunk *hit6 = NULL;
      Mix_Chunk *hit7 = NULL;
      Mix_Chunk *hit8 = NULL;
      Mix_Chunk *hit9 = NULL;
      Mix_Chunk *hit10 = NULL;
      Mix_Chunk *startLetterSound = NULL;
      Mix_Chunk *backgroundPrinter = NULL;
      Mix_Chunk *backgroundRandom = NULL;
      Mix_Chunk *flagSound = NULL;
      Mix_Chunk *pauseSound = NULL;
      Mix_Chunk *levelUpSound = NULL;
      Mix_Chunk *trophySound = NULL;
      Mix_Chunk *screenSlideSound = NULL;
      Mix_Chunk *invalidSound = NULL;
      Mix_Chunk *groundSound = NULL;
      Mix_Chunk *screenSound = NULL;
      Mix_Chunk *screenSoundReverse = NULL;
      Mix_Chunk *allLettersPop = NULL;
      Mix_Music *gameplayMusic = NULL;


};

#endif
