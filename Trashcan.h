#include "Object.h"

#ifndef Trashcan_h
#define Trashcan_h

class Trashcan{
  public:
    Trashcan(SDL_Renderer* renderer){
      object = new Object(0, 1020, 70, 130, TRASHCAN_SPAWN_X, TRASHCAN_SPAWN_Y, renderer);
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
      if(x >= TRASHCAN_SPAWN_X && x <= TRASHCAN_SPAWN_X + 70)
        if(y >= TRASHCAN_SPAWN_Y - 10 && y <= TRASHCAN_SPAWN_Y + 40)
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