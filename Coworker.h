
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
      SDL_Rect renderQuad = {COWORKER_COMPUTER_X, COWORKER_COMPUTER_Y, computerClips[0].w*SCALESIZE, computerClips[0].h*SCALESIZE};
      SDL_RenderCopy(renderer, objectTexture, &computerClips[computerClipsIndex], &renderQuad); 
    
      
      renderQuad = {COWORKER_SPAWN_X,COWORKER_SPAWN_Y, charClips[0].w*SCALESIZE, charClips[0].h*SCALESIZE};
      SDL_RenderCopy(renderer, objectTexture, &charClips[0], &renderQuad);
      
      if(!heavyHead){ 
        renderQuad = {COWORKER_SPAWN_X + 13*SCALESIZE, COWORKER_SPAWN_Y - 2*SCALESIZE, charHead.w*SCALESIZE, charHead.h*SCALESIZE};
        SDL_RenderCopy(renderer, objectTexture, &charHead, &renderQuad);
      } 
      else{
        renderQuad = {COWORKER_SPAWN_X + 13*SCALESIZE, COWORKER_SPAWN_Y - 1*SCALESIZE, charHead.w*SCALESIZE, charHead.h*SCALESIZE};
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
        SDL_Rect blinkingEyes = {45, 83, 4, 1};
        SDL_Rect renderQuad; 
        if(!heavyHead){ 
          renderQuad = {COWORKER_SPAWN_X + 14*SCALESIZE, COWORKER_SPAWN_Y + 1*SCALESIZE, blinkingEyes.w*SCALESIZE, blinkingEyes.h*SCALESIZE};
        } 
        else{ 
          renderQuad = {COWORKER_SPAWN_X + 14*SCALESIZE, COWORKER_SPAWN_Y + 2*SCALESIZE, blinkingEyes.w*SCALESIZE, blinkingEyes.h*SCALESIZE};
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
      charHead.x = 44;
      charHead.y = 84;
      charHead.w = 7;
      charHead.h = 7; 
      for(int i = 0; i < 2; i++){
        charClips[i].x = COWORKER_OBJECT_X;
        charClips[i].y = COWORKER_OBJECT_Y;
        charClips[i].w = COWORKER_OBJECT_W;
        charClips[i].h = COWORKER_OBJECT_H;
      }
      for(int i = 0; i < 26; i++){
        computerClips[i].x = 116 + 8*(i%4);
        computerClips[i].y = 68 + 8*((i/4)%7);
        computerClips[i].w = 8;
        computerClips[i].h = 8;
      }
    }

    void setObjectTexture(SDL_Texture* texture)
    {
      this->objectTexture = texture;
    }

    bool collisionCheck(double x, double y){
      if(x > COWORKER_SPAWN_X + 12*SCALESIZE && x < COWORKER_SPAWN_X + 19*SCALESIZE){
        if(y < COWORKER_SPAWN_Y - 1*SCALESIZE && y > COWORKER_SPAWN_Y - 6*SCALESIZE){ 
          return true;
        }
      }
      return false; 
    }

    bool computerCollisionCheck(double x, double y){
      if(x > COWORKER_COMPUTER_X && x < COWORKER_COMPUTER_X + 8*SCALESIZE){
        if(y > COWORKER_COMPUTER_Y -1*SCALESIZE && y < COWORKER_COMPUTER_Y+ 5*SCALESIZE){
          return true;
        } 
      }
      return false;
    }

    void setHeavyHead(bool value){
      heavyHead = value;
      heavyHeadTime = SDL_GetTicks();
    }
    
    void setSpeed(double value){
      speed = value;
    }

    void updateComputer(){
      computerClipsIndex++; 
      if(computerClipsIndex == 26)
        computerClipsIndex = 0;
    } 
  private:
    SDL_Texture* objectTexture = NULL;
    SDL_Renderer* renderer = NULL;
    SDL_Rect charClips[2];
    SDL_Rect computerClips[26]; 
    int computerClipsIndex = 0; 
    SDL_Rect charHead; 
    SDL_Color scoreColor;
    TTF_Font* font = NULL;
    int charIndex = 0;
    Uint32 blinkTime = 0;
    Uint32 heavyHeadTime = 0; 
    Uint32 computerClipTime = 0;
    bool blink = false;
    bool heavyHead = false;
    bool frozen = false;
    double speed = 1;
};

#endif
