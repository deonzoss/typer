
#include "Object.h"

#ifndef Door_h
#define Door_h

class Door{
  public:
    Door(SDL_Renderer* renderer){
      object = new Object(0, 1020, 70, 130, 1190, 750, renderer);
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
