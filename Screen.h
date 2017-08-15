#ifndef Screen_h
#define Screen_h

class Screen
{
  public:
    Screen(SDL_Renderer* renderer)
    {
      this->renderer = renderer;

      wholeScreen.x = 0;
      wholeScreen.y = 40;
      wholeScreen.w = 1280;
      wholeScreen.h = 540;

      wholeScreenXPos = 0;
      wholeScreenYPos = SCREEN_STARTING_YPOS;
      
      leftFrame.x = wholeScreen.x;
      leftFrame.y = wholeScreen.y;
      leftFrame.w = 50;
      leftFrame.h = wholeScreen.h;

      rightFrame.x = wholeScreen.w - 50;
      rightFrame.y = wholeScreen.y;
      rightFrame.w = 50;
      rightFrame.h = wholeScreen.h;
  
      for(int i = 0; i < 5; i++){
        startFrames[i].w = 60;
        startFrames[i].h = 90;
        startFrames[i].x = 240 + i*60;
        startFrames[i].y = 580;
      } 
      for(int i = 0; i < 9; i++){
        endFrames[i].w = 60;
        endFrames[i].h = 90;
        endFrames[i].x = 540 + i*60;
        endFrames[i].y = 580;
      } 
      
      endXPos = SCREEN_WIDTH/2 - (endFrames[0].w*9)/2;
    }

    ~Screen()
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
      if(wholeScreenYPos<SCREEN_END_YPOS){ 
        wholeScreenYPos+=10;
      }
      else{
        wholeScreenYPos = SCREEN_END_YPOS;
        screenDropped = true; 
        return true; 
      }
      return false;
    }

    bool liftScreen(){
      if(!endLettersDropped){
        return false;
      } 
      else if(wholeScreenYPos>SCREEN_STARTING_YPOS){ 
        wholeScreenYPos-=10;
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
    
      if(!screenDropped){
        if(raiseLetters){
          for(int i = 0; i < raiseLetters; i++){
            if(startFramesYPos[i] > -50){ 
              startFramesYPos[i] -= 10;
            }
          }
          if(raiseLetters == 5 && startFramesYPos[4] <= -50){
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
            if(endFramesYPos[i] > -50){
              endFramesYPos[i] -= 10;
            }
          }
          if(raiseEndLetters == 9 && endFramesYPos[8] <= -50){
            endLettersRaised = true;
            endLettersDropped = false;
            raiseEndLetters = 0;
            for(int i = 0; i < 9; i++){
              endFramesYPos[i] = 410;
            }
          }
        }
        else if(dropLetters){
          for(int i = 0; i < dropLetters; i++){
            if(startFramesYPos[i] < 40){
              startFramesYPos[i] += 10;
            }
          }
          if(dropLetters == 5 && startFramesYPos[4] >= 40){
            lettersRaised = false;
            lettersDropped = true;
            dropLetters = 0;
          }
        } 
        for(int i = 0; i < 5; i++){ 
          renderQuad = {490+i*startFrames[i].w,startFramesYPos[i],startFrames[i].w,startFrames[i].h};	
          SDL_RenderCopy(renderer, objectTexture,&startFrames[i], &renderQuad);
        } 
      }

      if(endGame){
        dropGameOver();
      }
      if(endLettersDropped && screenDropped){
        for(int i = 0; i < 9; i++){
          endFramesYPos[i] = wholeScreenYPos + 540;
        }
      } 
      if(endGame || endLettersDropped){ 
        for(int i = 0; i < 9; i++){
          SDL_Rect renderQuad = {endXPos+i*endFrames[i].w,endFramesYPos[i],endFrames[i].w,endFrames[i].h};	
          SDL_RenderCopy(renderer, objectTexture,&endFrames[i], &renderQuad);
        }
      }
      renderQuad = {wholeScreenXPos,wholeScreenYPos,wholeScreen.w,wholeScreen.h};	
      SDL_RenderCopy(renderer, objectTexture,&wholeScreen, &renderQuad);
      
    }
    
    void dropGameOver(){ 
      for(int i = 0; i < endGame; i++){
        if(endFramesYPos[i] < 540){
          endFramesYPos[i] += 10;
        }
      }
      if(endGame == 9 && endFramesYPos[8] >= 540){
        endGame = 0;
        endLettersDropped=true; 
        return; 
      }
      if(endGame < 9)
        endGame++;      
    }

    void renderFrame()
    {
      SDL_Rect renderQuad = {0, 0, leftFrame.w, leftFrame.h};
      SDL_RenderCopy(renderer, objectTexture,&leftFrame, &renderQuad);

      renderQuad = {wholeScreen.w - rightFrame.w, 0, rightFrame.w, rightFrame.h};	
      SDL_RenderCopy(renderer, objectTexture,&rightFrame, &renderQuad);
    }

    void setObjectTexture(SDL_Texture* texture)
    {
      this->objectTexture = texture;
    }
    
    void setEndGame(int value){
      endGame = value;
    }

    bool getLettersRaised(){ return lettersRaised; }
    
    bool getLettersDropped(){ return lettersDropped; }

  private:
    SDL_Texture* objectTexture = NULL;
    SDL_Renderer* renderer = NULL;
    SDL_Rect leftFrame;
    SDL_Rect rightFrame;
    SDL_Rect wholeScreen;
    SDL_Rect startFrames[5]; 
    SDL_Rect endFrames[9]; 
    bool screenDropped = false;
    bool lettersRaised = false; 
    bool lettersDropped = true; 
    bool endLettersDropped = false; 
    bool endLettersRaised = true; 
    int wholeScreenXPos = 0;
    int wholeScreenYPos = 0;
    int raiseLetters = 0;
    int raiseEndLetters = 0; 
    int dropLetters = 0; 
    int startFramesYPos[5] = {40, 40, 40, 40, 40};
    int endFramesYPos[9] = {410,410,410,410,410,410,410,410,410};        
    int endXPos;
    int endGame = 0;

};	

#endif
