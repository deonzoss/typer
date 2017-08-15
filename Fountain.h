#include "Object.h"

#ifndef Fountain_h
#define Fountain_h

class Fountain{
  public:
    Fountain(SDL_Renderer* renderer){
      object = new Object(0, 1150, 100, 300, FOUNTAIN_SPAWN_X,FOUNTAIN_SPAWN_Y, renderer);
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

    bool collisionCheck(){
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
