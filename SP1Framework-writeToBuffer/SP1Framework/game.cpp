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
COORD charLocationLegs;
COORD charLocation;
COORD charLocationMid;
COORD charLocationTop;
extern bool fHandup;
extern double catchtimer;

COORD ConsoleSize = { 80, 25 };

GameState State = MAINMENU;

void init()
{
	initConsole(ConsoleSize);

	charLocationLegs.X = ConsoleSize.X / 2 + 4;
	charLocationLegs.Y = ConsoleSize.Y - 1;

	charLocation.X = ConsoleSize.X / 2 + 4;
	charLocation.Y = ConsoleSize.Y - 2;

	charLocationMid.X = ConsoleSize.X / 2 + 4;
	charLocationMid.Y = ConsoleSize.Y - 3;

	charLocationTop.X = ConsoleSize.X / 2 + 6;
	charLocationTop.Y = ConsoleSize.Y - 4;

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
		if (keyPressed[K_ESCAPE])
		{
			g_quitGame = true;
		}
		break;

	}


	// Updating the location of the character based on the key press


	


}

void updateHighscore()//HIGHSCORE
{
	if (keyPressed[K_1])
	{
		Beep(1500, 75);
		State = MAINMENU;
	}
	if (keyPressed[K_ESCAPE])
	{
		Beep(1000, 90);
		State = EXIT;
	}
}

void updatePause()//PAUSE
{
	if (keyPressed[K_2] || keyPressed[K_ESCAPE])
	{
		Beep(1000, 90);
		State = EXIT;
	}
	if (keyPressed[K_1])
	{
		Beep(1500, 75);
		State = INGAME;

	}


}


void updateExit()//EXIT
{
	
}



void updateGame()//INGAME
{


	if (keyPressed[K_LEFT] && charLocation.X > ConsoleSize.X / 2 - 16 && fHandup != true)

	{



		Beep(1440, 62);
		Beep(1000, 62);

		charLocation.X -= 7;
		charLocationMid.X -= 7;
		charLocationTop.X -= 7;
		charLocationLegs.X -= 7;



	}

	if (keyPressed[K_RIGHT] && charLocation.X < ConsoleSize.X - 16 && fHandup != true)
	{


		

		Beep(1440, 62);
		Beep(2000, 62);

		charLocation.X += 7;
		charLocationMid.X += 7;
		charLocationTop.X += 7;
		charLocationLegs.X += 7;


	}

	if (keyPressed[K_BACKSPACE])
	{
		Beep(3500, 75);
		State = PAUSE;
	}
	if (keyPressed[K_ESCAPE])
	{
		Beep(1000,90);
		State = EXIT;
	}
}



void updateMainMenu()//MAINMENU
{
	if (keyPressed[K_ENTER])
	{
		Beep(3000, 62);
		State = INGAME;
	}

	if (keyPressed[K_HOME])
	{
		Beep(3000, 62);
		State = HIGHSCORE;
	}

	if (keyPressed[K_ESCAPE])
	{
		Beep(1000, 62);
		State = EXIT;
	}

}

void update_hand()
{
	if (keyPressed[K_SPACE] && fHandup != true)
	{
		Beep(2000, 62);
		fHandup = true;
		catchtimer = elapsedTime + 1;
	}
	hand_down();
}

void updateDead()
{
	
	if (keyPressed[K_ENTER])
	{
		Beep(1500, 62);
		reset();
		State = MAINMENU;
	}
}
