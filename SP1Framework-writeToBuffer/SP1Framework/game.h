#ifndef _GAME_H
#define _GAME_H

#include "Framework\timer.h"

#include <iostream>
#include <fstream>
#include <string>

using std::string;



extern StopWatch g_timer;
extern bool g_quitGame;
extern bool ingame;

enum Keys
{
    K_UP,
    K_DOWN,
    K_LEFT,
    K_RIGHT,
	K_1,
	K_2,
	K_SPACE,
	K_ENTER,
	K_BACKSPACE,
	K_HOME,
    K_ESCAPE,
    K_COUNT
};
enum GameState
{
	MAINMENU = 1, 
	HIGHSCORE,
	INGAME,
	PAUSE,
	EXIT,
	DEAD,
	MAX
};






void init();                // initialize your variables, allocate memory, etc
void getInput();            // get input from player
void update(double dt);     // update the game and the state of the game

void shutdown();            // do clean up, free memory

void mainLoop();



void updateGame();
void updatePause();
void updateMainMenu();
void updateExit();
void updateHighscore();
void updateDead();

void check_ball_hand_position();
void gen_ball();




#endif // _GAME_H