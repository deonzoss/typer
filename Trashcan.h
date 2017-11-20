#include "Object.h"

#ifndef Trashcan_h
#define Trashcan_h

class Trashcan{
  public:
    Trashcan(SDL_Renderer* renderer){
      object = new Object(0, 102, 7, 13, TRASHCAN_SPAWN_X, TRASHCAN_SPAWN_Y, renderer);
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

    bool collisionCheck(double x, double y){
      if(x >= TRASHCAN_SPAWN_X && x <= TRASHCAN_SPAWN_X + 7*SCALESIZE)
        if(y >= TRASHCAN_SPAWN_Y - 1*SCALESIZE && y <= TRASHCAN_SPAWN_Y + 4*SCALESIZE)
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
