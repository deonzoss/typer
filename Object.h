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
      SDL_RenderCopy(renderer, objectTexture, &objectClip, &renderQuad);
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

  private:
    SDL_Texture* objectTexture = NULL;
    SDL_Renderer* renderer = NULL;
    SDL_Rect objectClip;
    SDL_Rect renderQuad;




};
#endif
