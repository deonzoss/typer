
#include "Object.h"

#ifndef Clock_h
#define Clock_h

class Clock{
  public:
    Clock(SDL_Renderer* renderer){
      object = new Object(0, 640, 100, 100, CLOCK_SPAWN_X, CLOCK_SPAWN_Y, renderer);
      this->renderer = renderer;
    }

    void render(){
      object->render();
    }
    
    void animate(){

    }

    void setObjectTexture(SDL_Texture* texture){
      this->objectTexture = texture;
      object->setObjectTexture(texture);
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
    SDL_Rect renderQuad;
};

#endif
