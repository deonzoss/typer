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
        menuFrames[i].w = 230;
        menuFrames[i].h = 50;
        menuFrames[i].x = 10;
        menuFrames[i].y = 580; 
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
       
      tipTextXPos = 200;
      tipTextYPos = 200; 
    
      tipSentenceText = new Word(renderer, 160, 250, "- Spacebar pauses the game.", 1, MENU_FONT_COLOR, SHADOW_COLOR, 50, 1); 
    
    }

    void loadMenuFrameText(){

      characterText = new Word(renderer, menuFramesXPos[0] + 30, menuFramesYPos[0] + 5, "CHARACTER", 0, CODE_COLOR, SHADOW_COLOR, MAIN_MENU_FONT_SIZE, 0);
      levelText = new Word(renderer, menuFramesXPos[1] + 70, menuFramesYPos[1] + 5, "LEVEL", 0, CODE_COLOR, SHADOW_COLOR, MAIN_MENU_FONT_SIZE, 0);
      scoreboardText = new Word(renderer, menuFramesXPos[2] + 20, menuFramesYPos[2] + 5, "HIGH-SCORES", 0, CODE_COLOR, SHADOW_COLOR, MAIN_MENU_FONT_SIZE, 0);
      optionsText = new Word(renderer, menuFramesXPos[3] + 50, menuFramesYPos[3] + 5, "OPTIONS", 0, CODE_COLOR, SHADOW_COLOR, MAIN_MENU_FONT_SIZE, 0);

    }

    void render(){
      if(menuDisplay){
        displayMenu(); 
        if(menuDisplay == 6){
          return;
        } 
      }  
      floatText(); 
      SDL_Rect renderQuad = {typeStartXPos+3, typeStartYPos+3, typeStartWidth, typeStartHeight};
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
      
      makeBorder(1000, 380);

      SDL_Rect renderQuad = {tipTextXPos, tipTextYPos, tipTextWidth, tipTextHeight};
      SDL_RenderCopyEx(renderer, tipText, NULL, &renderQuad, 0.0, NULL, SDL_FLIP_NONE);
      renderQuad = {tipTextXPos+2, tipTextYPos+2, tipTextWidth, tipTextHeight};
      SDL_RenderCopyEx(renderer, tipTextShadow, NULL, &renderQuad, 0.0, NULL, SDL_FLIP_NONE);
    }

    void displayCharacterMenu(){
      makeBorder(1000, 700);
    }

    void displayLevelMenu(){
      makeBorder(1000, 600);
    }
    
    void displayScoresMenu(){
      makeBorder(1000, 500);
    }
    
    void displayOptionsMenu(){
      makeBorder(1000, 400);
    }
    
    void displayPauseMenu(){
      SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
      borderRect = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
      SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0x66);
      SDL_RenderFillRect(renderer, &borderRect);
      SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);
      if(!pauseText){
        pauseText = new Word(renderer, SCREEN_WIDTH/2 - 130, SCREEN_HEIGHT/2 - 50, "PAUSED", 1, CODE_COLOR, SHADOW_COLOR, 100, 3); 
      }
      pauseText->render();

    }

    void makeBorder(int width, int height){
      borderRect = {SCREEN_WIDTH/2 - 500, SCREEN_HEIGHT/2 - 320, width, height};
      SDL_SetRenderDrawColor(renderer, 65, 111, 153, 0xFF);
      SDL_RenderFillRect(renderer, &borderRect);
      outlineRect = {borderRect.x+10, borderRect.y+10, borderRect.w-20, borderRect.h-20};
      SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
      SDL_RenderFillRect(renderer, &outlineRect);
    }
          
    void floatText(){
      if(floatUp){
        typeStartYPos -= 1;
      }
      else if(typeStartYPos < GROUND_VALUE){ 
        typeStartYPos += 1;
      }
      if(typeStartYPos >= GROUND_VALUE){
        if((SDL_GetTicks() - floatTime) > 1000){ 
          floatUp = true;
          floatTime = SDL_GetTicks();
        }
      }
      else if(typeStartYPos <= (GROUND_VALUE - 10)){
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
    int menuFramesYPos[4] = {40, 40, 40, 40};
    int menuFramesXPos[4] = {10, 250, 800, 1040};

    SDL_Texture* typeStart = NULL;
    SDL_Texture* typeStartShadow = NULL;
    
    SDL_Texture* tipText = NULL;
    int tipTextXPos = 0;
    int tipTextYPos= 0;
    int tipTextWidth = 0;
    int tipTextHeight = 0;
    SDL_Texture* tipTextShadow = NULL;
    SDL_Texture* objectTexture = NULL;
    
    TTF_Font* font = NULL;
   
    int menuDisplay = 0; 
    int typeStartXPos = 0;
    int typeStartYPos = 0;
    int typeStartWidth = 0;
    int typeStartHeight = 0;
    char* startString = "t y p e   \" s t a r t \"   t o   b e g i n   g a m e ";
    bool floatUp = false;
    Uint32 floatTime = 0;
};

#endif
