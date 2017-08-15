#ifndef Word_h
#define Word_h

class Word
{
  public:
    Word(SDL_Renderer* renderer, int xPos, int yPos, char string[50], bool shadow, SDL_Color fontColor, SDL_Color shadowColor, int fontSize, int shadowOffset){
      this->renderer = renderer;
      this->xPos = xPos;
      this->yPos = yPos;
      this->fontColor = fontColor;
      this->shadowColor = shadowColor;
      this->shadowOffset = shadowOffset; 
      this->shadow = shadow;    
      strcpy(this->string, string); 
      this->fontSize = fontSize; 
      strcpy(this->fontString, (char*)CODE_FONT);
      loadFont(); 
      loadFromRenderedText(); 
    }

    ~Word(){
      free();
    }

    void free(){

    }
  
    void loadFont(){
        font = TTF_OpenFont(CODE_FONT, fontSize);
        if(!font){
          printf("SDL_ttf Error: %s\n", TTF_GetError()); 
        } 
    }

    void loadFromRenderedText(){
      free();

      SDL_Surface* textSurface = TTF_RenderText_Solid(font, string, fontColor);
      if(!textSurface){
        printf("SDL Error: %s\n", TTF_GetError());
      } 
      
      wordTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
      
      wordWidth = textSurface->w;
      wordHeight = textSurface->h;
      
      SDL_FreeSurface(textSurface);

      if(shadow){
        SDL_Surface* shadowSurface = TTF_RenderText_Solid(font, string, shadowColor);
        shadowTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
        
        SDL_FreeSurface(shadowSurface);
      }
    }

    void render(){
      SDL_Rect renderQuad; 
      if(shadow){
        renderQuad = {xPos + shadowOffset, yPos + shadowOffset, wordWidth, wordHeight};
        SDL_RenderCopyEx(renderer, shadowTexture, NULL, &renderQuad, 0.0, NULL, SDL_FLIP_NONE);
      }
      renderQuad = {xPos, yPos, wordWidth, wordHeight};
      SDL_RenderCopyEx(renderer, wordTexture, NULL, &renderQuad, 0.0, NULL, SDL_FLIP_NONE);
    }

  
  private: 
    SDL_Renderer* renderer = NULL;
    SDL_Texture* wordTexture = NULL;
    SDL_Texture* shadowTexture = NULL; 
    char string[50];
    int wordWidth = 0;
    int wordHeight = 0;
    int xPos = 0;
    int yPos = 0;
    int shadowOffset = 0;
    int fontSize = 0; 
    TTF_Font* font;
    SDL_Color fontColor;
    SDL_Color shadowColor;
    char fontString[30];
    bool shadow = false;
}; 

#endif  