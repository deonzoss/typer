//Trophy.h
#include "Object.h"
//#include "Setup.h"

#ifndef Trophy_h
#define Trophy_h

class Trophy
{
  public:
    Trophy(SDL_Renderer* renderer,double spawnXPos, double spawnYPos, int xPos, int yPos, int width, int height, double destination){
      this->renderer = renderer;
      setupClip(xPos, yPos, width, height);
      this->spawnXPos = spawnXPos;
      this->spawnYPos = spawnYPos;
      this->destination = destination;
      randNum = rand()%3;
    }

    ~Trophy(){

    }

    void free(){

    }

    void render(){
      SDL_Rect renderQuad = {spawnXPos, spawnYPos, TROPHY_WIDTH, TROPHY_HEIGHT};
      SDL_RenderCopyEx(renderer, objectTexture, &trophyClip, &renderQuad, angle, NULL, SDL_FLIP_NONE);
      if(angle == 360){
        angle = 0;
      }
      if(!bounce && drop){
        spawnYPos+=.7*SCALESIZE;
        angle+=6+(randNum*6);
        collisionCheck();
      }
      else if(bounce && drop){
        spawnYPos+=.7*SCALESIZE;
        collisionCheck();
      }
      else if(bounce){
        if(spawnYPos > destination-(.5*SCALESIZE)){
          spawnYPos-=.1*SCALESIZE;
        }
        else{
          drop = true;
        }
      }

    }

    void collisionCheck(){
      if(spawnYPos >= destination){
        spawnYPos = destination+.1*SCALESIZE;
        if(!bounce){
          bounce = true;
        }
        else{
          bounce = false;
        }
        drop = false;
      }
      /*if(spawnYPos < 0-(4*SCALESIZE/4.)){
          if(angle == 0){
            printf("%lf\n", spawnYPos);
            drop = false;
          }
      }*/

    }
    
    void setupClip(int xPos, int yPos, int width, int height)
    {
      trophyClip.x = xPos;
      trophyClip.y = yPos;
      trophyClip.w = width;
      trophyClip.h = height;
    }

    void setObjectTexture(SDL_Texture* texture){
      this->objectTexture = texture;
    }

    void freeze(){
      frozen = true;
    }

    void unfreeze(){
      frozen = false;
    }

    bool getFrozen(){
      return frozen;
    }

    double getSpeed(){
      return speed;
    }

    void setSpeed(double value){
      speed = value;
    }

    void setDrop(bool value){
      drop = value;
    }
    bool getDrop(){
      return drop;
    }

  private:
    SDL_Texture* objectTexture = NULL;
    SDL_Renderer* renderer = NULL;
    SDL_Rect trophyClip;
    bool frozen = false;
    double spawnXPos;
    double spawnYPos;
    double speed = 1;
    double angle = 360;
    bool drop = false;
    bool bounce = false;
    double destination = 0;
    int randNum;
};

#endif
