//Setup.h
#include<SDL2/SDL_ttf.h>
#include<SDL2/SDL_image.h>

#ifndef Setup_h
#define Setup_h

const double PI = 3.14159265;
const double GRAVITY = 9.8;


const int SCREEN_WIDTH = 640*2;
const int SCREEN_HEIGHT = 480*2;
const int SCREEN_STARTING_YPOS = -500;
const int SCREEN_END_YPOS = 0; 
const int TEXT_SIZE = 40; 
const int NUM_TEXT_ROWS = 10;
const int MAX_TEXT_LENGTH = 20;
const int MAX_TEXT_SAMPLE_SIZE = 6;

//SPEED
const double LEVEL_ONE_SPEED = 1.5;
const double LETTER_SLOW_SPEED = 10;
const int TEXT_ROW_OFFSET = 90;
const int MAX_MULTIPLIER_VAL = 45;
const int MULTIPLIER_Y = 60;
const int MULTIPLIER_X = 280;
const int GROUND_VALUE = 930-TEXT_SIZE;
const char CODE_FONT[30] = "fonts/VT323-Regular.ttf";

const SDL_Color CODE_COLOR = {0xFF,0xFF,0xFF};//WHITE
const SDL_Color SHADOW_COLOR = {0, 0, 0};//BLACK


const int SCOREBOARDX = 60;
const int SCOREBOARDY = 60;
const int SCOREBOARD_FONT_SIZE = 40;


//MAIN MENU STUFF
const int MAIN_MENU_FONT_SIZE = 40;
const SDL_Color MENU_FONT_COLOR = {65, 111, 153};
const SDL_Color MENU_SHADOW_FONT_COLOR = {92, 109, 109};


const int CHARACTER_SCORE_X = 130;	//initial coordinates for values to fly out of
const int CHARACTER_SCORE_Y = 795;	//computer
const int CHARACTER_SCORE_FONT_SIZE = 30;
const int LETTER_TYPED_SCORE = 10;

const Uint32 LETTER_LIFETIME = 2000;

//OBJECTS


const int MAIN_CHARACTER_OBJECT_Y = 810;
const int MAIN_CHARACTER_OBJECT_X = 110;
const int MAIN_CHARACTER_OBJECT_W = MAIN_CHARACTER_OBJECT_X;
const int MAIN_CHARACTER_OBJECT_H = 150;

const int COWORKER_OBJECT_Y = 740;
const int COWORKER_OBJECT_X = 520;
const int COWORKER_OBJECT_W = 270;
const int COWORKER_OBJECT_H = 230;
const int COWORKER_SPAWN_X = 750;
const int COWORKER_SPAWN_Y = 680;

const int BOSS_OBJECT_Y = 1520;
const int BOSS_OBJECT_X = 0;
const int BOSS_OBJECT_W = 120;
const int BOSS_OBJECT_H = 190;
const int BOSS_SPAWN_X = 500;
const int BOSS_SPAWN_Y = 690;
const int WALKING_SPEED = 2;

const int TRASHCAN_SPAWN_X = 1190;
const int TRASHCAN_SPAWN_Y = 750;

const int CLOCK_SPAWN_X = 140;
const int CLOCK_SPAWN_Y = 580;

const int DOOR_SPAWN_X = 1190;
const int DOOR_SPAWN_Y = 750;

const int FOUNTAIN_SPAWN_X = 1080;
const int FOUNTAIN_SPAWN_Y = 580;

bool init();

bool loadMedia();

bool setup();
#endif
