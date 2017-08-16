#ifndef Object_h
#define Object_h

class Object
{
  public:
    Object(int xPos, int yPos, int width, int height, int spawnXPos, int spawnYPos, SDL_Renderer* renderer)
    {
      this->renderer = renderer;
      objectClip.x = xPos;
      objectClip.y = yPos;
      objectClip.h = height;
      objectClip.w = width;
      renderQuad = {spawnXPos, spawnYPos, width, height};
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

    int getY(){
      return renderQuad.y;
    }

  private:
    SDL_Texture* objectTexture = NULL;
    SDL_Renderer* renderer = NULL;
    SDL_Rect objectClip;
    SDL_Rect renderQuad;
};
#endif
