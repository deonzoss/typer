#include <stdio.h>

#ifndef level_h
#define level_h

class Level
{
	public:
		Level();

		~Level();

		void setMaxWords(int max);

		void setWordRate(int rate);

		void setSpeed(double speed);

		void setCurrNumWords(int num);
		
		int getCurrNumWords();	
		
		int getMaxWords();
		
		int getWordRate();
		
		double getSpeed();	
	
	private:
		int currNumWords;	
		int maxWords;
		int wordRate;
		double masterSpeed;
};

#endif


