//TrophyFactory.h
#include "Trophy.h"
#include "Setup.h"

class TrophyFactory
{
  public:
    TrophyFactory(SDL_Renderer* renderer){
      this->renderer = renderer;
      for(int i = 0; i < 50; i++){
        trophyPlaced[i]=false;
      }
    }

    Trophy* makeTrophy(int trophyType){
      determinePosition();
      determineTrophy(trophyType);

      Trophy* trophy = new Trophy(renderer,xPos, yPos, animationSheetXPos, animationSheetYPos, origTrophyWidth, origTrophyHeight, destination);
      trophyIndex++;
      return trophy;
    }

    void determineTrophy(int trophyType){
      int randNum1 = rand()%2;
      int randNum2;

      if(randNum1){
        randNum2 = rand()%13;
        animationSheetXPos=randNum2*origTrophyWidth;
        animationSheetYPos=198;
      }
      else{
        randNum2 = rand()%12;
        animationSheetXPos=randNum2*origTrophyWidth;
        animationSheetYPos=198+origTrophyHeight;
      }
    }

    void determinePosition()
    {
      if(trophyIndex < 9){
        while(trophyPlaced[randNum]){
          randNum = rand()%9;
        }
        xPos = TROPHY_SPAWN_X+0*(TROPHY_WIDTH+.5*SCALESIZE)+(TROPHY_WIDTH+.5*SCALESIZE)*randNum;
        yPos = -11.25*SCALESIZE;
        destination = (MAIN_CHARACTER_DESK_SPAWN_Y - TROPHY_HEIGHT); 
        //yPos= (MAIN_CHARACTER_DESK_SPAWN_Y - TROPHY_HEIGHT); 
        trophyPlaced[randNum] = true;
      }
      else if(trophyIndex < 16){
        randNum = rand()%7;
        while(trophyPlaced[9+randNum]){
          randNum = rand()%7;
        }
        xPos = TROPHY_SPAWN_X+1*((TROPHY_WIDTH+.5*SCALESIZE))+(TROPHY_WIDTH+.5*SCALESIZE)*randNum;
        yPos = -14.5*SCALESIZE;
        destination = (MAIN_CHARACTER_DESK_SPAWN_Y - 2*TROPHY_HEIGHT); 
        //yPos= (MAIN_CHARACTER_DESK_SPAWN_Y - 2*TROPHY_HEIGHT); 
        trophyPlaced[9+randNum] = true;
      }
      else if(trophyIndex < 21){
        randNum = rand()%5;
        while(trophyPlaced[16+randNum]){
          randNum = rand()%5;
        }
        xPos = TROPHY_SPAWN_X+2*((TROPHY_WIDTH+.5*SCALESIZE))+(TROPHY_WIDTH+.5*SCALESIZE)*randNum;
        yPos = -17.75*SCALESIZE;
        destination = (MAIN_CHARACTER_DESK_SPAWN_Y - 3*TROPHY_HEIGHT); 
        //yPos= (MAIN_CHARACTER_DESK_SPAWN_Y - 3*TROPHY_HEIGHT); 
        trophyPlaced[16+randNum] = true;
      }
      else if(trophyIndex < 24){
        randNum = rand()%3;
        while(trophyPlaced[21+randNum]){
          randNum = rand()%3;
        }
        xPos = TROPHY_SPAWN_X+3*((TROPHY_WIDTH+.5*SCALESIZE))+(TROPHY_WIDTH+.5*SCALESIZE)*randNum;
        yPos = -21*SCALESIZE;
        destination = (MAIN_CHARACTER_DESK_SPAWN_Y - 4*TROPHY_HEIGHT); 
        //yPos= (MAIN_CHARACTER_DESK_SPAWN_Y - 4*TROPHY_HEIGHT); 
        trophyPlaced[21+randNum] = true;
      }
      else if(trophyIndex == 24){
        randNum = 0;
        xPos = TROPHY_SPAWN_X+4*((TROPHY_WIDTH+.5*SCALESIZE))+(TROPHY_WIDTH+.5*SCALESIZE)*randNum;
        yPos = -24.25*SCALESIZE;
        destination = (MAIN_CHARACTER_DESK_SPAWN_Y - 5*TROPHY_HEIGHT); 
        //yPos= (MAIN_CHARACTER_DESK_SPAWN_Y - 7*TROPHY_HEIGHT); 
        trophyPlaced[24] = true;
      }

    }
    
  private:
    SDL_Renderer* renderer;
    int trophyIndex = 0;
    int origTrophyWidth = 10;
    int origTrophyHeight = 13;
    int randNum = 0;
    double xPos = 0;
    double yPos = 0;
    int animationSheetXPos = 0;
    int animationSheetYPos = 0;
    bool trophyPlaced[50];
    double destination = 0;
};
