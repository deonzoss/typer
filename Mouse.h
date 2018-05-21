#ifndef Mouse_h
#define Mouse_h

class Mouse
{
  public:
    Mouse(double xPos, double yPos, SDL_Renderer* renderer)
    {
      this->renderer = renderer;
      this->xPos = xPos;
      this->yPos = yPos;
      mouseClip.x = 149;
      mouseClip.y = 68;
      mouseClip.h = 6;
      mouseClip.w = 6;
      renderQuad = {xPos, yPos, mouseClip.h*SCALESIZE/2, mouseClip.w*SCALESIZE/2};
    }

    ~Mouse()
    {
      free();
    }

    void free()
    {

    }
    
    void setObjectTexture(SDL_Texture* texture)
    {
      this->objectTexture = texture;
    }
    
    void render(){
      SDL_RenderCopy(renderer, objectTexture, &mouseClip, &renderQuad);
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
    SDL_Rect mouseClip;
    SDL_Rect renderQuad;
    double xPos = NULL;
    double yPos = NULL;
    double width = NULL;
    double height = NULL;

};

#endif
