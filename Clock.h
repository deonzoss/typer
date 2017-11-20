
#include "Object.h"

#ifndef Clock_h
#define Clock_h

class Clock{
  public:
    Clock(SDL_Renderer* renderer){
      object = new Object(0, 64, 10, 10, CLOCK_SPAWN_X, CLOCK_SPAWN_Y, renderer);
      this->renderer = renderer;
      
      minuteHand.x = 10;
      minuteHand.y = 68;
      minuteHand.w = 1;
      minuteHand.h = 9;

      hourHand.x = 11;
      hourHand.y = 68;
      hourHand.w = 1;
      hourHand.h = 7;

    }

    void render(){
      object->render();
      renderQuad = {CLOCK_SPAWN_X + 4*SCALESIZE, CLOCK_SPAWN_Y, minuteHand.w*SCALESIZE, minuteHand.h*SCALESIZE};
      SDL_RenderCopyEx(renderer, objectTexture, &minuteHand, &renderQuad, minuteHandAngle, NULL, SDL_FLIP_NONE); 
      renderQuad = {CLOCK_SPAWN_X + 4*SCALESIZE, CLOCK_SPAWN_Y + 1*SCALESIZE, hourHand.w*SCALESIZE, hourHand.h*SCALESIZE};
      SDL_RenderCopyEx(renderer, objectTexture, &hourHand, &renderQuad, hourHandAngle, NULL, SDL_FLIP_NONE); 
      if(minuteHandAngle > 360){
        minuteHandAngle = 0;
      }
      else{
        minuteHandAngle+= (.12*SCALESIZE)/speed;
      }
      if(hourHandAngle > 360){
        hourHandAngle = 0;
      }
      else{
        hourHandAngle += (.012*SCALESIZE)/speed; 
      }
    }

    void setObjectTexture(SDL_Texture* texture){
      this->objectTexture = texture;
      object->setObjectTexture(texture);
    }

    void setSpeed(double value){
      this->speed = value;
    }

    double getSpeed(){
      return speed;
    }
    
    bool collisionCheck(double x, double y){
      if(x >= CLOCK_SPAWN_X && x <= CLOCK_SPAWN_X + 10*SCALESIZE)
        if(y >= CLOCK_SPAWN_Y - 1*SCALESIZE && y <= CLOCK_SPAWN_Y + 10*SCALESIZE)
          return true; 
      return false;
    }

  private:
    Object* object;
    SDL_Renderer* renderer = NULL;
    SDL_Texture* objectTexture; 
    SDL_Rect objectClip;
    SDL_Rect minuteHand;
    SDL_Rect hourHand; 
    SDL_Rect renderQuad;
    double minuteHandAngle = 0;
    double hourHandAngle = 0;
    double speed = 1;
};

#endif
