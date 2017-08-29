#ifndef Texture_h
#define Texture_h



class Texture
{
	public:
		Texture();
		
		~Texture();

		bool loadFromRenderedText(std::string textureText);

		bool loadText(std::string text);

		void render(double x, double y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);
	
		bool offScreen();	
	
		int popFront();	

		double getWidth();
		
		double getHeight();
		
		void setOriginalText(std::string originalText);	
		
		std::string getText();
		
		std::string getOriginalText();	
		
		bool hasText();		

		int length();	
		
		double getXPos();

		void setXPos(double x);

		void setFont(TTF_Font* gFont);
		
		void setRenderer(SDL_Renderer* renderer);	
		SDL_Renderer* getRenderer();	
		
		void setSpeed(double speed);	

    double getSpeed();	

    void move();	
		
		void free();
		
	private:
		SDL_Texture* mTexture = NULL;
		SDL_Texture* shadowTexture = NULL;	
		SDL_Renderer* renderer = NULL;
		TTF_Font* gFont = NULL;
		
		std::string text;
		std::string originalText;	

		double mWidth = 0;
		double mHeight = 0;
		double shadowWidth = 0;
		double shadowHeight = 0;
		
		double xPos = 0;
		double speed = 0;

};

#endif
