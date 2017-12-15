#include <SDL2/SDL_ttf.h>

#ifndef Scorer_h
#define Scorer_h


class Scorer
{
  public:
    Scorer(char string[6], SDL_Renderer* renderer,double x, double y)
    {
      this->renderer = renderer; 
      strcpy(scoreString, string); 
      loadFont();
      loadTexture(); 
      this->x = x;
      this->y = y;
      angle = 65 + (rand()%20);
      movement = (rand()%2);
      velocity = 10 + (rand()%3);	
      randGroundValue = GROUND_VALUE + (rand()%3*(int)SCALESIZE);	
      lifetime = SDL_GetTicks();	
    }

    ~Scorer()
    {
      free();
    }

    void free()
    {
      if(scoreTexture!=NULL){	
        SDL_DestroyTexture(scoreTexture);	
      }      
      if(shadowTexture!=NULL){
        SDL_DestroyTexture(shadowTexture);	
      }
      TTF_CloseFont(font); 
    }
  
    void loadFont()
    {
      font = TTF_OpenFont(CODE_FONT, CHARACTER_SCORE_FONT_SIZE);
      //TTF_SetFontStyle(font, TTF_STYLE_BOLD);
      if(font == NULL){
        printf("Error loading character font\n");
      }

    }

    void loadTexture(){
      SDL_Surface* textSurface = TTF_RenderText_Solid(font, scoreString, {142,74,74});
      SDL_Surface* shadowSurface = TTF_RenderText_Solid(font, scoreString, SHADOW_COLOR);
      
      if(!textSurface){
        printf("Error making textSurface for character\n");
      }
      else{
        scoreTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
        shadowTexture = SDL_CreateTextureFromSurface(renderer, shadowSurface);
        width = textSurface->w;
        height = textSurface->h;

        if(!scoreTexture){
          printf("Error creating score texture for character\n");
        }

        SDL_FreeSurface(textSurface);
        SDL_FreeSurface(shadowSurface);

      }
    }

    void move(){
        
      if(onGround){
        SDL_SetTextureBlendMode(scoreTexture, SDL_BLENDMODE_BLEND);
        SDL_SetTextureAlphaMod(scoreTexture, alpha);
        
        SDL_SetTextureBlendMode(shadowTexture, SDL_BLENDMODE_BLEND);
        SDL_SetTextureAlphaMod(shadowTexture, alpha);
        return;
      }
      
      double radians = angle*PI/180.0;
      relY = ((abs(relX))*(tan(radians)))-(((GRAVITY)*(pow((abs(relX)),2)))/(2.0*(pow(velocity,2)*pow(cos(radians),2))));

      relX -= .1/speed;
      y -= relY/speed;
      
      if(movement)	
        x -= relX/speed;
      else
        x += relX/speed;

      
      groundContact();	
    }

    void render(){
      SDL_Rect renderQuad = {x+.2*SCALESIZE, y+.2*SCALESIZE, width, height};
      SDL_RenderCopyEx(renderer, shadowTexture, NULL, &renderQuad, NULL, NULL, SDL_FLIP_NONE);
      
      renderQuad = {x, y, width, height};
      SDL_RenderCopyEx(renderer, scoreTexture, NULL, &renderQuad, NULL, NULL, SDL_FLIP_NONE);
    }

    bool groundContact(){
      if(y >= randGroundValue){
        y = randGroundValue;
        onGround = true;	
        lifetime = SDL_GetTicks(); 
        return true;
      }
      return false;
    }

    bool getOnGround(){
      return onGround;
    }

    Uint32 getLifetime(){
      return SDL_GetTicks()-lifetime;
    }

    void fade(){
      alpha--;
    }
            
    Uint8 getAlpha()
    {
      return alpha;
    }
    
    void setSpeed(double value){ speed = value;} 
    double getWidth(){ return width;}
    double getHeight(){ return height;}
    double getXPos(){ return x;}	
    double getYPos(){ return y;}	
    SDL_Texture* getText(){ return scoreTexture;}
    SDL_Texture* getShadowText(){ return shadowTexture;}

  private:
    SDL_Renderer* renderer = NULL;
    SDL_Texture* scoreTexture = NULL;
    SDL_Texture* shadowTexture = NULL;	
    TTF_Font* font = NULL; 
    double width = 0;
    double height = 0;
    double x = 0;
    double y = 0;
    double relX = 0;
    double relY = 0;
    int angle = 0;	
    int velocity = 0;
    int movement = 0;
    int randGroundValue = 0;
    Uint32 lifetime;
    bool onGround = false;
    Uint8 alpha = 255;
    char scoreString[6];
    double speed = 1;

};

#endif
