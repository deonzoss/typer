#ifndef Letter_h
#define Letter_h


class Letter
{
	public:
		Letter();
		~Letter();
		
		void move();

		bool loadLetter(char letter, SDL_Renderer* renderer);

		bool loadFromRenderedText(char letter, SDL_Color letterColor, SDL_Renderer* renderer);

		void render(double x, double y,SDL_Renderer* renderer, SDL_Rect* clip=NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);	
	
		void fade();
		
		void setX(double x);

		void setY(double Y);

		Uint8 getAlpha();	

		bool offScreen();	

		bool groundContact();

		Uint32 getLifetime();	
		
		double getX();

		double getY();

    void setDynamic(int value); 
    
    int  getDynamic(); 
    
    bool getOnGround();

    void setOnGround(bool value);

    double getSpeed();

    void setSpeed(double value); 

    char getLetter();
  
  private:
		SDL_Texture* texture = NULL;
		SDL_Texture* shadowTexture = NULL;
		TTF_Font* font = NULL;
		char letter = '\0';
		double width = 0;
		double height= 0;	
		double xPos= 0;
		double yPos= 0;
		double relX=0;
		int randGroundValue=0;
		double relY=0;
	  double prevRelY=0;	
    double rate=0;
    int randXChange=0;
    double velocity=0;
		int angle=0;
		Uint32 lifetime = 0;
		bool onGround = false;
		Uint8 alpha = 255;
    int dynamic = 0;
    double speedMult = 1;

};

#endif
