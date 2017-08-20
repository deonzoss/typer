
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
     
      windowWorker[1].x = 540;
      windowWorker[1].y = 980;
      windowWorker[1].w = 60;
      windowWorker[1].h = 160;
      
      windowWorkerArm.x = 520;
      windowWorkerArm.y = 980;
      windowWorkerArm.w = 20;
      windowWorkerArm.h = 120;
    }

    void render(){
      if(animate && ((SDL_GetTicks()-handleLifetime) > LETTER_LIFETIME)){
        animate = false;
        windowWorkersIndex = 0;
        windowWorkerIndex = 0; 
        object->setY(730);
      }

      
      if(windowWorkerIndex){ 
        renderQuad = {WINDOW_WORKER_X + 40, WINDOW_WORKER_Y, windowWorkerArm.w, windowWorkerArm.h};
        SDL_RenderCopy(renderer, objectTexture, &windowWorkerArm, &renderQuad);
        angle = 0;
        raiseArm = false; 
      }
      else{
        renderQuad = {WINDOW_WORKER_X + 40, WINDOW_WORKER_Y, windowWorkerArm.w, windowWorkerArm.h};
        SDL_RenderCopyEx(renderer, objectTexture, &windowWorkerArm, &renderQuad, angle, NULL, SDL_FLIP_NONE); 
      }
      
      renderQuad = {WINDOW_WORKER_X,WINDOW_WORKER_Y, windowWorker[0].w, windowWorker[0].h};
      SDL_RenderCopy(renderer, objectTexture, &windowWorker[windowWorkerIndex], &renderQuad); 
      
      renderQuad = {WINDOW_WORKERS_X, WINDOW_WORKERS_Y, windowWorkers[0].w, windowWorkers[0].h};
      SDL_RenderCopy(renderer, objectTexture, &windowWorkers[windowWorkersIndex], &renderQuad); 
       
      if(raiseArm){
        if(angle >= randValue){
          angle-=10/speed;
        } 
        else if(SDL_GetTicks() - armTime > 2000*speed){
          raiseArm = false;
        }
      }
      else{
        if(angle < 0){
          angle+=10/speed;
        }
        else{
          randValue = -45 - (rand()%90); 
          raiseArm = true; 
          armTime = SDL_GetTicks();
        }
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

    void setSpeed(double value){
      speed = value;
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
    int angle = 0;
    bool raiseArm = false;
    Uint32 armTime;
    int randValue;
    double speed = 1;
};

#endif
