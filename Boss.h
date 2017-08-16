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
          if((SDL_GetTicks() - walkTime) > (220)*speed){
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

        if(facingRight && xPos >= 1000){
          facingRight = false;
        }
        else if(xPos <= 0){
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
            renderQuad = {xPos+10, BOSS_SPAWN_Y - 70, charHeadRight.w, charHeadRight.h};
          }
          else{ 
            renderQuad = {xPos+10, BOSS_SPAWN_Y - 60, charHeadRight.w, charHeadRight.h};
          } 
          SDL_RenderCopy(renderer, objectTexture, &charHeadRight, &renderQuad);
        }
        else{ 
          if(walkingFrameIndex%2==0 || !walking){
            renderQuad = {xPos+40, BOSS_SPAWN_Y - 70, charHeadLeft.w, charHeadLeft.h};
          }
          else{ 
            renderQuad = {xPos+40, BOSS_SPAWN_Y - 60, charHeadLeft.w, charHeadLeft.h};
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
            renderQuad = {xPos+10, BOSS_SPAWN_Y - 60, charHeadRight.w, charHeadRight.h};
          }
          else{ 
            renderQuad = {xPos+10, BOSS_SPAWN_Y - 50, charHeadRight.w, charHeadRight.h};
          } 
          SDL_RenderCopy(renderer, objectTexture, &charHeadRight, &renderQuad);
        } 
        else{
          if(walkingFrameIndex%2==0 || !walking){
            renderQuad = {xPos+40, BOSS_SPAWN_Y - 60, charHeadLeft.w, charHeadLeft.h};
          }
          else{ 
            renderQuad = {xPos+40, BOSS_SPAWN_Y - 50, charHeadLeft.w, charHeadLeft.h};
          } 
          SDL_RenderCopy(renderer, objectTexture, &charHeadLeft, &renderQuad);
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
        SDL_Rect blinkingEyes;
        int yPos; 
        if(heavyHead){
          yPos = BOSS_SPAWN_Y - 30;
        }
        else{
          yPos = BOSS_SPAWN_Y - 40;
        }
        if(walkingFrameIndex%2==1 && walking){
          yPos+=10;
        }
        if(facingRight){ 
          blinkingEyes = {460, 750, 40, 10};
          SDL_Rect renderQuad = {xPos+30, yPos, blinkingEyes.w, blinkingEyes.h};
          SDL_RenderCopy(renderer, objectTexture, &blinkingEyes, &renderQuad);
        }
        else{
          blinkingEyes = {450, 830, 40, 10};
          SDL_Rect renderQuad = {xPos+50, yPos, blinkingEyes.w, blinkingEyes.h};
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
    
    bool collisionCheck(int x, int y){
      if(facingRight){  
        if(x >= xPos && (x <= xPos + 70)){
          if(y >= BOSS_SPAWN_Y - 100 && y <= BOSS_SPAWN_Y - 50){
            return true;
          }
        }
      }
      else {
        if(x >= xPos + 20 && (x <= xPos + 90)){
          if(y >= BOSS_SPAWN_Y - 100 && y <= BOSS_SPAWN_Y - 50){
            return true;
          }
        }
      }
      return false; 
    }

    void setupClips()
    {
      charHeadRight.x = 10;
      charHeadRight.y = 1450;
      charHeadRight.w = 70;
      charHeadRight.h = 70;

      charHeadLeft.x = 40;
      charHeadLeft.y = 1710;
      charHeadLeft.w = 70;
      charHeadLeft.h = 70;

      for(int i = 0; i < 5; i++){
        charRightClips[i].x = BOSS_OBJECT_X+(150*i);
        charRightClips[i].y = BOSS_OBJECT_Y;
        charRightClips[i].w = BOSS_OBJECT_W;
        charRightClips[i].h = BOSS_OBJECT_H;
        
        charLeftClips[i].x = BOSS_OBJECT_X+(150*i);
        charLeftClips[i].y = BOSS_OBJECT_Y+BOSS_OBJECT_H+70;
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
