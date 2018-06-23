#include "Object.h"

#ifndef Cabinet_h
#define Cabinet_h

class Cabinet{
  public:
    Cabinet(SDL_Renderer* renderer){
      object = new Object(117, 159, 9, 6, 178*SCALESIZE, 86*SCALESIZE, renderer);
      paperYPos = 86*SCALESIZE + 1*SCALESIZE;
      paperXPos = 178*SCALESIZE + 1*SCALESIZE;
      paper2YPos = 86*SCALESIZE + 1*SCALESIZE;
      paper2XPos = 178*SCALESIZE + 2*SCALESIZE;
      paper = new Object(127, 159, 3, 5, paperXPos, paperYPos, renderer);
      paper2 = new Object(132, 159, 3, 5, paper2XPos, paper2YPos, renderer);
      paper->setRotate(true);
      paper2->setRotate(true);
      this->renderer = renderer;
      
      paperAngle = 45;
      paper2Angle = 45;
      randXChange = (rand()%((int)(.5*SCALESIZE))); 
      
      int randNum1 = 2+(rand()%4);
      paperVelocity = (double)((1+(1./randNum1)))*SCALESIZE;
      int randNum2 = 2+(rand()%4);
      while(randNum1 == randNum2)
        randNum2 = 2+rand()%4;
      paper2Velocity = (double)((1+(1./randNum2)))*SCALESIZE;
    }

    void render(){
      if(papersOut){
        animate();
        if(paper->getY() < 86*SCALESIZE - 2*SCALESIZE){
          paper->render();
        }
        if(paper2->getY() < 86*SCALESIZE - 2*SCALESIZE){
          paper2->render();
        }
      }
      object->render();
    }

    void resetFlies(){
      paper->setRotate(true);
      paper2->setRotate(true);
      paper->setX(178*SCALESIZE + 2*SCALESIZE);
      paper->setY(86*SCALESIZE + 1*SCALESIZE);
      paper2->setX(178*SCALESIZE + 1*SCALESIZE);
      paper2->setY(86*SCALESIZE + 1*SCALESIZE);
      randXChange = (rand()%((int)(.5*SCALESIZE)));
      paperRelY = 0;
      paperRate = 0;
      paperRelX = 0;
      paperPrevRelY = 0;
      paperPrevRelX = 0;
      paperYPos = paper->getY();
      paperXPos = paper->getX();
      paper2RelY = 0;
      paper2Rate = 0;
      paper2RelX = 0;
      paper2PrevRelY = 0;
      paper2PrevRelX = 0;
      paper2YPos = paper2->getY();
      paper2XPos = paper2->getX();
      int randNum1 = 2+rand()%4;
      paperVelocity = ((1+(1./randNum1)))*SCALESIZE;
      int randNum2 = 2+rand()%4;
      while(randNum1 == randNum2)
        randNum2 = 2+rand()%4;
      paper2Velocity = ((1+(1./randNum2)))*SCALESIZE;
    }

    
    void animate(){
      
      papersOut = true;
      
      double radians = paperAngle*PI/180.0;

     
      if(paperRate > -.1*SCALESIZE){
        paperRelY = (((abs(paperRelX))*(tan(radians)))-(((GRAVITY)*(pow((abs(paperRelX)),2)))/(2.0*(pow(paperVelocity,2)*pow(cos(radians),2))))/10);	
        paperRate = 4*(paperRelY-paperPrevRelY);
        if(paperRate < -.1*SCALESIZE)
          paperRate = -.2*SCALESIZE; 
      } 
      
      
      paperPrevRelY = paperRelY;  
      paperRelX -= (-5)/speedMult;
       
      paperYPos -= (paperRate/15)*SCALESIZE;
      if(paperAngle%2){  
        paperXPos += (-.5*SCALESIZE - randXChange)/speedMult;	
      }
      else{
        paperXPos -= (-.5*SCALESIZE - randXChange)/speedMult;
      }
      
      int randInt; 
      randInt = (rand()%2);
      if(paper->getX() < 178*SCALESIZE){
        paper->setX(paper->getX()+3);
      }
      else if(paper->getX() > (178*SCALESIZE + 7*SCALESIZE)){
        paper->setX(paper->getX()-3);
      } 
      else if(randInt)
        paper->setX(paper->getX()+3);
      else
        paper->setX(paper->getX()-3);
      
      paper->setY(paperYPos);

      
      radians = paper2Angle*PI/180.0;
     
      if(paper2Rate > -.1*SCALESIZE){
        paper2RelY = (((abs(paper2RelX))*(tan(radians)))-(((GRAVITY)*(pow((abs(paper2RelX)),2)))/(2.0*(pow(paper2Velocity,2)*pow(cos(radians),2))))/10);	
        paper2Rate = 4*(paper2RelY-paper2PrevRelY);
        if(paper2Rate < -.1*SCALESIZE)
          paper2Rate = -.2*SCALESIZE; 
      } 
      
      
      paper2PrevRelY = paper2RelY;  
      paper2RelX -= (-5)/speedMult;
       
      paper2YPos -= (paper2Rate/15)*SCALESIZE;
      if(paper2Angle%2){  
        paper2XPos += (-.3*SCALESIZE - randXChange)/speedMult;	
      }
      else{
        paper2XPos -= (-.3*SCALESIZE - randXChange)/speedMult;
      }
      
      randInt = (rand()%2);
      if(paper2->getX() < 178*SCALESIZE){
        paper2->setX(paper2->getX()+3);
      }
      else if(paper2->getX() > (178*SCALESIZE + 7*SCALESIZE)){
        paper2->setX(paper2->getX()-3);
      } 
      else if(randInt)
        paper2->setX(paper2->getX()+3);
      else
        paper2->setX(paper2->getX()-3);
      
      paper2->setY(paper2YPos);

      if(paper2->getY() > 86*SCALESIZE+1*SCALESIZE && paper->getY() > 86*SCALESIZE+1*SCALESIZE){
        papersOut = false;
        resetFlies();
      }

      return;
    }

    void setObjectTexture(SDL_Texture* texture){
      this->objectTexture = texture;
      object->setObjectTexture(texture);
      paper->setObjectTexture(texture);
      paper2->setObjectTexture(texture);
    }

    bool collisionCheck(double x, double y){
      if(x >= 178*SCALESIZE && x <= 178*SCALESIZE + 7*SCALESIZE)
        if(y >= 86*SCALESIZE - 1*SCALESIZE && y <= 86*SCALESIZE + 4*SCALESIZE)
          return true;
      return false;
    }

  private:
    Object* object;
    Object* paper;
    Object* paper2;
    SDL_Renderer* renderer = NULL;
    SDL_Texture* objectTexture; 
    SDL_Rect renderQuad;
    bool papersOut;
    double paperRelX;
    double paper2RelX;
    double paperRelY;
    double paper2RelY;
    double paper2PrevRelY;
    double paper2PrevRelX;
    double paperPrevRelX;
    double paperPrevRelY;
    double paperXPos;
    double paper2XPos;
    double paperYPos;
    double paper2YPos;
    double paperRate;
    double paper2Rate;
    int randXChange;
    double paperVelocity;
    double paper2Velocity;
    int paperAngle;
    int paper2Angle;
    double speedMult = 1;





};

#endif
