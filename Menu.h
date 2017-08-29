#include "Word.h"
#ifndef Menu_h
#define Menu_h

class Menu
{
  public:
    Menu(SDL_Renderer* renderer)
    {
      this->renderer = renderer;
      menuDisplay = 1; 
      loadFont();
      for(int i = 0; i < 4; i++){
        menuFrames[i].w = 23*SCALESIZE;
        menuFrames[i].h = 5*SCALESIZE;
        menuFrames[i].x = 1*SCALESIZE;
        menuFrames[i].y = 58*SCALESIZE; 
      }
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
       
      tipTextXPos = 20*SCALESIZE;
      tipTextYPos = 20*SCALESIZE; 
    
      tipSentenceText = new Word(renderer, 16*SCALESIZE, 25*SCALESIZE, "- Spacebar pauses the game.", 1, MENU_FONT_COLOR, SHADOW_COLOR, 5*SCALESIZE, .1*SCALESIZE); 
    
    }

    void loadMenuFrameText(){

      characterText = new Word(renderer, menuFramesXPos[0] + 3*SCALESIZE, menuFramesYPos[0] + .5*SCALESIZE, "CHARACTER", 0, CODE_COLOR, SHADOW_COLOR, MAIN_MENU_FONT_SIZE, 0);
      
      levelText = new Word(renderer, menuFramesXPos[1] + 7*SCALESIZE, menuFramesYPos[1] + .5*SCALESIZE, "LEVEL", 0, CODE_COLOR, SHADOW_COLOR, MAIN_MENU_FONT_SIZE, 0);
     
      scoreboardText = new Word(renderer, menuFramesXPos[2] + 2*SCALESIZE, menuFramesYPos[2] + .5*SCALESIZE, "HIGH-SCORES", 0, CODE_COLOR, SHADOW_COLOR, MAIN_MENU_FONT_SIZE, 0);

      optionsText = new Word(renderer, menuFramesXPos[3] + 5*SCALESIZE, menuFramesYPos[3] + .5*SCALESIZE, "OPTIONS", 0, CODE_COLOR, SHADOW_COLOR, MAIN_MENU_FONT_SIZE, 0);

    }

    void render(){
      if(menuDisplay){
        displayMenu(); 
        if(menuDisplay == 6){
          return;
        } 
      }  
      floatText(); 
      SDL_Rect renderQuad = {typeStartXPos+.3*SCALESIZE, typeStartYPos+.3*SCALESIZE, typeStartWidth, typeStartHeight};
      SDL_RenderCopyEx(renderer, typeStartShadow, NULL, &renderQuad, 0.0, NULL, SDL_FLIP_NONE);
      renderQuad = {typeStartXPos, typeStartYPos, typeStartWidth, typeStartHeight};
      SDL_RenderCopyEx(renderer, typeStart, NULL, &renderQuad, 0.0, NULL, SDL_FLIP_NONE);
    
      characterText->render();
      levelText->render();
      scoreboardText->render();
      optionsText->render();
      tipSentenceText->render();
    }
    
    void displayMenuFrames(){
      for(int i = 0; i < 4; i++){
        SDL_Rect renderQuad = {menuFramesXPos[i], menuFramesYPos[i], menuFrames[i].w, menuFrames[i].h};
        SDL_RenderCopy(renderer, objectTexture, &menuFrames[i], &renderQuad);
      }
      
      if(!characterText){
        loadMenuFrameText();
      } 
    }

    void displayMenu(){
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
      else if(menuDisplay == 6){
        displayPauseMenu();
        return;
      }
      displayMenuFrames(); 
    }				

    void displayTipMenu(){
      if(!tipText){
        loadTipText();
      }
      
      makeBorder(100*SCALESIZE, 38*SCALESIZE);

      SDL_Rect renderQuad = {tipTextXPos, tipTextYPos, tipTextWidth, tipTextHeight};
      SDL_RenderCopyEx(renderer, tipText, NULL, &renderQuad, 0.0, NULL, SDL_FLIP_NONE);
      renderQuad = {tipTextXPos+.2*SCALESIZE, tipTextYPos+.2*SCALESIZE, tipTextWidth, tipTextHeight};
      SDL_RenderCopyEx(renderer, tipTextShadow, NULL, &renderQuad, 0.0, NULL, SDL_FLIP_NONE);
    }

    void displayCharacterMenu(){
      makeBorder(100*SCALESIZE, 70*SCALESIZE);
    }

    void displayLevelMenu(){
      makeBorder(100*SCALESIZE, 60*SCALESIZE);
    }
    
    void displayScoresMenu(){
      makeBorder(100*SCALESIZE, 50*SCALESIZE);
    }
    
    void displayOptionsMenu(){
      makeBorder(100*SCALESIZE, 40*SCALESIZE);
    }
    
    void displayPauseMenu(){
      SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
      borderRect = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
      SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0x66);
      SDL_RenderFillRect(renderer, &borderRect);
      SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);
      if(!pauseText){
        pauseText = new Word(renderer, SCREEN_WIDTH/2 - 13*SCALESIZE, SCREEN_HEIGHT/2 - 5*SCALESIZE, "PAUSED", 1, CODE_COLOR, SHADOW_COLOR, 10*SCALESIZE, .3*SCALESIZE); 
      }
      pauseText->render();

    }

    void makeBorder(double width, double height){
      borderRect = {SCREEN_WIDTH/2 - 50*SCALESIZE, SCREEN_HEIGHT/2 - 32*SCALESIZE, width, height};
      SDL_SetRenderDrawColor(renderer, 65, 111, 153, 0xFF);
      SDL_RenderFillRect(renderer, &borderRect);
      outlineRect = {borderRect.x+1*SCALESIZE, borderRect.y+1*SCALESIZE, borderRect.w-2*SCALESIZE, borderRect.h-2*SCALESIZE};
      SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
      SDL_RenderFillRect(renderer, &outlineRect);
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

    void setMenuDisplay(int value){ menuDisplay = value;}
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
    SDL_Rect outlineRect;
    SDL_Rect borderRect;
    SDL_Rect menuFrames[4]; 
    int menuFramesYPos[4] = {4*SCALESIZE, 4*SCALESIZE, 4*SCALESIZE, 4*SCALESIZE};
    int menuFramesXPos[4] = {1*SCALESIZE, 25*SCALESIZE, 80*SCALESIZE, 104*SCALESIZE};

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
   
    int menuDisplay = 0; 
    double typeStartXPos = 0;
    double typeStartYPos = 0;
    double typeStartWidth = 0;
    double typeStartHeight = 0;
    char* startString = "t y p e   \" s t a r t \"   t o   b e g i n   g a m e ";
    bool floatUp = false;
    Uint32 floatTime = 0;
};

#endif
