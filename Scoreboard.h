#ifndef Scoreboard_h
#define Scoreboard_h

class Scoreboard
{
	public:
		Scoreboard(SDL_Renderer* renderer)
		{
			this->renderer = renderer;
			multColor = {245, 0, 0};
			multColorVal = 50;		
			loadFont(SCOREBOARD_FONT_SIZE);	
			loadScoreWord();	
		}
		
		~Scoreboard()
		{
			free();
		}

		void free()
		{
			if(fontTexture){
				SDL_DestroyTexture(fontTexture);
				fontTexture = NULL;
				fontTextureWidth = 0;
				fontTextureHeight = 0;
			}
		
			if(multTexture){
				SDL_DestroyTexture(multTexture);
				multTexture = NULL;
				SDL_DestroyTexture(shadowMultTexture);
				shadowMultTexture = NULL;
			
				multTextureWidth = 0;
				multTextureHeight = 0;
			}
								
		}
		
		void loadFont(double fontSize){
			font = TTF_OpenFont(CODE_FONT, fontSize);
			if(font == NULL){
				printf("Error opening score font. TTF_Error: %n", TTF_GetError());
			}
		
		}

		void loadScoreWord(){
			
			char* scoreWord = "SCORE: "; 
		
			fontColor = CODE_COLOR;	
			loadFont(SCOREBOARD_FONT_SIZE - 1*SCALESIZE);	
			SDL_Surface* textSurface = TTF_RenderText_Solid(font, scoreWord, fontColor);
		
			if(!textSurface){
				printf("Error making score surface. TTF_Error: %n", TTF_GetError());
			}
			else{
				scoreTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
				if(!scoreTexture){
					printf("Unable to render texture from rendered text, SDL Error: %s\n", SDL_GetError);
				}
				else{
					scoreTextureWidth = textSurface->w;
					scoreTextureHeight = textSurface->h;
				}

				SDL_FreeSurface(textSurface);
			}

			loadFont(SCOREBOARD_FONT_SIZE);

		}

		void loadFromRenderedText()
		{
			free();	

			char scoreString[10];
			strcpy(scoreString, std::to_string(score).c_str());
			
			if (wordScore){
				incScore = false;	
				fontColor = {113,172,224};	
				if(SDL_GetTicks()-time > 200)	
					wordScore = false;	
			}
      else if(objectScore){
        fontColor = {241,40,40};
        if(SDL_GetTicks()-time > 100)
          objectScore = false;
      }
			else if(incScore){		
				fontColor = {114,224,66};	
				if(SDL_GetTicks()-time > 100)	
					incScore = false;	
			}

			else{
				fontColor = CODE_COLOR;
			}
			SDL_Surface* textSurface = TTF_RenderText_Solid(font, scoreString, fontColor);
			if(!textSurface){
				printf("Error making score surface. TTF_Error: %n", TTF_GetError());
			}
			else{
				fontTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
				if(!fontTexture){
					printf("Unable to render texture from rendered text, SDL Error: %s\n", SDL_GetError);
				}
				else{
					fontTextureWidth = textSurface->w;
					fontTextureHeight = textSurface->h;
				}

				SDL_FreeSurface(textSurface);
			}

			
			
			if(multValue > 1){
				char multString[3];
				strcpy(multString, "x");
				strcat(multString, std::to_string(multValue).c_str());
				
				multColor = getColor(multColor);	

				SDL_Surface* multSurface = TTF_RenderText_Solid(font, multString, multColor);
				SDL_Surface* shadowMultSurface = TTF_RenderText_Solid(font, multString, SHADOW_COLOR);	
				if(!multSurface){
					printf("Error making mult surface. TTF_Error: %n", TTF_GetError());
				}
				else{
					multTexture = SDL_CreateTextureFromSurface(renderer, multSurface);
					shadowMultTexture = SDL_CreateTextureFromSurface(renderer, shadowMultSurface);
					if(!multTexture){
						printf("Unable to render texture from rendered text, SDL Error: %s\n", SDL_GetError);
					}
					else{
						multTextureWidth = multSurface->w;
						multTextureHeight = multSurface->h;
					}

					SDL_FreeSurface(multSurface);
					SDL_FreeSurface(shadowMultSurface);
			
				}
			}
			else{
				multColorVal = 0;
			}
				

					
		}

		SDL_Color getColor(SDL_Color multColor){
			if(!multColorDesc){
				multColorVal+=(multValue/4)*(multValue);
			}
			else{
				multColorVal-=(multValue/4)*(multValue);
			}		
			if(multColorVal >= 50 + multValue*20){
				multColorDesc = true;
				multColorVal = 50 + multValue*20;	
			}
			else if(multColorVal <= 50){
				multColorDesc = false;
				multColorVal = 50;	
			}
				
			multColor = {245, multColorVal, 0};
			return multColor;
		}

		void setupMultDisplay()
		{
			if(objectTexture)
			{
        blankMultDisplay.x = 0*SCALESIZE;
        blankMultDisplay.y = 2*SCALESIZE;
        blankMultDisplay.w = 89*SCALESIZE;
        blankMultDisplay.h = 2*SCALESIZE;
    
        for(int i = 0; i < MAX_MULTIPLIER_VAL; i++)
				{	
					multClips[i].x = 0*SCALESIZE;
					multClips[i].y = 0*SCALESIZE;
					multClips[i].w = (2*SCALESIZE*(i+1))-(1*SCALESIZE);
					multClips[i].h = 2*SCALESIZE;
				}	
			}
		}	
		
		void render()
		{
			
			
			/********************Render "SCORE: "***************************/	
			
			SDL_Rect scoreRenderQuad = {scoreTextureX,scoreTextureY, scoreTextureWidth, scoreTextureHeight};

			SDL_RenderCopyEx(renderer, scoreTexture, NULL, &scoreRenderQuad, 0.0, NULL, SDL_FLIP_NONE);
			
			
			
			/********************Now render score value*********************/	
			
			loadFromRenderedText();	
			
			scoreRenderQuad = {fontTextureX + scoreTextureWidth - .5*SCALESIZE, fontTextureY - (fontTextureHeight - scoreTextureHeight) + .2*SCALESIZE, fontTextureWidth, fontTextureHeight};

			SDL_RenderCopyEx(renderer, fontTexture, NULL, &scoreRenderQuad, 0.0, NULL, SDL_FLIP_NONE);




      SDL_Rect multRenderQuad = {MULTIPLIER_X,MULTIPLIER_Y,blankMultDisplay.w,blankMultDisplay.h};

      SDL_RenderCopy(renderer, objectTexture, &blankMultDisplay, &multRenderQuad);	


			if(multiplier){	

				multRenderQuad = {MULTIPLIER_X,MULTIPLIER_Y,multClips[multiplier-1].w,multClips[multiplier-1].h};

				SDL_RenderCopy(renderer, objectTexture, &multClips[multiplier-1], &multRenderQuad);	
			}		
			
			if(multValue > 1){	
				scoreRenderQuad = {multTextureX + .1*SCALESIZE, multTextureY - .7*SCALESIZE, multTextureWidth, multTextureHeight};
				SDL_RenderCopyEx(renderer, shadowMultTexture, NULL, &scoreRenderQuad, 0.0, NULL, SDL_FLIP_NONE);
				
				scoreRenderQuad = {multTextureX - .2*SCALESIZE, multTextureY - 1*SCALESIZE, multTextureWidth, multTextureHeight};
				SDL_RenderCopyEx(renderer, multTexture, NULL, &scoreRenderQuad, 0.0, NULL, SDL_FLIP_NONE);
			}
		
			
		}

		int calculateAndAddWordScore(std::string word){
			int totalScore = 0;
			int count1 = 0, count2 = 0, count3 = 0;
			for(std::string::iterator it=word.begin(); it!=word.end(); ++it){
				if(std::ispunct(*it)){
					totalScore+=30;
				}
				else if(std::isdigit(*it)){
					totalScore+=20;
				}
				else if(std::isalpha(*it)){
					totalScore+=10;
				}
			}
			wordScore = true;	
			int calc = updateScore(totalScore,1);	
			return calc;
		}

		void setLevel(int currentLevel)
		{
			this->currentLevel = currentLevel;
		}

		int updateScore(int value, int type)
		{
			int calc = value;	
      if(type == 1){ 
        incScore = true;
        if(value > 0 && multiplier){
          calc*=(multValue);	
          score+=calc;
        }
        else if (value > 0){
          score+=value;
        }
      }
      else if(type == 2){
        objectScore = true;
        score+=value;
      }
      time = SDL_GetTicks();	
	
			return calc;
		}

		void setObjectTexture(SDL_Texture* objectTexture)
		{
			this->objectTexture = objectTexture;
			setupMultDisplay();
		}

		void setMultiplier(int value){	
			multiplier = value;
			multValue = (multiplier/5)+1;	
			if(multiplier > MAX_MULTIPLIER_VAL){
				multiplier = MAX_MULTIPLIER_VAL;
			}
			else if(multiplier == 1){
				multValue = 1;
			}
		}

		int getMultiplier()
		{
			return multiplier;
		}


	private:
		SDL_Texture* fontTexture = NULL;	//number following "SCORE: "
		SDL_Texture* scoreTexture = NULL;	//"SCORE: "	
		SDL_Texture* multTexture = NULL;	//"x2, x3, ..., x10"	
		SDL_Texture* objectTexture = NULL;	//texture from "spritesheet"	
		SDL_Texture* shadowMultTexture = NULL;	
		TTF_Font* font = NULL;
		SDL_Renderer* renderer = NULL;
		SDL_Rect multClips[MAX_MULTIPLIER_VAL];
	        SDL_Rect blankMultDisplay;	
                SDL_Color fontColor;	
		SDL_Color multColor;	
		int multColorVal;
	
		Uint32 time;	
		
		int score= 0;
		int currentLevel = 0;
		int multiplier = 0;
		int multValue = 1;	
	
		double fontTextureWidth = 0;			//for texture of score value (number following SCORE:)
		double fontTextureHeight = 0;
		double fontTextureX = SCOREBOARDX;
		double fontTextureY = SCOREBOARDY;
		
		double scoreTextureWidth = 0;			//for texture of "SCORE: "
		double scoreTextureHeight = 0;
		double scoreTextureX = SCOREBOARDX;
		double scoreTextureY = SCOREBOARDY;
	
		double multTextureWidth = 0;
		double multTextureHeight = 0;
		double multTextureX = SCREEN_WIDTH-10*SCALESIZE;
		double multTextureY = SCOREBOARDY;
	
		bool incScore = false;
    bool objectScore = false;
    bool wordScore = false;
		bool multColorDesc = false;
};

#endif

