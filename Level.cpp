#include <stdio.h>
#include "Level.h"

Level::Level()
{
	maxWords = 0;
	wordRate = 0;
	masterSpeed = 0;
	currNumWords = 0;
}

void Level::setMaxWords(int max)
{
	maxWords = max;
}

void Level::setWordRate(int rate)
{
	wordRate = rate;
}

void Level::setSpeed(double speed)
{
	masterSpeed = speed;
}

void Level::setCurrNumWords(int num)
{
	currNumWords = num;
}

int Level::getCurrNumWords()
{
	return currNumWords;
}

int Level::getMaxWords()
{
	return maxWords;
}

int Level::getWordRate()
{
	return wordRate;
}

double Level::getSpeed()
{
	return masterSpeed;
}
