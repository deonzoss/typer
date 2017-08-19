
#include "Object.h"

#ifndef Door_h
#define Door_h

class Door{
  public:
    Door(SDL_Renderer* renderer){
      object = new Object(1090, 840, 40, 20, 430, 730, renderer);
      this->renderer = renderer;
      windowWorkers[0].x = 460;
      windowWorkers[0].y = 1140;
      windowWorkers[0].w = 540;
      windowWorkers[0].h = 130;
     
      windowWorkers[1].x = 460;
      windowWorkers[1].y = 1270;
      windowWorkers[1].w = 540;
      windowWorkers[1].h = 130;
      
      windowWorker[0].x = 460;
      windowWorker[0].y = 980;
      windowWorker[0].w = 60;
      windowWorker[0].h = 160;
     
      windowWorker[1].x = 530;
      windowWorker[1].y = 980;
      windowWorker[1].w = 60;
      windowWorker[1].h = 160;
      
      windowWorkerArm.x = 520;
      windowWorkerArm.y = 1030;
      windowWorkerArm.w = 10;
      windowWorkerArm.h = 60;
    }

    void render(){
      if(animate && ((SDL_GetTicks()-handleLifetime) > LETTER_LIFETIME)){
        animate = false;
        windowWorkersIndex = 0;
        windowWorkerIndex = 0; 
        object->setY(730);
      }

      renderQuad = {WINDOW_WORKER_X,WINDOW_WORKER_Y, windowWorker[0].w, windowWorker[0].h};
      SDL_RenderCopy(renderer, objectTexture, &windowWorker[windowWorkerIndex], &renderQuad); 
      
      if(windowWorkerIndex){ 
        renderQuad = {WINDOW_WORKER_X + 60, WINDOW_WORKER_Y + 50, windowWorkerArm.w, windowWorkerArm.h};
        SDL_RenderCopy(renderer, objectTexture, &windowWorkerArm, &renderQuad); 
      }
      else{
        renderQuad = {WINDOW_WORKER_X + 50, WINDOW_WORKER_Y + 50, windowWorkerArm.w, windowWorkerArm.h};
        SDL_RenderCopy(renderer, objectTexture, &windowWorkerArm, &renderQuad); 
      }
      
      renderQuad = {WINDOW_WORKERS_X, WINDOW_WORKERS_Y, windowWorkers[0].w, windowWorkers[0].h};
      SDL_RenderCopy(renderer, objectTexture, &windowWorkers[windowWorkersIndex], &renderQuad); 
      
      
      object->render();
    }
    
    void setObjectTexture(SDL_Texture* texture){
      this->objectTexture = texture;
      object->setObjectTexture(texture);
    }

    void setAnimate(bool value){
      animate = value;
      if(animate){
        windowWorkersIndex = 1;
        windowWorkerIndex = 1;
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
    SDL_Rect windowWorkers[2]; 
    SDL_Rect windowWorker[2]; 
    SDL_Rect windowWorkerArm; 
    Uint32 handleLifetime; 
    bool animate = false;
    int windowWorkersIndex = 0;
    int windowWorkerIndex = 0;
};

#endif
