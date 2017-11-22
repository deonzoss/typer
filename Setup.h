//Setup.h
#include<SDL2/SDL_ttf.h>
#include<SDL2/SDL_image.h>

#ifndef Setup_h
#define Setup_h

const double SCALESIZE = 10;


const double PI = 3.14159265;
const double GRAVITY = 9.8;



//SPEED
const double LEVEL_ONE_SPEED = .15*SCALESIZE;
const double LETTER_SLOW_SPEED = 10;
const double WALKING_SPEED = .19*SCALESIZE;
const double WALKING_ANIMATION_CHANGE_SPEED = 220;




//SCREEN
const double SCREEN_ORIG_WIDTH=128;
const double SCREEN_ORIG_HEIGHT=96;
const double SCREEN_WIDTH = SCREEN_ORIG_WIDTH*SCALESIZE;
const double SCREEN_HEIGHT =SCREEN_ORIG_HEIGHT*SCALESIZE;
const double TEXT_ROW_OFFSET = 9*SCALESIZE;
const double MULTIPLIER_Y = 6*SCALESIZE;
const double MULTIPLIER_X = 28*SCALESIZE;
const char CODE_FONT[30] = "fonts/VT323-Regular.ttf";
const SDL_Color CODE_COLOR = {0xFF,0xFF,0xFF};//WHITE
const SDL_Color SHADOW_COLOR = {0, 0, 0};//BLACK
const double SCOREBOARDX = 6*SCALESIZE;
const double SCOREBOARDY = 6*SCALESIZE;
const double SCOREBOARD_FONT_SIZE = 4*SCALESIZE;
const double SCREEN_STARTING_YPOS = -50*SCALESIZE;
const double SCREEN_END_YPOS = 0*SCALESIZE; 
const double TEXT_SIZE = 4*SCALESIZE; 
const int  NUM_TEXT_ROWS = 10;
const int MAX_TEXT_LENGTH = 20;




//MAIN MENU STUFF
const double MAIN_MENU_FONT_SIZE = 4*SCALESIZE;
const SDL_Color MENU_FONT_COLOR = {65, 111, 153};
const SDL_Color MENU_SHADOW_FONT_COLOR = {92, 109, 109};
const double TIP_TEXT_XPOS = 20;
const double TIP_TEXT_YPOS = 19;
const double MENU_FRAMES_SPAWN_Y = 4*SCALESIZE;

const double CHARACTER_SCORE_X = 13*SCALESIZE;	//initial coordinates for values to fly out of
const double CHARACTER_SCORE_Y = 79.5*SCALESIZE;	//computer
const double CHARACTER_SCORE_FONT_SIZE = 3*SCALESIZE;



//SCORES
const int LETTER_TYPED_SCORE = 10;
const int MAX_MULTIPLIER_VAL = 45;


//LIFETIMES
const Uint32 LETTER_LIFETIME = 2000;

//ENVIRONMENT VARIABLES
const double GROUND_VALUE = (93*SCALESIZE)-TEXT_SIZE;


//OBJECTS
const double MAIN_CHARACTER_OBJECT_Y = 81;
const double MAIN_CHARACTER_OBJECT_X = 11;
const double MAIN_CHARACTER_OBJECT_W = MAIN_CHARACTER_OBJECT_X;
const double MAIN_CHARACTER_OBJECT_H = 15;

const double COWORKER_OBJECT_Y = 74;
const double COWORKER_OBJECT_X = 52;
const double COWORKER_OBJECT_W = 27;
const double COWORKER_OBJECT_H = 23;
const double COWORKER_SPAWN_X = 85*SCALESIZE;
const double COWORKER_SPAWN_Y = 68*SCALESIZE;

const double COWORKER_COMPUTER_X = 86*SCALESIZE;
const double COWORKER_COMPUTER_Y = 68*SCALESIZE;

const double BOSS_OBJECT_Y = 152;
const double BOSS_OBJECT_X = 0;
const double BOSS_OBJECT_W = 12;
const double BOSS_OBJECT_H = 19;
const double BOSS_SPAWN_X = 50*SCALESIZE;
const double BOSS_SPAWN_Y = 69*SCALESIZE;
const int BOSS_BLINK_TIME = 2500;
const int BOSS_BLINK_DURATION = 100;

const double TRASHCAN_SPAWN_X = 75*SCALESIZE;
const double TRASHCAN_SPAWN_Y = 75*SCALESIZE;

const double CLOCK_SPAWN_X = 14*SCALESIZE;
const double CLOCK_SPAWN_Y = 58*SCALESIZE;

const double DOOR_SPAWN_X = 119*SCALESIZE;
const double DOOR_SPAWN_Y = 75*SCALESIZE;

const double WINDOW_WORKER_X = 60*SCALESIZE;
const double WINDOW_WORKER_Y = 63*SCALESIZE;

const double WINDOW_WORKERS_X = 54*SCALESIZE;
const double WINDOW_WORKERS_Y = 69*SCALESIZE;

const double FOUNTAIN_SPAWN_X = 115*SCALESIZE;
const double FOUNTAIN_SPAWN_Y = 58*SCALESIZE;

const double LEFT_FOUNTAIN_HANDLE_SPAWN_X = FOUNTAIN_SPAWN_X + 1*SCALESIZE;
const double LEFT_FOUNTAIN_HANDLE_SPAWN_Y = 74*SCALESIZE;

const double RIGHT_FOUNTAIN_HANDLE_SPAWN_X = FOUNTAIN_SPAWN_X + 6*SCALESIZE;
const double RIGHT_FOUNTAIN_HANDLE_SPAWN_Y = 74*SCALESIZE;

bool init();

bool loadMedia();

bool setup();
#endif
