
#include "Object.h"

#ifndef Door_h
#define Door_h

class Door{
  public:
    Door(SDL_Renderer* renderer){
      object = new Object(109, 84, 4, 2, OFFSET + 44*SCALESIZE, 73*SCALESIZE, renderer);
      this->renderer = renderer;
      windowWorkers[0].x = 46;
      windowWorkers[0].y = 114;
      windowWorkers[0].w = 54;
      windowWorkers[0].h = 13;
     
      windowWorkers[1].x = 46;
      windowWorkers[1].y = 127;
      windowWorkers[1].w = 54;
      windowWorkers[1].h = 13;
      
      windowWorker[0].x = 46;
      windowWorker[0].y = 98;
      windowWorker[0].w = 6;
      windowWorker[0].h = 16;
     
      windowWorker[1].x = 54;
      windowWorker[1].y = 98;
      windowWorker[1].w = 6;
      windowWorker[1].h = 16;
      
      windowWorkerArm.x = 52;
      windowWorkerArm.y = 98;
      windowWorkerArm.w = 2;
      windowWorkerArm.h = 12;
    }

    void render(){
      if(animate && ((SDL_GetTicks()-handleLifetime) > LETTER_LIFETIME)){
        animate = false;
        windowWorkersIndex = 0;
        windowWorkerIndex = 0; 
        object->setY(73*SCALESIZE);
      }

      
      if(windowWorkerIndex){ 
        renderQuad = {WINDOW_WORKER_X + 4*SCALESIZE, WINDOW_WORKER_Y, windowWorkerArm.w*SCALESIZE, windowWorkerArm.h*SCALESIZE};
        SDL_RenderCopy(renderer, objectTexture, &windowWorkerArm, &renderQuad);
        angle = 0;
        raiseArm = false; 
      }
      else{
        renderQuad = {WINDOW_WORKER_X + 4*SCALESIZE, WINDOW_WORKER_Y, windowWorkerArm.w*SCALESIZE, windowWorkerArm.h*SCALESIZE};
        SDL_RenderCopyEx(renderer, objectTexture, &windowWorkerArm, &renderQuad, angle, NULL, SDL_FLIP_NONE); 
      }
      
      renderQuad = {WINDOW_WORKER_X,WINDOW_WORKER_Y, windowWorker[0].w*SCALESIZE, windowWorker[0].h*SCALESIZE};
      SDL_RenderCopy(renderer, objectTexture, &windowWorker[windowWorkerIndex], &renderQuad); 
      
      renderQuad = {WINDOW_WORKERS_X, WINDOW_WORKERS_Y, windowWorkers[0].w*SCALESIZE, windowWorkers[0].h*SCALESIZE};
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
      if(x>= (OFFSET + 43*SCALESIZE) && x <= (OFFSET + 48*SCALESIZE)){
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
