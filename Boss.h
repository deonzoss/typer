#ifndef Boss_h
#define Boss_h

class Boss
{
  public:
    Boss(SDL_Renderer* renderer)
    {
      this->renderer = renderer;
      blinkTime = SDL_GetTicks();
      walkTime = SDL_GetTicks(); 
      setupClips();
      loadFont();
    }
    
    ~Boss()
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
      SDL_Rect renderQuad; 
      if(!frozen){ 
        if(walking){ 
          if(facingRight){ 
            renderQuad = {xPos,BOSS_SPAWN_Y, charRightClips[walkingFrameIndex].w, charRightClips[walkingFrameIndex].h};
            SDL_RenderCopy(renderer, objectTexture, &charRightClips[walkingFrameIndex], &renderQuad);
            xPos+=WALKING_SPEED/speed;
          }
          else{
            renderQuad = {xPos,BOSS_SPAWN_Y, charLeftClips[walkingFrameIndex].w, charLeftClips[walkingFrameIndex].h};
            SDL_RenderCopy(renderer, objectTexture, &charLeftClips[walkingFrameIndex], &renderQuad);
            xPos-=WALKING_SPEED/speed; 
          }
          if((SDL_GetTicks() - walkTime) > (WALKING_ANIMATION_CHANGE_SPEED)*speed){
            walkingFrameIndex++;
            if(walkingFrameIndex == 5){
              walkingFrameIndex = 1;
            }
            walkTime = SDL_GetTicks();
          }
        }
        else{
          if(facingRight){   
            renderQuad = {BOSS_SPAWN_X,BOSS_SPAWN_Y, charRightClips[0].w, charRightClips[0].h};
            SDL_RenderCopy(renderer, objectTexture, &charRightClips[0], &renderQuad);
          }
          else{
            renderQuad = {BOSS_SPAWN_X,BOSS_SPAWN_Y, charLeftClips[0].w, charLeftClips[0].h};
            SDL_RenderCopy(renderer, objectTexture, &charLeftClips[0], &renderQuad);
          }
        }

        if(facingRight && xPos >= 100*SCALESIZE){
          facingRight = false;
        }
        else if(xPos <= 0*SCALESIZE){
          facingRight = true;
        }
      }
      else{
        if(facingRight){ 
          renderQuad = {xPos,BOSS_SPAWN_Y, charRightClips[walkingFrameIndex].w, charRightClips[walkingFrameIndex].h};
          SDL_RenderCopy(renderer, objectTexture, &charRightClips[walkingFrameIndex], &renderQuad);
        }
        else{
          renderQuad = {xPos,BOSS_SPAWN_Y, charLeftClips[walkingFrameIndex].w, charLeftClips[walkingFrameIndex].h};
          SDL_RenderCopy(renderer, objectTexture, &charLeftClips[walkingFrameIndex], &renderQuad);
        }
      }
      if(!heavyHead){ 
        if(facingRight){ 
          if(walkingFrameIndex%2==0 || !walking){
            renderQuad = {xPos+1*SCALESIZE, BOSS_SPAWN_Y - 7*SCALESIZE, charHeadRight.w, charHeadRight.h};
          }
          else{ 
            renderQuad = {xPos+1*SCALESIZE, BOSS_SPAWN_Y - 6*SCALESIZE, charHeadRight.w, charHeadRight.h};
          } 
          SDL_RenderCopy(renderer, objectTexture, &charHeadRight, &renderQuad);
        }
        else{ 
          if(walkingFrameIndex%2==0 || !walking){
            renderQuad = {xPos+4*SCALESIZE, BOSS_SPAWN_Y - 7*SCALESIZE, charHeadLeft.w, charHeadLeft.h};
          }
          else{ 
            renderQuad = {xPos+4*SCALESIZE, BOSS_SPAWN_Y - 6*SCALESIZE, charHeadLeft.w, charHeadLeft.h};
          } 
          SDL_RenderCopy(renderer, objectTexture, &charHeadLeft, &renderQuad);
        } 
      } 
      else{
        if(SDL_GetTicks()-heavyHeadTime > LETTER_LIFETIME){
          heavyHead = false;
        }
        if(facingRight){
          if(walkingFrameIndex%2==0 || !walking){
            renderQuad = {xPos+1*SCALESIZE, BOSS_SPAWN_Y - 6*SCALESIZE, charHeadRight.w, charHeadRight.h};
          }
          else{ 
            renderQuad = {xPos+1*SCALESIZE, BOSS_SPAWN_Y - 5*SCALESIZE, charHeadRight.w, charHeadRight.h};
          } 
          SDL_RenderCopy(renderer, objectTexture, &charHeadRight, &renderQuad);
        } 
        else{
          if(walkingFrameIndex%2==0 || !walking){
            renderQuad = {xPos+4*SCALESIZE, BOSS_SPAWN_Y - 6*SCALESIZE, charHeadLeft.w, charHeadLeft.h};
          }
          else{ 
            renderQuad = {xPos+4*SCALESIZE, BOSS_SPAWN_Y - 5*SCALESIZE, charHeadLeft.w, charHeadLeft.h};
          } 
          SDL_RenderCopy(renderer, objectTexture, &charHeadLeft, &renderQuad);
        }
      }
     
      if(!frozen){
        tryToBlink();
      }
    }

    void tryToBlink(){
      if((SDL_GetTicks() - blinkTime) > BOSS_BLINK_TIME){
        blink = true;
        blinkTime = SDL_GetTicks();
      }
      if(blink && ((SDL_GetTicks() - blinkTime) < BOSS_BLINK_DURATION)){
        SDL_Rect blinkingEyes;
        double yPos; 
        if(heavyHead){
          yPos = BOSS_SPAWN_Y - 3*SCALESIZE;
        }
        else{
          yPos = BOSS_SPAWN_Y - 4*SCALESIZE;
        }
        if(walkingFrameIndex%2==1 && walking){
          yPos+=1*SCALESIZE;
        }
        if(facingRight){ 
          blinkingEyes = {46*SCALESIZE, 75*SCALESIZE, 4*SCALESIZE, 1*SCALESIZE};
          SDL_Rect renderQuad = {xPos+3*SCALESIZE, yPos, blinkingEyes.w, blinkingEyes.h};
          SDL_RenderCopy(renderer, objectTexture, &blinkingEyes, &renderQuad);
        }
        else{
          blinkingEyes = {45*SCALESIZE, 83*SCALESIZE, 4*SCALESIZE, 1*SCALESIZE};
          SDL_Rect renderQuad = {xPos+5*SCALESIZE, yPos, blinkingEyes.w, blinkingEyes.h};
          SDL_RenderCopy(renderer, objectTexture, &blinkingEyes, &renderQuad);
        }
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
    
    bool collisionCheck(double x, double y){
      if(facingRight){  
        if(x >= xPos && (x <= xPos + 7*SCALESIZE)){
          if(y >= BOSS_SPAWN_Y - 10*SCALESIZE && y <= BOSS_SPAWN_Y - 5*SCALESIZE){
            return true;
          }
        }
      }
      else {
        if(x >= xPos + 2*SCALESIZE && (x <= xPos + 9*SCALESIZE)){
          if(y >= BOSS_SPAWN_Y - 10*SCALESIZE && y <= BOSS_SPAWN_Y - 5*SCALESIZE){
            return true;
          }
        }
      }
      return false; 
    }

    void setupClips()
    {
      charHeadRight.x = 1*SCALESIZE;
      charHeadRight.y = 145*SCALESIZE;
      charHeadRight.w = 7*SCALESIZE;
      charHeadRight.h = 7*SCALESIZE;

      charHeadLeft.x = 4*SCALESIZE;
      charHeadLeft.y = 171*SCALESIZE;
      charHeadLeft.w = 7*SCALESIZE;
      charHeadLeft.h = 7*SCALESIZE;

      for(int i = 0; i < 5; i++){
        charRightClips[i].x = BOSS_OBJECT_X+(15*SCALESIZE*i);
        charRightClips[i].y = BOSS_OBJECT_Y;
        charRightClips[i].w = BOSS_OBJECT_W;
        charRightClips[i].h = BOSS_OBJECT_H;
        
        charLeftClips[i].x = BOSS_OBJECT_X+(15*SCALESIZE*i);
        charLeftClips[i].y = BOSS_OBJECT_Y+BOSS_OBJECT_H+7*SCALESIZE;
        charLeftClips[i].w = BOSS_OBJECT_W;
        charLeftClips[i].h = BOSS_OBJECT_H;
      }
    }

    void setObjectTexture(SDL_Texture* texture)
    {
      this->objectTexture = texture;
    }

    void setHeavyHead(bool value){
      heavyHead = true;
      heavyHeadTime = SDL_GetTicks();
    }

    bool getWalking(){
      return walking;
    }

    bool getFacingRight(){
      return facingRight;
    }
    
    int getFrameIndex(){
      return walkingFrameIndex;
    }

    double getSpeed(){
      return speed;
    }

    void setSpeed(double value){
      speed = value;
    }

  private:
    SDL_Texture* objectTexture = NULL;
    SDL_Renderer* renderer = NULL;
    SDL_Rect charRightClips[5];
    SDL_Rect charLeftClips[5];
    SDL_Rect charHeadRight; 
    SDL_Rect charHeadLeft; 
    SDL_Color scoreColor;
    TTF_Font* font = NULL;
    int charIndex = 0;
    Uint32 blinkTime = 0;
    Uint32 walkTime = 0;
    Uint32 heavyHeadTime = 0; 
    bool blink = false;
    bool heavyHead = false;
    bool frozen = false;
    bool facingRight = false;
    bool walking = true;
    double xPos = BOSS_SPAWN_X;
    int walkingFrameIndex = 1;
    double speed = 1;
};

#endif
