//Setup.h
#include<X11/Xlib.h>
#include<SDL2/SDL_ttf.h>
#include<SDL2/SDL_image.h>

#ifndef Setup_h
#define Setup_h

//double SCALESIZE;


const double PI = 3.14159265;
const double GRAVITY = 9.8;
const int MAX_MULTIPLIER_VAL = 45;

extern double OFFSET;
extern Uint32 LETTER_LIFETIME;
extern double SCALESIZE;
extern double LEVEL_ONE_SPEED;
extern double LEVEL_SPEED_INCREASE;
extern double LETTER_SLOW_SPEED;
extern double WALKING_SPEED;
extern double WALKING_ANIMATION_CHANGE_SPEED;
extern double SCREEN_ORIG_WIDTH;
extern double SCREEN_ORIG_HEIGHT;
extern double SCREEN_WIDTH;
extern double SCREEN_HEIGHT;
extern double TEXT_ROW_OFFSET;
extern double MULTIPLIER_Y;
extern double MULTIPLIER_X;
extern char CODE_FONT[30];
extern SDL_Color CODE_COLOR;
extern SDL_Color SHADOW_COLOR;
extern double SCOREBOARDX;
extern double SCOREBOARDY;
extern double SCOREBOARD_FONT_SIZE;
extern double SCREEN_STARTING_YPOS;
extern double SCREEN_STARTING_XPOS;
extern double SCREEN_END_YPOS;
extern double TEXT_SIZE;
extern int  NUM_TEXT_ROWS;
extern int MAX_TEXT_LENGTH;
extern int FLAG_XPOS;
extern int FLAG_YPOS;
extern double MAIN_MENU_FONT_SIZE;
extern SDL_Color MENU_FONT_COLOR;
extern SDL_Color MENU_SHADOW_FONT_COLOR;
extern double TIP_TEXT_XPOS;
extern double TIP_TEXT_YPOS;
extern double MENU_FRAMES_SPAWN_Y;
extern double CHARACTER_SCORE_X;
extern double CHARACTER_SCORE_Y;
extern double CHARACTER_SCORE_FONT_SIZE;
extern int LETTER_TYPED_SCORE;
extern double GROUND_VALUE;
extern double MAIN_CHARACTER_OBJECT_Y;
extern double MAIN_CHARACTER_OBJECT_X;
extern double MAIN_CHARACTER_OBJECT_W;
extern double MAIN_CHARACTER_OBJECT_H;
extern double MAIN_CHARACTER_DESK_SPAWN_Y;
extern double MAIN_CHARACTER_DESK_SPAWN_X;
extern double COWORKER_OBJECT_Y;
extern double COWORKER_OBJECT_X;
extern double COWORKER_OBJECT_W;
extern double COWORKER_OBJECT_H;
extern double COWORKER_SPAWN_X;
extern double COWORKER_SPAWN_Y;
extern double COWORKER_COMPUTER_X;
extern double COWORKER_COMPUTER_Y;
extern double BOSS_OBJECT_Y;
extern double BOSS_OBJECT_X;
extern double BOSS_OBJECT_W;
extern double BOSS_OBJECT_H;
extern double BOSS_SPAWN_X;
extern double BOSS_SPAWN_Y;
extern int BOSS_BLINK_TIME;
extern int BOSS_BLINK_DURATION;
extern double TRASHCAN_SPAWN_X;
extern double TRASHCAN_SPAWN_Y;
extern double CLOCK_SPAWN_X;
extern double CLOCK_SPAWN_Y;
extern double DOOR_SPAWN_X;
extern double DOOR_SPAWN_Y;
extern double WINDOW_WORKER_X;
extern double WINDOW_WORKER_Y;
extern double WINDOW_WORKERS_X;
extern double WINDOW_WORKERS_Y;
extern double FOUNTAIN_SPAWN_X;
extern double FOUNTAIN_SPAWN_Y;
extern double LEFT_FOUNTAIN_HANDLE_SPAWN_X;
extern double LEFT_FOUNTAIN_HANDLE_SPAWN_Y;
extern double RIGHT_FOUNTAIN_HANDLE_SPAWN_X;
extern double RIGHT_FOUNTAIN_HANDLE_SPAWN_Y;
extern double TROPHY_SPAWN_X;
extern double TROPHY_HEIGHT;
extern double TROPHY_WIDTH;





bool init();

bool loadMedia();

bool setup();
#endif
