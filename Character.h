
#ifndef Character_h
#define Character_h

class Character
{
  public:
    Character(SDL_Renderer* renderer)
    {
      this->renderer = renderer;
      blinkTime = SDL_GetTicks();	
      typeTime = SDL_GetTicks();	
      setupClips();	
      loadFont();	
    }

    ~Character()
    {
      free();
    }

    void free()
    {
    
    }

    void loadFont()
    {
      font = TTF_OpenFont(CODE_FONT, CHARACTER_SCORE_FONT_SIZE);
      if(font == NULL){
        printf("Error loading character font\n");
      }

    }
    
    class ScoreText
    {
      public:
        ScoreText(SDL_Texture* text, SDL_Texture* shadowText, int width, int height, int x, int y)
        {
          this->text = text;
          this->shadowText = shadowText;	
          this->width = width;
          this->height = height;
          this->x = x;
          this->y = y;
          angle = 65 + (rand()%20);
          movement = (rand()%2);
          velocity = 10 + (rand()%3);	
          randGroundValue = GROUND_VALUE + (rand()%30);	
          lifetime = SDL_GetTicks();	
        }

        ~ScoreText()
        {
          free();
        }

        void free()
        {
          if(text!=NULL)	
            SDL_DestroyTexture(text);	
          if(shadowText!=NULL)	
            SDL_DestroyTexture(shadowText);	
        }
        
        void move(){
            
          if(onGround){
            SDL_SetTextureBlendMode(text, SDL_BLENDMODE_BLEND);
            SDL_SetTextureAlphaMod(text, alpha);
            
            
            SDL_SetTextureBlendMode(shadowText, SDL_BLENDMODE_BLEND);
            SDL_SetTextureAlphaMod(shadowText, alpha);
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
        SDL_Texture* getText(){ return text;}
        SDL_Texture* getShadowText(){ return shadowText;}

      private:

        SDL_Texture* text = NULL;
        SDL_Texture* shadowText = NULL;	
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

    };


    void loadFromRenderedText()
    {
      free();

      ScoreText* scoreText;	
      char scoreString[6];
      strcpy(scoreString, "+");
      strcat(scoreString, std::to_string(scoring).c_str());
      
      if(scoreType == 1){
        scoreColor = {114, 224, 66};
      }
      else if(scoreType == 2){
        scoreColor = {113, 172, 224};
      }
      SDL_Surface* textSurface = TTF_RenderText_Solid(font, scoreString, scoreColor);
      SDL_Surface* shadowSurface = TTF_RenderText_Solid(font, scoreString, SHADOW_COLOR);
      
      if(!textSurface){
        printf("Error making textSurface for character\n");
      }
      else{
        SDL_Texture* scoreTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
        SDL_Texture* shadowTexture = SDL_CreateTextureFromSurface(renderer, shadowSurface);
                
        if(!scoreTexture){
          printf("Error creating score texture for character\n");
        }
        else{
          scoreText = new ScoreText(scoreTexture, shadowTexture, textSurface->w, textSurface->h, CHARACTER_SCORE_X, CHARACTER_SCORE_Y);
        }

        SDL_FreeSurface(textSurface);
        SDL_FreeSurface(shadowSurface);

      }

      scoreVector.push_back(scoreText);

      scoring = 0;
      scoreType = 0;

    }
                                      
    void freeze(){
      frozen = true;
    }
    void unfreeze(){
      frozen = false;
    }

    void render()
    {
      SDL_Rect renderQuad = {60,790, charClips[0].w, charClips[0].h};
      SDL_RenderCopy(renderer, objectTexture, &charClips[0], &renderQuad);
     
      if(!heavyHead){ 
        renderQuad = {80,720, charHead.w, charHead.h};
        SDL_RenderCopy(renderer, objectTexture, &charHead, &renderQuad);
      } 
      else{
        if((SDL_GetTicks() - heavyHeadTime) > LETTER_LIFETIME){
          heavyHead = false;
        }
        renderQuad = {80,730, charHead.w, charHead.h};
        SDL_RenderCopy(renderer, objectTexture, &charHead, &renderQuad);
      } 
      
      if(!frozen){
        tryToType();	
        tryToScore();			
        tryToBlink();

        if(!scoreVector.empty()){
          for(int i = 0; i < scoreVector.size(); i++){
            if(scoreVector[i]->getLifetime() > LETTER_LIFETIME){
              scoreVector[i]->fade();

              if(!scoreVector[i]->getAlpha()){	
                ScoreText* temp = scoreVector[i];
                scoreVector.erase(scoreVector.begin()+i);
                delete(temp);
              }
            }
            
            scoreVector[i]->move();	
          }
        }
      }
      
      for(int i = 0; i < scoreVector.size(); i++){		
        renderQuad = {scoreVector[i]->getXPos()+2, scoreVector[i]->getYPos()+2, scoreVector[i]->getWidth(), scoreVector[i]->getHeight()};
        SDL_RenderCopyEx(renderer, scoreVector[i]->getShadowText(), NULL, &renderQuad, NULL, NULL, SDL_FLIP_NONE);

        renderQuad = {scoreVector[i]->getXPos(), scoreVector[i]->getYPos(), scoreVector[i]->getWidth(), scoreVector[i]->getHeight()};
        SDL_RenderCopyEx(renderer, scoreVector[i]->getText(), NULL, &renderQuad, NULL, NULL, SDL_FLIP_NONE);
      }
    }

    void tryToScore()
    {
      if(scoring){
        loadFromRenderedText();
      }
    }		
      
    void tryToType()
    {
      if(typing){
        typeTime = SDL_GetTicks();
        typing = false;		
        charIndex++;
        if(charIndex == 4)
          charIndex = 1;
      }
      else if((SDL_GetTicks() - typeTime) < 300){
        SDL_Rect renderQuad = {60,790, charClips[0].w, charClips[0].h};
        SDL_RenderCopy(renderer, objectTexture, &charClips[charIndex], &renderQuad);	
      }
    }
        
    void setupClips()
    {
      for(int i = 0; i < 4; i++){
        charClips[i].x = MAIN_CHARACTER_OBJECT_X*i;
        charClips[i].y = MAIN_CHARACTER_OBJECT_Y;
        charClips[i].w = MAIN_CHARACTER_OBJECT_W;
        charClips[i].h = MAIN_CHARACTER_OBJECT_H;
      }

      charHead.x = 20;
      charHead.y = 740;
      charHead.w = 70;
      charHead.h = 70;
    }

    void tryToBlink()
    {
      if((SDL_GetTicks() - blinkTime) > 3000){
        blink = true;
        blinkTime = SDL_GetTicks();	
      }

      if(blink && ((SDL_GetTicks() - blinkTime) < 100)){
        if(!heavyHead){ 
          SDL_Rect blinkingEyes = {460,750,40,10};
          SDL_Rect renderQuad = {100,750, blinkingEyes.w, blinkingEyes.h};
          SDL_RenderCopy(renderer, objectTexture, &blinkingEyes, &renderQuad);
        }
        else{
          SDL_Rect blinkingEyes = {460,750,40,10};
          SDL_Rect renderQuad = {100,760, blinkingEyes.w, blinkingEyes.h};
          SDL_RenderCopy(renderer, objectTexture, &blinkingEyes, &renderQuad);
        } 
      }
      else if(blink){
        blink = false;
      }
    }

    void setObjectTexture(SDL_Texture* texture)
    {
      this->objectTexture = texture;
    }

    void setHeavyHead(bool value)
    {
      this->heavyHead = value;
      heavyHeadTime = SDL_GetTicks(); 
    }

    void setTyping(bool value)
    {
      if(this->typing != value){
        this->typing = value;
      }
    }

    void setScoring(int value, int type)
    {
      this->scoring = value;
      this->scoreType = type;
    }

    bool collisionCheck(int x, int y){
      if(x >= 80 && x <= 140){
        if(y >= 710 && y <= 760){
          heavyHeadTime = SDL_GetTicks(); 
          return true;
        }
      }
      return false;
    }

  private:
    SDL_Texture* objectTexture = NULL;
    SDL_Renderer* renderer = NULL;
    SDL_Rect charClips[4];
    SDL_Rect charHead; 
    SDL_Color scoreColor;	
    TTF_Font* font = NULL;	
    int charIndex = 0;
    Uint32 blinkTime = 0;
    Uint32 typeTime = 0;
    Uint32 heavyHeadTime = 0; 
    bool blink = false;
    bool heavyHead = false;
    bool typing = false;
    bool frozen = false;
    int scoring = 0;
    int scoreType = 0;
    std::vector<ScoreText*> scoreVector;

};

#endif
