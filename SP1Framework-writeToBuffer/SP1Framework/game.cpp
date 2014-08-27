// This is the main file for the game logic and function
//
//
#include "game.h"
#include "UI.h"
#include "ball.h"
#include "catch.h"
#include "Highscore.h"
#include "Framework\console.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::ifstream;



bool keyPressed[K_COUNT];
bool ingame = false;

double elapsedTime;
double deltaTime;
COORD charLocation;
COORD charLocation1;
COORD charLocationMid;
COORD charLocationTop;
extern bool fHandup;
extern double catchtimer;


COORD ConsoleSize = { 80, 25 };




GameState State = MAINMENU;







void init()
{
	initConsole(ConsoleSize,"CATCHBALLS");
   
	charLocation.X = ConsoleSize.X / 2 + 5;
	charLocation.Y = ConsoleSize.Y - 1;
	
	charLocationMid.X = ConsoleSize.X / 2 + 5;
	charLocationMid.Y = ConsoleSize.Y - 2;

	charLocationTop.X = ConsoleSize.X / 2 + 5;
	charLocationTop.Y = ConsoleSize.Y - 3;


	ballinit();

	elapsedTime = 0.0;
	
}

void shutdown()
{
    // Reset to white text on black background
	colour(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);

	shutDownConsole();
}

void getInput()
{    
    keyPressed[K_UP] = isKeyPressed(VK_UP);
    keyPressed[K_DOWN] = isKeyPressed(VK_DOWN);
    keyPressed[K_LEFT] = isKeyPressed(VK_LEFT);
    keyPressed[K_RIGHT] = isKeyPressed(VK_RIGHT);
	keyPressed[K_ESCAPE] = isKeyPressed(VK_ESCAPE);
	keyPressed[K_ENTER] = isKeyPressed(VK_RETURN);
	keyPressed[K_SPACE] = isKeyPressed(VK_SPACE);
	keyPressed[K_BACKSPACE] = isKeyPressed(VK_BACK);
	keyPressed[K_HOME] = isKeyPressed(VK_HOME);
	keyPressed[K_1] = isKeyPressed(VK_F1);
	keyPressed[K_2] = isKeyPressed(VK_F2);
}


void updateHandsup()
{
	if (keyPressed[K_SPACE])
	{
		fHandup = true;
		charLocation1.X = charLocation.X - 1;
		charLocation1.Y = charLocation.Y - 2;
	}
}

void update(double dt) 
{
	
	
	
	if (State == INGAME)
	{
		elapsedTime += dt;
		deltaTime = dt;
	}
	

	switch (State)
	{
	
	case MAINMENU:
		updateMainMenu();
		break;
	case HIGHSCORE:
		updateHighscore();
		break;

	case INGAME:
		updateGame();
		break;

	case PAUSE:
		updatePause();
		break;
	case DEAD:
		updateDead();
		break;

	case EXIT:
		updateExit();
		break;

	}
	
	
	// Updating the location of the character based on the key press

	
	if (keyPressed[K_ESCAPE])
	{
		g_quitGame = true;
	}
	
	
}

void updateHighscore()//HIGHSCORE
{
	if (keyPressed[K_1])
	{
		State = MAINMENU;
	}
	if (keyPressed[K_ESCAPE])
	{
		State = EXIT;
	}
}

void updatePause()//PAUSE
{
	if (keyPressed[K_2]||keyPressed[K_ESCAPE])
	{
		State = EXIT;
	}
	if (keyPressed[K_1])
	{
		
		State = INGAME;
		
	}
	

}


void updateExit()//EXIT
{
	return;
}



void updateGame()//INGAME
{


	if (keyPressed[K_LEFT]&& charLocation.X > ConsoleSize.X / 2 - 10)

	{


		charLocation.X-=7;
		charLocationMid.X-=7;
		charLocationTop.X-=7;
		


	}

	if (keyPressed[K_RIGHT]&& charLocation.X < ConsoleSize.X - 16)
	{

		charLocation.X+=7;
		charLocationMid.X+=7;
		charLocationTop.X+=7;
		

	}

	if (keyPressed[K_BACKSPACE])
	{
		
		State = PAUSE;
	}
	if (keyPressed[K_ESCAPE])
	{
		State = EXIT;
	}
}



void updateMainMenu()//MAINMENU
{
	if (keyPressed[K_ENTER])
	{
		State = INGAME;
	}
	
	if (keyPressed[K_HOME])
	{
		State = HIGHSCORE;
	}

	if (keyPressed[K_ESCAPE])
	{
		State = EXIT;
	}

}

void update_hand()
{
	if (keyPressed[K_SPACE])
	{
		fHandup = true;
		catchtimer = elapsedTime + 1;
	}
	hand_down();
}

void updateDead()
{
	if (keyPressed[K_ENTER])
	{
		State = MAINMENU;
	}
}
