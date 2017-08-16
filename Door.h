
#include "Object.h"

#ifndef Door_h
#define Door_h

class Door{
  public:
    Door(SDL_Renderer* renderer){
      object = new Object(1090, 840, 40, 20, 430, 730, renderer);
      this->renderer = renderer;
    }

    void render(){
      if(animate && ((SDL_GetTicks()-handleLifetime) > LETTER_LIFETIME)){
        animate = false;
        object->setY(730);
      } 
      object->render();
    }
    
    void setObjectTexture(SDL_Texture* texture){
      this->objectTexture = texture;
      object->setObjectTexture(texture);
    }

    void setAnimate(bool value){
      animate = value;
      if(animate){
        handleLifetime = SDL_GetTicks(); 
        object->setY(740); 
      }
    }

    bool collisionCheck(int x, int y){
      if(x>= 420 && x <= 460){
        if(y >= 710 && y <= 760){
          return true;
        }
      } 
      return false;
    }

  private:
    Object* object;
    SDL_Renderer* renderer = NULL;
    SDL_Texture* objectTexture; 
    SDL_Rect objectClip;
    SDL_Rect renderQuad;
    Uint32 handleLifetime; 
    bool animate = false;
};

#endif
