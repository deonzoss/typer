
#ifndef Coworker_h
#define Coworker_h

class Coworker
{
  public:
    Coworker(SDL_Renderer* renderer)
    {
      this->renderer = renderer;
      blinkTime = SDL_GetTicks();
      setupClips();
      loadFont();
    }

    ~Coworker()
    {
      free();
    }

    void free()
    {

    }

    void loadFont()
    {
      font= TTF_OpenFont(CODE_FONT, CHARACTER_SCORE_FONT_SIZE);
      if(font==NULL){
        printf("Error loading coworker font\n");
      }
    }
 
    void render()
    {
      SDL_Rect renderQuad = {COWORKER_SPAWN_X,COWORKER_SPAWN_Y, charClips[0].w, charClips[0].h};
      SDL_RenderCopy(renderer, objectTexture, &charClips[0], &renderQuad);
      
      if(!heavyHead){ 
        renderQuad = {COWORKER_SPAWN_X + 130, COWORKER_SPAWN_Y - 20, charHead.w, charHead.h};
        SDL_RenderCopy(renderer, objectTexture, &charHead, &renderQuad);
      } 
      else{
        renderQuad = {COWORKER_SPAWN_X + 130, COWORKER_SPAWN_Y - 10, charHead.w, charHead.h};
        SDL_RenderCopy(renderer, objectTexture, &charHead, &renderQuad);
        if(SDL_GetTicks() - heavyHeadTime >= LETTER_LIFETIME){
          heavyHead = false;
        } 
      }
      
      if(!frozen){
        tryToBlink();
      }
    }

    void tryToBlink(){
      if((SDL_GetTicks() - blinkTime) > 2500){
        blink = true;
        blinkTime = SDL_GetTicks();
      }
      if(blink && ((SDL_GetTicks() - blinkTime) < 100)){
        SDL_Rect blinkingEyes = {450, 830, 40, 10};
        SDL_Rect renderQuad; 
        if(!heavyHead){ 
          renderQuad = {COWORKER_SPAWN_X + 140, COWORKER_SPAWN_Y + 10, blinkingEyes.w, blinkingEyes.h};
        } 
        else{ 
          renderQuad = {COWORKER_SPAWN_X + 140, COWORKER_SPAWN_Y + 20, blinkingEyes.w, blinkingEyes.h};
        } 
        SDL_RenderCopy(renderer, objectTexture, &blinkingEyes, &renderQuad);
      }
      else if(blink){
        blink = false;
      } 
    }

    void freeze(){
      frozen = true;
    }

    void unfreeze(){
      frozen = false;
    }

    void setupClips()
    {
      charHead.x = 440;
      charHead.y = 840;
      charHead.w = 70;
      charHead.h = 70; 
      for(int i = 0; i < 2; i++){
        charClips[i].x = COWORKER_OBJECT_X;
        charClips[i].y = COWORKER_OBJECT_Y;
        charClips[i].w = COWORKER_OBJECT_W;
        charClips[i].h = COWORKER_OBJECT_H;
      }
    }

    void setObjectTexture(SDL_Texture* texture)
    {
      this->objectTexture = texture;
    }

    bool collisionCheck(int x, int y){
      if(x > COWORKER_SPAWN_X + 120 && x < COWORKER_SPAWN_X + 190){
        if(y < COWORKER_SPAWN_Y - 10 && y > COWORKER_SPAWN_Y - 60){ 
          return true;
        }
      }
      return false; 
    }

    void setHeavyHead(bool value){
      heavyHead = value;
      heavyHeadTime = SDL_GetTicks();
    }

  private:
    SDL_Texture* objectTexture = NULL;
    SDL_Renderer* renderer = NULL;
    SDL_Rect charClips[2];
    SDL_Rect charHead; 
    SDL_Color scoreColor;
    TTF_Font* font = NULL;
    int charIndex = 0;
    Uint32 blinkTime = 0;
    Uint32 heavyHeadTime = 0; 
    bool blink = false;
    bool heavyHead = false;
    bool frozen = false;
};

#endif
