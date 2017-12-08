#include "Object.h"

#ifndef Trashcan_h
#define Trashcan_h

class Trashcan{
  public:
    Trashcan(SDL_Renderer* renderer){
      object = new Object(0, 102, 7, 13, TRASHCAN_SPAWN_X, TRASHCAN_SPAWN_Y, renderer);
      flyYPos = TRASHCAN_SPAWN_Y + 1*SCALESIZE;
      flyXPos = TRASHCAN_SPAWN_X + 1*SCALESIZE;
      fly2YPos = TRASHCAN_SPAWN_Y + 1*SCALESIZE;
      fly2XPos = TRASHCAN_SPAWN_X + 2*SCALESIZE;
      fly = new Object(10, 106, 3, 2, flyXPos, flyYPos, renderer);
      fly2 = new Object(10, 106, 3, 2, fly2XPos, fly2YPos, renderer);
      this->renderer = renderer;
      
      flyAngle = 45;
      fly2Angle = 45;
      randXChange = (rand()%((int)(.5*SCALESIZE))); 
      
      int randNum1 = 2+(rand()%4);
      flyVelocity = (double)((1+(1./randNum1)))*SCALESIZE;
      int randNum2 = 2+(rand()%4);
      while(randNum1 == randNum2)
        randNum2 = 2+rand()%4;
      fly2Velocity = (double)((1+(1./randNum2)))*SCALESIZE;
    }

    void render(){
      if(fliesOut){
        animate();
        if(fly->getY() < TRASHCAN_SPAWN_Y + 1*SCALESIZE){
          fly->render();
        }
        if(fly2->getY() < TRASHCAN_SPAWN_Y + 1*SCALESIZE){
          fly2->render();
        }
      }
      object->render();
    }

    void resetFlies(){
      fly->setX(TRASHCAN_SPAWN_X + 2*SCALESIZE);
      fly->setY(TRASHCAN_SPAWN_Y + 1*SCALESIZE);
      fly2->setX(TRASHCAN_SPAWN_X + 1*SCALESIZE);
      fly2->setY(TRASHCAN_SPAWN_Y + 1*SCALESIZE);
      randXChange = (rand()%((int)(.5*SCALESIZE)));
      flyRelY = 0;
      flyRate = 0;
      flyRelX = 0;
      flyPrevRelY = 0;
      flyPrevRelX = 0;
      flyYPos = fly->getY();
      flyXPos = fly->getX();
      fly2RelY = 0;
      fly2Rate = 0;
      fly2RelX = 0;
      fly2PrevRelY = 0;
      fly2PrevRelX = 0;
      fly2YPos = fly2->getY();
      fly2XPos = fly2->getX();
      int randNum1 = 2+rand()%4;
      flyVelocity = ((1+(1./randNum1)))*SCALESIZE;
      int randNum2 = 2+rand()%4;
      while(randNum1 == randNum2)
        randNum2 = 2+rand()%4;
      fly2Velocity = ((1+(1./randNum2)))*SCALESIZE;
    }

    
    void animate(){
      
      fliesOut = true;
      
      double radians = flyAngle*PI/180.0;
     
      if(flyRate > -.1*SCALESIZE){
        flyRelY = (((abs(flyRelX))*(tan(radians)))-(((GRAVITY)*(pow((abs(flyRelX)),2)))/(2.0*(pow(flyVelocity,2)*pow(cos(radians),2))))/10);	
        flyRate = 4*(flyRelY-flyPrevRelY);
        if(flyRate < -.1*SCALESIZE)
          flyRate = -.2*SCALESIZE; 
      } 
      
      
      flyPrevRelY = flyRelY;  
      flyRelX -= (-5)/speedMult;
       
      flyYPos -= (flyRate/15)*SCALESIZE;
      if(flyAngle%2){  
        flyXPos += (-.3*SCALESIZE - randXChange)/speedMult;	
      }
      else{
        flyXPos -= (-.3*SCALESIZE - randXChange)/speedMult;
      }
      
      int randInt; 
      randInt = (rand()%2);
      if(fly->getX() < TRASHCAN_SPAWN_X){
        fly->setX(fly->getX()+3);
      }
      else if(fly->getX() > (TRASHCAN_SPAWN_X + 7*SCALESIZE)){
        fly->setX(fly->getX()-3);
      } 
      else if(randInt)
        fly->setX(fly->getX()+3);
      else
        fly->setX(fly->getX()-3);
      
      fly->setY(flyYPos);

      
      radians = fly2Angle*PI/180.0;
     
      if(fly2Rate > -.1*SCALESIZE){
        fly2RelY = (((abs(fly2RelX))*(tan(radians)))-(((GRAVITY)*(pow((abs(fly2RelX)),2)))/(2.0*(pow(fly2Velocity,2)*pow(cos(radians),2))))/10);	
        fly2Rate = 4*(fly2RelY-fly2PrevRelY);
        if(fly2Rate < -.1*SCALESIZE)
          fly2Rate = -.2*SCALESIZE; 
      } 
      
      
      fly2PrevRelY = fly2RelY;  
      fly2RelX -= (-5)/speedMult;
       
      fly2YPos -= (fly2Rate/15)*SCALESIZE;
      if(fly2Angle%2){  
        fly2XPos += (-.3*SCALESIZE - randXChange)/speedMult;	
      }
      else{
        fly2XPos -= (-.3*SCALESIZE - randXChange)/speedMult;
      }
      
      randInt = (rand()%2);
      if(fly2->getX() < TRASHCAN_SPAWN_X){
        fly2->setX(fly2->getX()+3);
      }
      else if(fly2->getX() > (TRASHCAN_SPAWN_X + 7*SCALESIZE)){
        fly2->setX(fly2->getX()-3);
      } 
      else if(randInt)
        fly2->setX(fly2->getX()+3);
      else
        fly2->setX(fly2->getX()-3);
      
      fly2->setY(fly2YPos);

      if(fly2->getY() > TRASHCAN_SPAWN_Y+1*SCALESIZE && fly->getY() > TRASHCAN_SPAWN_Y+1*SCALESIZE){
        fliesOut = false;
        resetFlies();
      }

      return;
    }

    void setObjectTexture(SDL_Texture* texture){
      this->objectTexture = texture;
      object->setObjectTexture(texture);
      fly->setObjectTexture(texture);
      fly2->setObjectTexture(texture);
    }

    bool collisionCheck(double x, double y){
      if(x >= TRASHCAN_SPAWN_X && x <= TRASHCAN_SPAWN_X + 7*SCALESIZE)
        if(y >= TRASHCAN_SPAWN_Y - 1*SCALESIZE && y <= TRASHCAN_SPAWN_Y + 4*SCALESIZE)
          return true;
      return false;
    }

  private:
    Object* object;
    Object* fly;
    Object* fly2;
    SDL_Renderer* renderer = NULL;
    SDL_Texture* objectTexture; 
    SDL_Rect renderQuad;
    bool fliesOut;
    double flyRelX;
    double fly2RelX;
    double flyRelY;
    double fly2RelY;
    double fly2PrevRelY;
    double fly2PrevRelX;
    double flyPrevRelX;
    double flyPrevRelY;
    double flyXPos;
    double fly2XPos;
    double flyYPos;
    double fly2YPos;
    double flyRate;
    double fly2Rate;
    int randXChange;
    double flyVelocity;
    double fly2Velocity;
    int flyAngle;
    int fly2Angle;
    double speedMult = 1;





};

#endif
