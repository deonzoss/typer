#include "Word.h"
#ifndef Menu_h
#define Menu_h

class Menu
{
  public:
    Menu(SDL_Renderer* renderer)
    {
      this->renderer = renderer;
      loadFont();
      for(int i = 0; i < 4; i++){
        menuFrames[i].w = 23;
        menuFrames[i].h = 6;
        menuFrames[i].x = 1;
        menuFrames[i].y = 58; 
      }
      loadMenuFrameText();
    }

    ~Menu()
    {
      free();
    }

    void free()
    {

    }

    void loadFont()
    {
      font = TTF_OpenFont(CODE_FONT, MAIN_MENU_FONT_SIZE);
      if(font == NULL)
        printf("Error opening menu font\n");
    }
    
    void reset(){
      //currentBorderRect={0,0,0,0};
      //currentOutlineRect={0,0,0,0};
      //previousBorderRect={0,0,0,0};
      //previousOutlineRect={0,0,0,0};
      prevBorderType=0;
      borderType=0;
      setMenuDisplay(1);
      for(int i = 0; i < 4; i++){
        menuFramesYPos[i] = MENU_FRAMES_SPAWN_Y; 
      }
      characterText->setY(MENU_FRAMES_SPAWN_Y+.5*SCALESIZE);
      levelText->setY(MENU_FRAMES_SPAWN_Y+.5*SCALESIZE);
      scoreboardText->setY(MENU_FRAMES_SPAWN_Y+.5*SCALESIZE);
      optionsText->setY(MENU_FRAMES_SPAWN_Y+.5*SCALESIZE);
      raiseMenu = false;
      scrollDownPrevFrame = false;
      transition = false;
    }

    void raise(){
      for(int i = 0; i < 4; i++){
        menuFramesYPos[i] = menuFramesYPos[i]-1*SCALESIZE;  
      }
      characterText->setY(characterText->getY() - 1*SCALESIZE);
      levelText->setY(levelText->getY() - 1*SCALESIZE);
      scoreboardText->setY(scoreboardText->getY() - 1*SCALESIZE);
      optionsText->setY(optionsText->getY() - 1*SCALESIZE);

      if(typeStartYPos < SCREEN_HEIGHT){
        typeStartYPos+=1*SCALESIZE;
      }

      currentBorderRect.y-=1*SCALESIZE;
      currentOutlineRect.y-=1*SCALESIZE;

    }

    void setRaiseMenu(bool value){
      raiseMenu = value;
    }

    void loadFromRenderedText()
    {
      free();

      SDL_Surface* textSurface = TTF_RenderText_Solid(font, startString, CODE_COLOR);
      SDL_Surface* textSurfaceShadow = TTF_RenderText_Solid(font, startString, SHADOW_COLOR);
      typeStart = SDL_CreateTextureFromSurface(renderer, textSurface);
      typeStartShadow = SDL_CreateTextureFromSurface(renderer, textSurfaceShadow);
      typeStartWidth = textSurface->w;
      typeStartHeight = textSurface->h;
      SDL_FreeSurface(textSurface);
      SDL_FreeSurface(textSurfaceShadow);
       
      typeStartXPos = SCREEN_WIDTH/2 - typeStartWidth/2; 
      typeStartYPos = GROUND_VALUE; 
    }

    void loadTipText(){
      
      SDL_Surface* textSurface = TTF_RenderText_Solid(font, "TIP: ", MENU_FONT_COLOR); 
      SDL_Surface* textSurfaceShadow = TTF_RenderText_Solid(font, "TIP: ", MENU_SHADOW_FONT_COLOR);
      tipText = SDL_CreateTextureFromSurface(renderer, textSurface);
      tipTextShadow = SDL_CreateTextureFromSurface(renderer, textSurfaceShadow);
      tipTextWidth = textSurface->w;
      tipTextHeight = textSurface->h;
      SDL_FreeSurface(textSurface);
      SDL_FreeSurface(textSurfaceShadow);
       
      tipTextXPos = TIP_TEXT_XPOS*SCALESIZE;
      tipTextYPos = TIP_TEXT_YPOS*SCALESIZE; 
    
      tipSentenceText = new Word(renderer, 16*SCALESIZE, 25*SCALESIZE, "- Spacebar pauses the game.", 1, MENU_FONT_COLOR, SHADOW_COLOR, 5*SCALESIZE, .1*SCALESIZE); 
    
    }

    void loadMenuFrameText(){

      characterText = new Word(renderer, menuFramesXPos[0] + 3*SCALESIZE, menuFramesYPos[0] + .5*SCALESIZE, "CHARACTER", 0, CODE_COLOR, SHADOW_COLOR, MAIN_MENU_FONT_SIZE, 0);
      
      levelText = new Word(renderer, menuFramesXPos[1] + 7*SCALESIZE, menuFramesYPos[1] + .5*SCALESIZE, "LEVEL", 0, CODE_COLOR, SHADOW_COLOR, MAIN_MENU_FONT_SIZE, 0);
     
      scoreboardText = new Word(renderer, menuFramesXPos[2] + 2*SCALESIZE, menuFramesYPos[2] + .5*SCALESIZE, "HIGH-SCORES", 0, CODE_COLOR, SHADOW_COLOR, MAIN_MENU_FONT_SIZE, 0);

      optionsText = new Word(renderer, menuFramesXPos[3] + 5*SCALESIZE, menuFramesYPos[3] + .5*SCALESIZE, "OPTIONS", 0, CODE_COLOR, SHADOW_COLOR, MAIN_MENU_FONT_SIZE, 0);

    }

    void render(){
      if(raiseMenu){
        raise();
      }
      if(menuDisplay>=1 && menuDisplay <=5){
        if(transition && !scrollDownPrevFrame){
          displayPreviousBorder(); 
          displayPreviousMenuFrame(); 
          if(prevBorderType==2) 
            characterText->render();
          else if(prevBorderType==3)
            levelText->render();
          else if(prevBorderType==4)
            scoreboardText->render();
          else if(prevBorderType==5)
            optionsText->render();
        }
        displayBorder();
        displayMenu(); 
        if(!transition || prevBorderType!=2) 
          characterText->render();
        if(!transition || prevBorderType!=3)
          levelText->render();
        if(!transition || prevBorderType!=4)
          scoreboardText->render();
        if(!transition || prevBorderType!=5)
          optionsText->render();
        if(scrollDownPrevFrame){
          displayPreviousBorder(); 
          displayPreviousMenuFrame(); 
        }
      }  
      else if(menuDisplay==6){
        displayPauseMenu();
        return;
      } 
      floatText(); 
      SDL_Rect renderQuad = {typeStartXPos+.3*SCALESIZE, typeStartYPos+.3*SCALESIZE, typeStartWidth, typeStartHeight};
      SDL_RenderCopyEx(renderer, typeStartShadow, NULL, &renderQuad, 0.0, NULL, SDL_FLIP_NONE);
      renderQuad = {typeStartXPos, typeStartYPos, typeStartWidth, typeStartHeight};
      SDL_RenderCopyEx(renderer, typeStart, NULL, &renderQuad, 0.0, NULL, SDL_FLIP_NONE);
    
    }

    
    void displayMenuFrames(){
      for(int i = 0; i < 4; i++){
        if(i+2 != prevBorderType){ 
          SDL_Rect renderQuad = {menuFramesXPos[i], menuFramesYPos[i], menuFrames[i].w*SCALESIZE, menuFrames[i].h*SCALESIZE};
          SDL_RenderCopy(renderer, objectTexture, &menuFrames[i], &renderQuad);
        }
        else if(!transition){
          SDL_Rect renderQuad = {menuFramesXPos[i], menuFramesYPos[i], menuFrames[i].w*SCALESIZE, menuFrames[i].h*SCALESIZE};
          SDL_RenderCopy(renderer, objectTexture, &menuFrames[i], &renderQuad);
        }

      }
      
      if(!characterText){
        loadMenuFrameText();
      } 
    }

    void displayMenu(){
      
      displayMenuFrames(); 
     
      if(menuDisplay == 1){
        displayTipMenu();
      }
      else if(menuDisplay == 2){
        displayCharacterMenu();
      }
      else if(menuDisplay == 3){
        displayLevelMenu();
      }
      else if(menuDisplay == 4){
        displayScoresMenu();
      }
      else if(menuDisplay == 5){
        displayOptionsMenu();
      }
      
      displayMenuFrames(); 
    
    }				

    void displayTipMenu(){
      if(!tipText){
        loadTipText();
      }
      
      if(borderType != menuDisplay){ 
        makeBorder(100*SCALESIZE, tipTextHeight+tipTextYPos, SCREEN_WIDTH/2 - (100*SCALESIZE)/2,tipTextYPos-2*SCALESIZE);
      }

      
      SDL_Rect renderQuad = {currentBorderRect.x + 2*SCALESIZE, currentBorderRect.y + 2*SCALESIZE, tipTextWidth, tipTextHeight};
      SDL_RenderCopyEx(renderer, tipText, NULL, &renderQuad, 0.0, NULL, SDL_FLIP_NONE);
      renderQuad = {currentBorderRect.x + 2*SCALESIZE + .2*SCALESIZE, currentBorderRect.y + 2*SCALESIZE +.2*SCALESIZE, tipTextWidth, tipTextHeight};
      SDL_RenderCopyEx(renderer, tipTextShadow, NULL, &renderQuad, 0.0, NULL, SDL_FLIP_NONE);
      
      tipSentenceText->setX(currentBorderRect.x + 2*SCALESIZE); 
      tipSentenceText->setY(currentBorderRect.y + 5*SCALESIZE); 
      tipSentenceText->render();
    }

    void displayCharacterMenu(){
      if(borderType != menuDisplay){ 
        makeBorder(SCREEN_WIDTH - (2*SCALESIZE), SCREEN_HEIGHT/2, SCALESIZE , 0);
      }
    }

    void displayLevelMenu(){
      if(borderType != menuDisplay){ 
        makeBorder(SCREEN_WIDTH - (2*SCALESIZE), SCREEN_HEIGHT/2, SCALESIZE , 0);
      }
    }
    
    void displayScoresMenu(){
      if(borderType != menuDisplay){ 
        makeBorder(SCREEN_WIDTH - (2*SCALESIZE), SCREEN_HEIGHT/2, SCALESIZE , 0);
      }
    }
    
    void displayOptionsMenu(){
      if(borderType != menuDisplay){ 
        makeBorder(SCREEN_WIDTH - (2*SCALESIZE), SCREEN_HEIGHT/2, SCALESIZE , 0);
      }
    }
    
    void displayPauseMenu(){
      borderType=6;   
      prevBorderType=0; 
      SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
      currentBorderRect = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
      SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0x66);
      SDL_RenderFillRect(renderer, &currentBorderRect);
      SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);
      if(!pauseText){
        pauseText = new Word(renderer, SCREEN_WIDTH/2 - 13*SCALESIZE, SCREEN_HEIGHT/2 - 5*SCALESIZE, "PAUSED", 1, CODE_COLOR, SHADOW_COLOR, 10*SCALESIZE, .3*SCALESIZE); 
      }
      pauseText->render();
    }

    void makeBorder(double width, double height, double x, double y){
      prevBorderType = borderType; 
      borderType = menuDisplay;
      previousBorderRect = currentBorderRect;
      previousOutlineRect = currentOutlineRect;
      currentBorderRect = {x, y - height + MENU_FRAMES_SPAWN_Y, width, height};
      currentOutlineRect = {currentBorderRect.x+1*SCALESIZE, currentBorderRect.y + SCALESIZE, currentBorderRect.w-2*SCALESIZE, currentBorderRect.h-2*SCALESIZE};
    
      transition= true; 
    }

    void displayBorder(){
      if(borderType == 0){
        return;
      } 
      else if(borderType == 1 && !raiseMenu){ 
        if(currentBorderRect.y < tipTextYPos){
          currentBorderRect.y+=1*SCALESIZE;
          currentOutlineRect.y+=1*SCALESIZE; 
        } 
      }
      else if(currentBorderRect.y < MENU_FRAMES_SPAWN_Y-SCALESIZE & !raiseMenu){
        currentBorderRect.y+=1*SCALESIZE;
        currentOutlineRect.y+=1*SCALESIZE; 
        
        if(borderType >= 2 && borderType <=5){
         
          if(borderType == 2)
            characterText->setY(characterText->getY()+1*SCALESIZE);    
          else if(borderType == 3)
            levelText->setY(levelText->getY()+1*SCALESIZE);    
          else if(borderType == 4)
            scoreboardText->setY(scoreboardText->getY()+1*SCALESIZE);    
          else if(borderType == 5)
            optionsText->setY(optionsText->getY()+1*SCALESIZE);    
          
          menuFramesYPos[borderType-2]+=1*SCALESIZE; 
        }
      }
      SDL_SetRenderDrawColor(renderer, 65, 111, 153, 0xFF);
      SDL_RenderFillRect(renderer, &currentBorderRect);
      SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
      SDL_RenderFillRect(renderer, &currentOutlineRect);
    }
    
    void displayPreviousBorder(){
      if(prevBorderType == -1 || prevBorderType == 0 || prevBorderType == 6){
        transition=false; 
        return;
      }
      if(previousBorderRect.y > (0-previousBorderRect.h+MENU_FRAMES_SPAWN_Y)){
        previousBorderRect.y-=1*SCALESIZE;
        previousOutlineRect.y-=1*SCALESIZE; 
        SDL_SetRenderDrawColor(renderer, 65, 111, 153, 0xFF);
        SDL_RenderFillRect(renderer, &previousBorderRect);
        SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderFillRect(renderer, &previousOutlineRect);
        
        if(prevBorderType >= 2 && prevBorderType <=5){
          if(prevBorderType == 2)
            characterText->setY(characterText->getY()-1*SCALESIZE);    
          else if(prevBorderType == 3)
            levelText->setY(levelText->getY()-1*SCALESIZE);    
          else if(prevBorderType == 4)
            scoreboardText->setY(scoreboardText->getY()-1*SCALESIZE);    
          else if(prevBorderType == 5)
            optionsText->setY(optionsText->getY()-1*SCALESIZE);    
          menuFramesYPos[prevBorderType-2]-=1*SCALESIZE; 
        }
      }
      else{
        if(scrollDownPrevFrame){
          if(prevBorderType >= 2 && prevBorderType <=5){
            if(prevBorderType == 2){
              if(characterText->getY()<4*SCALESIZE){
                characterText->setY(characterText->getY()+1*SCALESIZE);    
                menuFramesYPos[prevBorderType-2] += 1*SCALESIZE;
              }
              else{
                scrollDownPrevFrame=false;
                transition = false;
              }
            }
            else if(prevBorderType == 3)
              if(levelText->getY()<4*SCALESIZE){
                levelText->setY(levelText->getY()+1*SCALESIZE);    
                menuFramesYPos[prevBorderType-2] += 1*SCALESIZE;
              }
              else{
                scrollDownPrevFrame=false;
                transition = false;
              }
            else if(prevBorderType == 4)
              if(scoreboardText->getY()<4*SCALESIZE){
                scoreboardText->setY(scoreboardText->getY()+1*SCALESIZE);    
                menuFramesYPos[prevBorderType-2] += 1*SCALESIZE;
              }
              else{
                scrollDownPrevFrame=false;
                transition = false;
              }
            else if(prevBorderType == 5)
              if(optionsText->getY()<4*SCALESIZE){
                optionsText->setY(optionsText->getY()+1*SCALESIZE);    
                menuFramesYPos[prevBorderType-2] += 1*SCALESIZE;
              }
              else{
                scrollDownPrevFrame=false;
                transition = false;
              }

          }
        }
        else if(prevBorderType >= 2 && prevBorderType <=5){
          if(prevBorderType == 2)
            characterText->setY(0*SCALESIZE);    
          else if(prevBorderType == 3)
            levelText->setY(0*SCALESIZE);    
          else if(prevBorderType == 4)
            scoreboardText->setY(0*SCALESIZE);    
          else if(prevBorderType == 5)
            optionsText->setY(0*SCALESIZE);    
          menuFramesYPos[prevBorderType-2] = 0*SCALESIZE;
          scrollDownPrevFrame = true;
        }
        else{
          transition = false;
        }
      } 
    
    }
    void displayPreviousMenuFrame(){
          SDL_Rect renderQuad = {menuFramesXPos[prevBorderType-2], menuFramesYPos[prevBorderType-2], menuFrames[prevBorderType-2].w*SCALESIZE, menuFrames[prevBorderType-2].h*SCALESIZE};
          SDL_RenderCopy(renderer, objectTexture, &menuFrames[prevBorderType-2], &renderQuad);
    }

    void floatText(){
      if(floatUp){
        typeStartYPos -= .1*SCALESIZE;
      }
      else if(typeStartYPos < GROUND_VALUE){ 
        typeStartYPos += .1*SCALESIZE;
      }
      if(typeStartYPos >= GROUND_VALUE){
        if((SDL_GetTicks() - floatTime) > 1000){ 
          floatUp = true;
          floatTime = SDL_GetTicks();
        }
      }
      else if(typeStartYPos <= (GROUND_VALUE - 1*SCALESIZE)){
        floatUp = false; 
      } 
    }

    void setMenuDisplay(int value){ 
      if(!transition) 
        menuDisplay = value;
    }
    
    int getMenuDisplay(){ return menuDisplay;}

    void setObjectTexture(SDL_Texture* texture){
      this->objectTexture = texture;
  }

  private:
    Word* characterText = NULL; 
    Word* levelText = NULL;
    Word* scoreboardText = NULL;
    Word* optionsText = NULL;
    Word* tipSentenceText = NULL;
    Word* pauseText = NULL; 
    
    SDL_Renderer* renderer = NULL;
    SDL_Rect menuFrames[4]; 
    int menuFramesYPos[4] = {4*SCALESIZE, 4*SCALESIZE, 4*SCALESIZE, 4*SCALESIZE};
    int menuFramesXPos[4] = {OFFSET + 1*SCALESIZE,OFFSET +  25*SCALESIZE,OFFSET +  80*SCALESIZE,OFFSET +  104*SCALESIZE};

    SDL_Texture* typeStart = NULL;
    SDL_Texture* typeStartShadow = NULL; 
    SDL_Texture* tipText = NULL;
    double tipTextXPos = 0;
    double tipTextYPos= 0;
    double tipTextWidth = 0;
    double tipTextHeight = 0;
    SDL_Texture* tipTextShadow = NULL;
    SDL_Texture* objectTexture = NULL;
    
    TTF_Font* font = NULL;
   
    int menuDisplay = 1; 
    double typeStartXPos = 0;
    double typeStartYPos = 0;
    double typeStartWidth = 0;
    double typeStartHeight = 0;
    char* startString = "t y p e   \" s t a r t \"   t o   b e g i n   g a m e ";
    bool floatUp = false;
    Uint32 floatTime = 0;

    SDL_Rect currentBorderRect;
    SDL_Rect currentOutlineRect;
    SDL_Rect previousBorderRect;
    SDL_Rect previousOutlineRect;
    bool transition = false; 
    bool scrollDownPrevFrame = false;
    bool raiseMenu = false;
    int borderType = 0;
    int prevBorderType = -1;
    
   
};

#endif
