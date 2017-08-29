#include "Object.h"

#ifndef Fountain_h
#define Fountain_h

class Fountain{
  public:
    Fountain(SDL_Renderer* renderer){
      object = new Object(0*SCALESIZE, 115*SCALESIZE, 10*SCALESIZE, 30*SCALESIZE, FOUNTAIN_SPAWN_X,FOUNTAIN_SPAWN_Y, renderer);
      leftHandle = new Object(10*SCALESIZE, 131*SCALESIZE, 2*SCALESIZE, 1*SCALESIZE, LEFT_FOUNTAIN_HANDLE_SPAWN_X, LEFT_FOUNTAIN_HANDLE_SPAWN_Y, renderer);
      rightHandle = new Object(12*SCALESIZE, 131*SCALESIZE, 2*SCALESIZE, 1*SCALESIZE, RIGHT_FOUNTAIN_HANDLE_SPAWN_X, RIGHT_FOUNTAIN_HANDLE_SPAWN_Y, renderer);
      this->renderer = renderer;
      
      for(int i = 0; i < 5; i++){
        stream[i].x = 10*SCALESIZE + (1*SCALESIZE*i);
        stream[i].y = 133*SCALESIZE;
        stream[i].w = 1*SCALESIZE;
        stream[i].h = 3*SCALESIZE;
      }
    }
    void render(){

      object->render();
      leftHandle->render();
      rightHandle->render();
      animate();  
    }
    
    void animate(){
      if(leftHandleDown){
        if(SDL_GetTicks()-leftHandleDownTime > LETTER_LIFETIME){
          leftHandleDown = false;
          leftHandle->setY(LEFT_FOUNTAIN_HANDLE_SPAWN_Y);
        }
        else{
          renderQuad = {LEFT_FOUNTAIN_HANDLE_SPAWN_X + 1*SCALESIZE, LEFT_FOUNTAIN_HANDLE_SPAWN_Y + 2*SCALESIZE, stream[0].w, stream[0].h};
          SDL_RenderCopy(renderer, objectTexture, &stream[leftStreamIndex], &renderQuad); 
          if(SDL_GetTicks()-leftStreamAnimationTimer > 100){
            if(leftStreamIndex < 2) 
              leftStreamIndex++;
            leftStreamAnimationTimer = SDL_GetTicks(); 
          } 
        }
      }
      else if(leftStreamIndex != 0){
          renderQuad = {LEFT_FOUNTAIN_HANDLE_SPAWN_X + 1*SCALESIZE, LEFT_FOUNTAIN_HANDLE_SPAWN_Y + 2*SCALESIZE, stream[0].w, stream[0].h};
          SDL_RenderCopy(renderer, objectTexture, &stream[leftStreamIndex], &renderQuad); 
          if(SDL_GetTicks()-leftStreamAnimationTimer > 100){
            if(leftStreamIndex == 5) 
              leftStreamIndex=0;
            else{
              leftStreamIndex++;
            }
            leftStreamAnimationTimer = SDL_GetTicks(); 
          }
      } 

      if(rightHandleDown){
        if(SDL_GetTicks()-rightHandleDownTime > LETTER_LIFETIME){
          rightHandleDown = false;
          rightHandle->setY(RIGHT_FOUNTAIN_HANDLE_SPAWN_Y);
        }
        else{
          renderQuad = {RIGHT_FOUNTAIN_HANDLE_SPAWN_X, RIGHT_FOUNTAIN_HANDLE_SPAWN_Y+2*SCALESIZE, stream[0].w, stream[0].h};
          SDL_RenderCopy(renderer, objectTexture, &stream[rightStreamIndex], &renderQuad); 
          if(SDL_GetTicks()-rightStreamAnimationTimer > 100){
            if(rightStreamIndex < 2) 
              rightStreamIndex++;
            rightStreamAnimationTimer = SDL_GetTicks(); 
          } 
        }
      }
      else if(rightStreamIndex != 0){
          renderQuad = {RIGHT_FOUNTAIN_HANDLE_SPAWN_X, RIGHT_FOUNTAIN_HANDLE_SPAWN_Y+2*SCALESIZE, stream[0].w, stream[0].h};
          SDL_RenderCopy(renderer, objectTexture, &stream[rightStreamIndex], &renderQuad); 
          if(SDL_GetTicks()-rightStreamAnimationTimer > 100){
            if(rightStreamIndex == 5) 
              rightStreamIndex = 0;
            else
              rightStreamIndex++;
            rightStreamAnimationTimer = SDL_GetTicks(); 
          }
      } 

    }

    void setObjectTexture(SDL_Texture* texture){
      this->objectTexture = texture;
      object->setObjectTexture(texture);
      leftHandle->setObjectTexture(texture); 
      rightHandle->setObjectTexture(texture); 
    }

    bool collisionCheck(double x, double y){
      if(x >= LEFT_FOUNTAIN_HANDLE_SPAWN_X && x <= LEFT_FOUNTAIN_HANDLE_SPAWN_X+2*SCALESIZE){
        if(y >= LEFT_FOUNTAIN_HANDLE_SPAWN_Y - 2*SCALESIZE && y <= LEFT_FOUNTAIN_HANDLE_SPAWN_Y + 3*SCALESIZE){
          leftHandleDownTime = SDL_GetTicks(); 
          leftHandleDown = true;       
          leftHandle->setY(LEFT_FOUNTAIN_HANDLE_SPAWN_Y+1*SCALESIZE); 
          return true;
        }
      } 
      else if(x >= RIGHT_FOUNTAIN_HANDLE_SPAWN_X && x <= RIGHT_FOUNTAIN_HANDLE_SPAWN_X+2*SCALESIZE){
        if(y >= LEFT_FOUNTAIN_HANDLE_SPAWN_Y - 2*SCALESIZE && y <= LEFT_FOUNTAIN_HANDLE_SPAWN_Y + 3*SCALESIZE){
          rightHandleDownTime = SDL_GetTicks(); 
          rightHandleDown = true; 
          rightHandle->setY(LEFT_FOUNTAIN_HANDLE_SPAWN_Y+1*SCALESIZE); 
          return true;
        }
      } 
      return false;
    }

  private:
    Object* object;
    Object* leftHandle;
    Object* rightHandle;
    SDL_Rect stream[5];
    SDL_Renderer* renderer = NULL;
    SDL_Texture* objectTexture; 
    SDL_Rect objectClip;
    SDL_Rect renderQuad;
    bool leftHandleDown = false;
    bool rightHandleDown = false;
    Uint32 leftHandleDownTime;
    Uint32 rightHandleDownTime;
    Uint32 leftStreamAnimationTimer;
    Uint32 rightStreamAnimationTimer;
    int leftStreamIndex = 0;
    int rightStreamIndex = 0;

};

#endif
