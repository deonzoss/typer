
#include "Object.h"

#ifndef Door_h
#define Door_h

class Door{
  public:
    Door(SDL_Renderer* renderer){
      object = new Object(109*SCALESIZE, 84*SCALESIZE, 4*SCALESIZE, 2*SCALESIZE, 43*SCALESIZE, 73*SCALESIZE, renderer);
      this->renderer = renderer;
      windowWorkers[0].x = 46*SCALESIZE;
      windowWorkers[0].y = 114*SCALESIZE;
      windowWorkers[0].w = 54*SCALESIZE;
      windowWorkers[0].h = 13*SCALESIZE;
     
      windowWorkers[1].x = 46*SCALESIZE;
      windowWorkers[1].y = 127*SCALESIZE;
      windowWorkers[1].w = 54*SCALESIZE;
      windowWorkers[1].h = 13*SCALESIZE;
      
      windowWorker[0].x = 46*SCALESIZE;
      windowWorker[0].y = 98*SCALESIZE;
      windowWorker[0].w = 6*SCALESIZE;
      windowWorker[0].h = 16*SCALESIZE;
     
      windowWorker[1].x = 54*SCALESIZE;
      windowWorker[1].y = 98*SCALESIZE;
      windowWorker[1].w = 6*SCALESIZE;
      windowWorker[1].h = 16*SCALESIZE;
      
      windowWorkerArm.x = 52*SCALESIZE;
      windowWorkerArm.y = 98*SCALESIZE;
      windowWorkerArm.w = 2*SCALESIZE;
      windowWorkerArm.h = 12*SCALESIZE;
    }

    void render(){
      if(animate && ((SDL_GetTicks()-handleLifetime) > LETTER_LIFETIME)){
        animate = false;
        windowWorkersIndex = 0;
        windowWorkerIndex = 0; 
        object->setY(73*SCALESIZE);
      }

      
      if(windowWorkerIndex){ 
        renderQuad = {WINDOW_WORKER_X + 4*SCALESIZE, WINDOW_WORKER_Y, windowWorkerArm.w, windowWorkerArm.h};
        SDL_RenderCopy(renderer, objectTexture, &windowWorkerArm, &renderQuad);
        angle = 0;
        raiseArm = false; 
      }
      else{
        renderQuad = {WINDOW_WORKER_X + 4*SCALESIZE, WINDOW_WORKER_Y, windowWorkerArm.w, windowWorkerArm.h};
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
        object->setY(74*SCALESIZE); 
      }
    }

    bool collisionCheck(double x, double y){
      if(x>= 42*SCALESIZE && x <= 46*SCALESIZE){
        if(y >= 71*SCALESIZE && y <= 76*SCALESIZE){
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
