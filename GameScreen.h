#include "Object.h"

#ifndef GameScreen_h
#define GameScreen_h

class GameScreen
{
  public:
    GameScreen(SDL_Renderer* renderer)
    {
      this->renderer = renderer;

      wholeScreen.x = 0;
      wholeScreen.y = 4;
      wholeScreen.w = 130;
      wholeScreen.h = 54;

      wholeScreenXPos = OFFSET - 1*SCALESIZE;
      wholeScreenYPos = SCREEN_STARTING_YPOS;
      
      leftFrame.x = wholeScreen.x;
      leftFrame.y = wholeScreen.y;
      leftFrame.w = 6;
      leftFrame.h = wholeScreen.h;

      rightFrame.x = wholeScreen.w - 6;
      rightFrame.y = wholeScreen.y;
      rightFrame.w = 6;
      rightFrame.h = wholeScreen.h;
      
      entireBar = new Object(0, 229, 192, 5, 0*SCALESIZE, -1*SCALESIZE, renderer);

      leftFrameExtension = new Object(130, 0, 4, 32, wholeScreenXPos-4*SCALESIZE, 0-28*SCALESIZE, renderer);
      rightFrameExtension = new Object(134, 0, 4, 32, wholeScreenXPos+wholeScreen.w*SCALESIZE, 0-28*SCALESIZE, renderer);

      blankWallLeft = new Object(138, 3,  30, wholeScreen.h, wholeScreenXPos-30*SCALESIZE, SCREEN_END_YPOS, renderer);
      blankWallRight = new Object(138, 3, 30, wholeScreen.h, wholeScreenXPos + wholeScreen.w*SCALESIZE, SCREEN_END_YPOS, renderer);
  
      for(int i = 0; i < 5; i++){
        startFrames[i].w = 6;
        startFrames[i].h = 9;
        startFrames[i].x = 24 + i*6;
        startFrames[i].y = 58;
      } 
      for(int i = 0; i < 9; i++){
        endFrames[i].w = 6;
        endFrames[i].h = 9;
        endFrames[i].x = 54 + i*6;
        endFrames[i].y = 58;
      } 

      for(int i = 0; i < 3; i++){
        flags[i] = new Object(111, 58, 5, 8, FLAG_XPOS + (6*i*SCALESIZE), FLAG_YPOS, renderer);
      }
      
      endXPos = SCREEN_WIDTH/2 - (endFrames[0].w*SCALESIZE*9)/2;

      Object* number3 = new Object( 66, 100, 6, 9, 1*6*SCALESIZE + OFFSET + 13*SCALESIZE, 56*SCALESIZE, renderer);
      Object* number2= new Object( 66 + 1*6, 100, 6, 9, 5*6*SCALESIZE + OFFSET + 13*SCALESIZE, 56*SCALESIZE, renderer);
      Object* number1= new Object( 66 + 2*6, 100, 6, 9, 9*6*SCALESIZE + OFFSET + 13*SCALESIZE, 56*SCALESIZE, renderer);
      Object* period1= new Object( 66 + 3*6, 100, 6, 9, 2*6*SCALESIZE + OFFSET + 13*SCALESIZE, 56*SCALESIZE, renderer);
      Object* period2= new Object( 66 + 3*6, 100, 6, 9, 3*6*SCALESIZE + OFFSET + 13*SCALESIZE, 56*SCALESIZE, renderer);
      Object* period3= new Object( 66 + 3*6, 100, 6, 9, 4*6*SCALESIZE + OFFSET + 13*SCALESIZE, 56*SCALESIZE, renderer);
      Object* period4= new Object( 66 + 3*6, 100, 6, 9, 6*6*SCALESIZE + OFFSET + 13*SCALESIZE, 56*SCALESIZE, renderer);
      Object* period5= new Object( 66 + 3*6, 100, 6, 9, 7*6*SCALESIZE + OFFSET + 13*SCALESIZE, 56*SCALESIZE, renderer);
      Object* period6= new Object( 66 + 3*6, 100, 6, 9, 8*6*SCALESIZE + OFFSET + 13*SCALESIZE, 56*SCALESIZE, renderer);
      Object* period7= new Object( 66 + 3*6, 100, 6, 9, 10*6*SCALESIZE + OFFSET + 13*SCALESIZE, 56*SCALESIZE, renderer);
      Object* period8= new Object( 66 + 3*6, 100, 6, 9, 11*6*SCALESIZE + OFFSET + 13*SCALESIZE, 56*SCALESIZE, renderer);
      Object* period9= new Object( 66 + 3*6, 100, 6, 9, 12*6*SCALESIZE + OFFSET + 13*SCALESIZE, 56*SCALESIZE, renderer);
      Object* letterG= new Object( 66 + 4*6, 100, 6, 9, 13*6*SCALESIZE + OFFSET + 13*SCALESIZE, 56*SCALESIZE, renderer);
      Object* letterO= new Object( 66 + 5*6, 100, 6, 9, 14*6*SCALESIZE + OFFSET + 13*SCALESIZE, 56*SCALESIZE, renderer);
      Object* exclamation= new Object( 66 + 6*6, 100, 6, 9, 15*6*SCALESIZE + OFFSET + 13*SCALESIZE, 56*SCALESIZE, renderer);
      countDownFrames[0] = number3;
      countDownFrames[1] = period1;
      countDownFrames[2] = period2;
      countDownFrames[3] = period3;
      countDownFrames[4] = number2;
      countDownFrames[5] = period4;
      countDownFrames[6] = period5;
      countDownFrames[7] = period6;
      countDownFrames[8] = number1;
      countDownFrames[9] = period7;
      countDownFrames[10] = period8;
      countDownFrames[11] = period9;
      countDownFrames[12] = letterG;
      countDownFrames[13] = letterO;
      countDownFrames[14] = exclamation;
    }

    ~GameScreen()
    {
      free();
    }

    void free()
    {

    }
    
    void raiseLetter(){
      raiseLetters++;
    }
    void raiseEndLetter(){
      raiseEndLetters++;
    }
    void dropLetter(){
      if(dropLetters < 5) 
        dropLetters++;
    }
    bool dropScreen(){
      if(wholeScreenYPos>(0-(wholeScreen.h*SCALESIZE/2.5))){
        int sideFramesYPos = leftFrameExtension->getY();
        leftFrameExtension->setY(sideFramesYPos+1*SCALESIZE);
        rightFrameExtension->setY(sideFramesYPos+1*SCALESIZE);
      }

      if(wholeScreenYPos<SCREEN_END_YPOS){ 
        wholeScreenYPos+=1*SCALESIZE;
      }
      else{
        wholeScreenYPos = SCREEN_END_YPOS;
        screenDropped = true; 
        if(countDown!=true){
          countDown = true;
        }
        return screenDropped; 
      }
      return false;
    }

    void setDemoScreen(){
        wholeScreenYPos = SCREEN_END_YPOS;
        leftFrameExtension->setY(-1*SCALESIZE);
        rightFrameExtension->setY(-1*SCALESIZE);
        screenDropped = true; 
        showDemo = true;
        if(countDown!=true){
          countDown = true;
        }
    }

    void setShowDemo(bool value){
      showDemo = value;
    }

    void countDownAnimate(){
      for(int i = 0; i < 15; i++){
       // countDownFrames[i]->render();
      }
      countDownDone = true;
    }

    bool liftScreen(){
      leftFrameExtension->render();
      rightFrameExtension->render();
      entireBar->render();
      if(!endLettersDropped && !showDemo){
        return false;
      }
      
      if(leftFrameExtension->getY() > -28*SCALESIZE){
        int sideFramesYPos = leftFrameExtension->getY();
        leftFrameExtension->setY(sideFramesYPos-1*SCALESIZE);
        rightFrameExtension->setY(sideFramesYPos-1*SCALESIZE);
        if(leftFrameExtension->getY() < -28*SCALESIZE){
          leftFrameExtension->setY(-28*SCALESIZE);
          rightFrameExtension->setY(-28*SCALESIZE);
        }
          
      }
      
      if(wholeScreenYPos>SCREEN_STARTING_YPOS){ 
        wholeScreenYPos-=1*SCALESIZE;
      }
      else{
        wholeScreenYPos = SCREEN_STARTING_YPOS;
        screenDropped = false; 
        return true; 
      }
      return false;
    }

    void renderScreen()
    {
      SDL_Rect renderQuad; 
      
      
      for(int i = 0; i < flagsDown; i++){
        if(flags[i]->getY()<FLAG_YPOS + (8*SCALESIZE)){
            flags[i]->setY(flags[i]->getY()+(.3*SCALESIZE));
            if(flags[i]->getY()>FLAG_YPOS+(8*SCALESIZE))
              flags[i]->setY(FLAG_YPOS + (8*SCALESIZE));
        }
        flags[i]->render();
      }
      
    
      if(!screenDropped){
        if(raiseLetters){
          for(int i = 0; i < raiseLetters; i++){
            if(startFramesYPos[i] > -5*SCALESIZE){ 
              startFramesYPos[i] -= 1*SCALESIZE;
            }
          }
          if(raiseLetters == 5 && startFramesYPos[4] <= -5*SCALESIZE){
            lettersRaised = true;
            lettersDropped = false; 
            raiseLetters = 0;
          }
        }
        else if(endLettersDropped){
          if(raiseEndLetters < 9){
            raiseEndLetter();
          } 
          for(int i = 0; i < raiseEndLetters; i++){
            if(endFramesYPos[i] > -5*SCALESIZE){
              endFramesYPos[i] -= 1*SCALESIZE;
            }
          }
          if(raiseEndLetters == 9 && endFramesYPos[8] <= -5*SCALESIZE){
            endLettersRaised = true;
            endLettersDropped = false;
            raiseEndLetters = 0;
            for(int i = 0; i < 9; i++){
              endFramesYPos[i] = 41*SCALESIZE;
            }
          }
        }
        else if(dropLetters){
          for(int i = 0; i < dropLetters; i++){
            if(startFramesYPos[i] < 4*SCALESIZE){
              startFramesYPos[i] += 1*SCALESIZE;
            }
          }
          if(dropLetters == 5 && startFramesYPos[4] >= 4*SCALESIZE){
            lettersRaised = false;
            lettersDropped = true;
            dropLetters = 0;
          }
        } 
        if(!lettersRaised){
          for(int i = 0; i < 5; i++){ 
            renderQuad = {OFFSET+49*SCALESIZE+i*startFrames[i].w*SCALESIZE,startFramesYPos[i],startFrames[i].w*SCALESIZE,startFrames[i].h*SCALESIZE};	
            SDL_RenderCopy(renderer, objectTexture,&startFrames[i], &renderQuad);
          } 
        }
      }

      if(endGame){
        dropGameOver();
      }
      if(endLettersDropped && screenDropped){
        for(int i = 0; i < 9; i++){
          endFramesYPos[i] = wholeScreenYPos + 54*SCALESIZE;
        }
      } 
      if(endGame || endLettersDropped){ 
        for(int i = 0; i < 9; i++){
          SDL_Rect renderQuad = {endXPos+i*endFrames[i].w*SCALESIZE,endFramesYPos[i],endFrames[i].w*SCALESIZE,endFrames[i].h*SCALESIZE};	
          SDL_RenderCopy(renderer, objectTexture,&endFrames[i], &renderQuad);
        }
      }
      
      if(!screenDropped){
        leftFrameExtension->render();
        rightFrameExtension->render();
      }
      
      if(countDown){
        countDownAnimate();
      }
     
      renderQuad = {wholeScreenXPos,wholeScreenYPos,wholeScreen.w*SCALESIZE,wholeScreen.h*SCALESIZE};	
      SDL_RenderCopy(renderer, objectTexture,&wholeScreen, &renderQuad);
      
      entireBar->render();


    }
    
    void dropGameOver(){ 
      for(int i = 0; i < endGame; i++){
        if(endFramesYPos[i] < SCREEN_END_YPOS + 54*SCALESIZE){
          endFramesYPos[i] += 1*SCALESIZE;
        }
      }
      for(int i = 0; i < flagsDown; i++){
        if(flags[i]->getY()>FLAG_YPOS){
          flags[i]->setY(flags[i]->getY()-1*SCALESIZE);
        }
      }
      if(endGame == 9 && endFramesYPos[8] >= SCREEN_END_YPOS + 54*SCALESIZE){
        endGame = 0;
        endLettersDropped=true; 
        flagsDown=0;
        resetFlags();
        return; 
      }
      if(endGame < 9)
        endGame++;      
    }

    void resetFlags(){
      for(int i = 0; i < 3; i++){
        flags[i]->setY(FLAG_YPOS);
        flags[i]->setX(FLAG_XPOS+(6*i*SCALESIZE));
      }
    }

    void renderFrame()
    {
      blankWallLeft->render();
      blankWallRight->render();
      leftFrameExtension->render();
      rightFrameExtension->render();
      entireBar->render();


      SDL_Rect renderQuad = {wholeScreenXPos, SCREEN_END_YPOS, leftFrame.w*SCALESIZE, leftFrame.h*SCALESIZE};
      SDL_RenderCopy(renderer, objectTexture,&leftFrame, &renderQuad);

      renderQuad = {wholeScreenXPos + wholeScreen.w*SCALESIZE - rightFrame.w*SCALESIZE, SCREEN_END_YPOS, rightFrame.w*SCALESIZE, rightFrame.h*SCALESIZE};	
      SDL_RenderCopy(renderer, objectTexture,&rightFrame, &renderQuad);
    }

    void setObjectTexture(SDL_Texture* texture)
    {
      this->objectTexture = texture;
      for(int i = 0; i < 3; i++){
        flags[i]->setObjectTexture(texture);
      }
      entireBar->setObjectTexture(objectTexture);
      leftFrameExtension->setObjectTexture(objectTexture);
      rightFrameExtension->setObjectTexture(objectTexture);
      blankWallLeft->setObjectTexture(objectTexture);
      blankWallRight->setObjectTexture(objectTexture);

      for(int i = 0; i < 15; i++){
        countDownFrames[i]->setObjectTexture(objectTexture);
      }
    }
    
    void setEndGame(int value){
      endGame = value;
    }

    bool getLettersRaised(){ return lettersRaised; }
    
    bool getLettersDropped(){ return lettersDropped; }

    void putFlagDown(){
      if(flagsDown < 3) 
        flagsDown++;
    }

    int getFlagsDown(){
      return flagsDown;
    }

    void setEndLettersDropped(bool value){
      endLettersDropped = value;
    }

  private:
    SDL_Texture* objectTexture = NULL;
    SDL_Renderer* renderer = NULL;
    SDL_Rect leftFrame;
    SDL_Rect rightFrame;
    SDL_Rect wholeScreen;
    SDL_Rect startFrames[5]; 
    SDL_Rect endFrames[9]; 
    Object* countDownFrames[15];
    Object* entireBar;
    Object* leftFrameExtension;
    Object* rightFrameExtension;
    Object* blankWallLeft;
    Object* blankWallRight;
    Object* flags[3];
    Uint32 countTime;
    bool screenDropped = false;
    bool countDownDone = false;
    bool countDown = false;
    bool lettersRaised = false; 
    bool lettersDropped = true; 
    bool endLettersDropped = false; 
    bool endLettersRaised = true; 
    bool showDemo = false;
    double wholeScreenXPos = 0;
    double wholeScreenYPos = 0;
    int raiseLetters = 0;
    int raiseEndLetters = 0; 
    int dropLetters = 0; 
    int startFramesYPos[5] = {4*SCALESIZE, 4*SCALESIZE, 4*SCALESIZE, 4*SCALESIZE, 4*SCALESIZE};
    int endFramesYPos[9] = {41*SCALESIZE,41*SCALESIZE,41*SCALESIZE,41*SCALESIZE,41*SCALESIZE,41*SCALESIZE,41*SCALESIZE,41*SCALESIZE,41*SCALESIZE};        
    double endXPos;
    int flagsDown = 0;
    int endGame = 0;


};	

#endif
