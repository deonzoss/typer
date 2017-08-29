#ifndef Screen_h
#define Screen_h

class Screen
{
  public:
    Screen(SDL_Renderer* renderer)
    {
      this->renderer = renderer;

      wholeScreen.x = 0*SCALESIZE;
      wholeScreen.y = 4*SCALESIZE;
      wholeScreen.w = 128*SCALESIZE;
      wholeScreen.h = 54*SCALESIZE;

      wholeScreenXPos = 0*SCALESIZE;
      wholeScreenYPos = SCREEN_STARTING_YPOS;
      
      leftFrame.x = wholeScreen.x;
      leftFrame.y = wholeScreen.y;
      leftFrame.w = 5*SCALESIZE;
      leftFrame.h = wholeScreen.h;

      rightFrame.x = wholeScreen.w - 5*SCALESIZE;
      rightFrame.y = wholeScreen.y;
      rightFrame.w = 5*SCALESIZE;
      rightFrame.h = wholeScreen.h;
  
      for(int i = 0; i < 5; i++){
        startFrames[i].w = 6*SCALESIZE;
        startFrames[i].h = 9*SCALESIZE;
        startFrames[i].x = 24*SCALESIZE + i*6*SCALESIZE;
        startFrames[i].y = 58*SCALESIZE;
      } 
      for(int i = 0; i < 9; i++){
        endFrames[i].w = 6*SCALESIZE;
        endFrames[i].h = 9*SCALESIZE;
        endFrames[i].x = 54*SCALESIZE + i*6*SCALESIZE;
        endFrames[i].y = 58*SCALESIZE;
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
        wholeScreenYPos+=1*SCALESIZE;
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
        for(int i = 0; i < 5; i++){ 
          renderQuad = {49*SCALESIZE+i*startFrames[i].w,startFramesYPos[i],startFrames[i].w,startFrames[i].h};	
          SDL_RenderCopy(renderer, objectTexture,&startFrames[i], &renderQuad);
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
          SDL_Rect renderQuad = {endXPos+i*endFrames[i].w,endFramesYPos[i],endFrames[i].w,endFrames[i].h};	
          SDL_RenderCopy(renderer, objectTexture,&endFrames[i], &renderQuad);
        }
      }
      renderQuad = {wholeScreenXPos,wholeScreenYPos,wholeScreen.w,wholeScreen.h};	
      SDL_RenderCopy(renderer, objectTexture,&wholeScreen, &renderQuad);
      
    }
    
    void dropGameOver(){ 
      for(int i = 0; i < endGame; i++){
        if(endFramesYPos[i] < 54*SCALESIZE){
          endFramesYPos[i] += 1*SCALESIZE;
        }
      }
      if(endGame == 9 && endFramesYPos[8] >= 54*SCALESIZE){
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
    double wholeScreenXPos = 0;
    double wholeScreenYPos = 0;
    int raiseLetters = 0;
    int raiseEndLetters = 0; 
    int dropLetters = 0; 
    int startFramesYPos[5] = {4*SCALESIZE, 4*SCALESIZE, 4*SCALESIZE, 4*SCALESIZE, 4*SCALESIZE};
    int endFramesYPos[9] = {41*SCALESIZE,41*SCALESIZE,41*SCALESIZE,41*SCALESIZE,41*SCALESIZE,41*SCALESIZE,41*SCALESIZE,41*SCALESIZE,41*SCALESIZE};        
    double endXPos;
    int endGame = 0;

};	

#endif
