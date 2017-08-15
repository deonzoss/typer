#ifndef Texture_h
#define Texture_h



class Texture
{
	public:
		Texture();
		
		~Texture();

		bool loadFromRenderedText(std::string textureText);

		bool loadText(std::string text);

		void render(int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);
	
		bool offScreen();	
	
		int popFront();	

		int getWidth();
		
		int getHeight();
		
		void setOriginalText(std::string originalText);	
		
		std::string getText();
		
		std::string getOriginalText();	
		
		bool hasText();		

		int length();	
		
		int getXPos();

		void setXPos(int x);

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

		int mWidth = 0;
		int mHeight = 0;
		int shadowWidth = 0;
		int shadowHeight = 0;
		
		double xPos = 0;
		double speed = 0;

};

#endif
