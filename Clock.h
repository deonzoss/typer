
#include "Object.h"

#ifndef Clock_h
#define Clock_h

class Clock{
  public:
    Clock(SDL_Renderer* renderer){
      object = new Object(0, 640, 100, 100, CLOCK_SPAWN_X, CLOCK_SPAWN_Y, renderer);
      this->renderer = renderer;
      
      minuteHand.x = 100;
      minuteHand.y = 680;
      minuteHand.w = 10;
      minuteHand.h = 90;

      hourHand.x = 110;
      hourHand.y = 680;
      hourHand.w = 10;
      hourHand.h = 70;

    }

    void render(){
      object->render();
      renderQuad = {CLOCK_SPAWN_X + 40, CLOCK_SPAWN_Y, minuteHand.w, minuteHand.h};
      SDL_RenderCopyEx(renderer, objectTexture, &minuteHand, &renderQuad, minuteHandAngle, NULL, SDL_FLIP_NONE); 
      renderQuad = {CLOCK_SPAWN_X + 40, CLOCK_SPAWN_Y + 10, hourHand.w, hourHand.h};
      SDL_RenderCopyEx(renderer, objectTexture, &hourHand, &renderQuad, hourHandAngle, NULL, SDL_FLIP_NONE); 
      if(minuteHandAngle > 360){
        minuteHandAngle = 0;
      }
      else{
        minuteHandAngle+= 1.2/speed;
      }
      if(hourHandAngle > 360){
        hourHandAngle = 0;
      }
      else{
        hourHandAngle += .12/speed; 
      }
    }
    
    void animate(){

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
    
    bool collisionCheck(int x, int y){
      if(x >= CLOCK_SPAWN_X && x <= CLOCK_SPAWN_X + 100)
        if(y >= CLOCK_SPAWN_Y - 10 && y <= CLOCK_SPAWN_Y + 100)
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
