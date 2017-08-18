#include "Object.h"

#ifndef Fountain_h
#define Fountain_h

class Fountain{
  public:
    Fountain(SDL_Renderer* renderer){
      object = new Object(0, 1150, 100, 300, FOUNTAIN_SPAWN_X,FOUNTAIN_SPAWN_Y, renderer);
      leftHandle = new Object(100, 1310, 20, 10, LEFT_FOUNTAIN_HANDLE_SPAWN_X, LEFT_FOUNTAIN_HANDLE_SPAWN_Y, renderer);
      rightHandle = new Object(120, 1310, 20, 10, RIGHT_FOUNTAIN_HANDLE_SPAWN_X, RIGHT_FOUNTAIN_HANDLE_SPAWN_Y, renderer);
      this->renderer = renderer;
      
      for(int i = 0; i < 5; i++){
        stream[i].x = 100 + (10*i);
        stream[i].y = 1330;
        stream[i].w = 10;
        stream[i].h = 30;
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
          renderQuad = {LEFT_FOUNTAIN_HANDLE_SPAWN_X + 10, LEFT_FOUNTAIN_HANDLE_SPAWN_Y + 20, stream[0].w, stream[0].h};
          SDL_RenderCopy(renderer, objectTexture, &stream[leftStreamIndex], &renderQuad); 
          if(SDL_GetTicks()-leftStreamAnimationTimer > 100){
            if(leftStreamIndex < 2) 
              leftStreamIndex++;
            leftStreamAnimationTimer = SDL_GetTicks(); 
          } 
        }
      }
      else if(leftStreamIndex != 0){
          renderQuad = {LEFT_FOUNTAIN_HANDLE_SPAWN_X + 10, LEFT_FOUNTAIN_HANDLE_SPAWN_Y + 20, stream[0].w, stream[0].h};
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
          renderQuad = {RIGHT_FOUNTAIN_HANDLE_SPAWN_X, RIGHT_FOUNTAIN_HANDLE_SPAWN_Y+20, stream[0].w, stream[0].h};
          SDL_RenderCopy(renderer, objectTexture, &stream[rightStreamIndex], &renderQuad); 
          if(SDL_GetTicks()-rightStreamAnimationTimer > 100){
            if(rightStreamIndex < 2) 
              rightStreamIndex++;
            rightStreamAnimationTimer = SDL_GetTicks(); 
          } 
        }
      }
      else if(rightStreamIndex != 0){
          renderQuad = {RIGHT_FOUNTAIN_HANDLE_SPAWN_X, RIGHT_FOUNTAIN_HANDLE_SPAWN_Y+20, stream[0].w, stream[0].h};
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

    bool collisionCheck(int x, int y){
      if(x >= LEFT_FOUNTAIN_HANDLE_SPAWN_X && x <= LEFT_FOUNTAIN_HANDLE_SPAWN_X+20){
        if(y >= LEFT_FOUNTAIN_HANDLE_SPAWN_Y - 20 && y <= LEFT_FOUNTAIN_HANDLE_SPAWN_Y + 30){
          leftHandleDownTime = SDL_GetTicks(); 
          leftHandleDown = true;       
          leftHandle->setY(LEFT_FOUNTAIN_HANDLE_SPAWN_Y+10); 
          return true;
        }
      } 
      if(x >= RIGHT_FOUNTAIN_HANDLE_SPAWN_X && x <= RIGHT_FOUNTAIN_HANDLE_SPAWN_X+20){
        if(y >= LEFT_FOUNTAIN_HANDLE_SPAWN_Y - 20 && y <= LEFT_FOUNTAIN_HANDLE_SPAWN_Y + 30){
          rightHandleDownTime = SDL_GetTicks(); 
          rightHandleDown = true; 
          rightHandle->setY(LEFT_FOUNTAIN_HANDLE_SPAWN_Y+10); 
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
