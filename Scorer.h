#ifndef Scorer_h
#define Scorer_h


class Scorer
{
  public:
    Scorer(char string[6], SDL_Renderer* renderer,int x, int y)
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
      randGroundValue = GROUND_VALUE + (rand()%30);	
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
      if(font == NULL){
        printf("Error loading character font\n");
      }

    }

    void loadTexture(){
      SDL_Surface* textSurface = TTF_RenderText_Solid(font, scoreString, {241,40,40});
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

      relX -= .1;
      y -= relY;
      
      if(movement)	
        x -= relX;
      else
        x += relX;

      
      groundContact();	
    }

    void render(){
      SDL_Rect renderQuad = {x+2, y+2, width, height};
      SDL_RenderCopyEx(renderer, shadowTexture, NULL, &renderQuad, NULL, NULL, SDL_FLIP_NONE);
      
      renderQuad = {x, y, width, height};
      SDL_RenderCopyEx(renderer, scoreTexture, NULL, &renderQuad, NULL, NULL, SDL_FLIP_NONE);
    }

    bool groundContact(){
      if(y >= randGroundValue){
        y = randGroundValue;
        onGround = true;	
        return true;
      }
      return false;
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
    
    int getWidth(){ return width;}
    int getHeight(){ return height;}
    int getXPos(){ return x;}	
    int getYPos(){ return y;}	
    SDL_Texture* getText(){ return scoreTexture;}
    SDL_Texture* getShadowText(){ return shadowTexture;}

  private:
    SDL_Renderer* renderer = NULL;
    SDL_Texture* scoreTexture = NULL;
    SDL_Texture* shadowTexture = NULL;	
    TTF_Font* font = NULL; 
    int width = 0;
    int height = 0;
    int x = 0;
    int y = 0;
    double relX = 0;
    int relY = 0;
    int angle = 0;	
    int velocity = 0;
    int movement = 0;
    int randGroundValue = 0;
    Uint32 lifetime;
    bool onGround = false;
    Uint8 alpha = 255;
    char scoreString[6];
};

#endif
