#ifndef Object_h
#define Object_h

class Object
{
  public:
    Object(double xPos, double yPos, double width, double height, double spawnXPos, double spawnYPos, SDL_Renderer* renderer)
    {
      this->renderer = renderer;
      objectClip.x = xPos;
      objectClip.y = yPos;
      objectClip.h = height;
      objectClip.w = width;
      renderQuad = {spawnXPos, spawnYPos, width*SCALESIZE, height*SCALESIZE};
    }

    void setObjectTexture(SDL_Texture* texture)
    {
      this->objectTexture = texture;
    }
    
    void render(){
      if(!rotate){
        SDL_RenderCopy(renderer, objectTexture, &objectClip, &renderQuad);
      }
      else{ 
        if(direction){
          angle+=randInt;
        }
        else{
          angle-=randInt;
        }
        if(angle > 360){
          angle = 0;
        }
        SDL_RenderCopyEx(renderer, objectTexture, &objectClip, &renderQuad, angle, NULL, SDL_FLIP_NONE);
      }
    }

    void setY(int value){
      renderQuad.y = value;
    }

    void setX(int value){
      renderQuad.x = value;
    }

    int getY(){
      return renderQuad.y;
    }
    
    int getX(){
      return renderQuad.x;
    }

    void setRotate(bool value){
      rotate = value;
      randInt = (rand() % 10) + 5;
      direction = (rand() % 2);
    }

  private:
    bool rotate = false;
    int direction = 0;
    int angle = 0;
    int randInt = 0;
    SDL_Texture* objectTexture = NULL;
    SDL_Renderer* renderer = NULL;
    SDL_Rect objectClip;
    SDL_Rect renderQuad;




};
#endif
