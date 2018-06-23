#include "Setup.h"
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
      if(animate && (SDL_GetTicks() - animationTime) < 100){
        renderQuad = {CLOCK_SPAWN_X + 4*SCALESIZE, CLOCK_SPAWN_Y  + 1*SCALESIZE, minuteHand.w*SCALESIZE, minuteHand.h*SCALESIZE};
        SDL_RenderCopyEx(renderer, objectTexture, &minuteHand, &renderQuad, minuteHandAngle, NULL, SDL_FLIP_NONE); 
        renderQuad = {CLOCK_SPAWN_X + 4*SCALESIZE, CLOCK_SPAWN_Y + 2*SCALESIZE, hourHand.w*SCALESIZE, hourHand.h*SCALESIZE};
        SDL_RenderCopyEx(renderer, objectTexture, &hourHand, &renderQuad, hourHandAngle, NULL, SDL_FLIP_NONE); 
        
      }
      else{
        if(animate){
          animate = false;
          object->setY(object->getY() - 1*SCALESIZE);
        }
        renderQuad = {CLOCK_SPAWN_X + 4*SCALESIZE, CLOCK_SPAWN_Y, minuteHand.w*SCALESIZE, minuteHand.h*SCALESIZE};
        SDL_RenderCopyEx(renderer, objectTexture, &minuteHand, &renderQuad, minuteHandAngle, NULL, SDL_FLIP_NONE); 
        renderQuad = {CLOCK_SPAWN_X + 4*SCALESIZE, CLOCK_SPAWN_Y + 1*SCALESIZE, hourHand.w*SCALESIZE, hourHand.h*SCALESIZE};
        SDL_RenderCopyEx(renderer, objectTexture, &hourHand, &renderQuad, hourHandAngle, NULL, SDL_FLIP_NONE); 
      }
    
      if(!levelStarted){ 
        if(minuteHandAngle > 360){
          minuteHandAngle = 0;
        }
        else{
          minuteHandAngle+= ((.01*SCALESIZE)/speed); 
        }
        if(hourHandAngle > 360){
          hourHandAngle = 0;
        }
        else{
          hourHandAngle+= ((.01*SCALESIZE)/speed)/12; 
        }
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

    void setMinuteHandAngle(double value){
      minuteHandAngle = value;
    }
    
    void setHourHandAngle(double value){
      hourHandAngle = value;
    }
    
    double getHourHandAngle(){
      return hourHandAngle;
    }

    void setLevelStarted(bool value){
      levelStarted = value;
    }

    void setAnimate(bool value){
      if(animate == false){
        object->setY(object->getY() + 1*SCALESIZE);
      }
      animate = value;
      animationTime = SDL_GetTicks();
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
    bool levelStarted = false;
    bool animate = false;
    Uint32 animationTime;

};

#endif
