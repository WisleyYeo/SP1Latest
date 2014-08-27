#include "UI.h"
#include "ball.h"
#include "game.h"
#include "catch.h"
#include "Highscore.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

#include "Framework\console.h"

// Console size, width by height
extern COORD ConsoleSize;


using std::string;
using std::cout;
using std::endl;
using std::ifstream;

extern double elapsedTime;
extern double deltaTime;
extern COORD charLocation;
extern COORD charLocationMid;
extern COORD charLocationTop;
extern bool fHandup;



extern GameState State;

Highscore HS[10];

extern int score;



COORD c;



void renderExit()
{
	
	ifstream ragequit;
	string rage;

	c.X = 0;
	c.Y = 0;

	SetConsoleTitle(L"RAGEQUITTING");
	
	ragequit.open("ragequit.txt");
	while (!ragequit.eof())
	{
		getline(ragequit, rage);
		writeToBuffer(c, rage);
		c.Y++;
	}
	
	g_quitGame = true;
}



void renderGame()
{
	clearBuffer(0x0F);
	
	background();
	endfall();
	update_hand();
	



	//render the game


	//render test screen code (not efficient at all)
	const WORD colors[] = {
		0x1A, 0x2B, 0x3C, 0x4D, 0x5E, 0x6F,
		0xA1, 0xB2, 0xC3, 0xD4, 0xE5, 0xF6
	};

	
	


	// displays the framerate
	std::ostringstream ss;
	ss << std::fixed << std::setprecision(3);
	ss << 1.0 / deltaTime << "fps";
	c.X = ConsoleSize.X - 9;
	c.Y = 0;
	writeToBuffer(c, ss.str());

	// displays the elapsed time
	ss.str("");
	ss << elapsedTime << "secs";
	c.X = 0;
	c.Y = 0;
	writeToBuffer(c, ss.str(), 0x59);

	//display the score
	ss.str("");
	ss << "Score : " << score;
	c.X = 0;
	c.Y = 3;
	writeToBuffer(c, ss.str(), 0x60);
	check_ball_hand_position();

	
	
	

	// render character

	if (fHandup == true)
	{
		writeToBuffer(charLocation, " \\_/ ", 0x0C);

		writeToBuffer(charLocationMid, "\\(_)/", 0x0C);

		writeToBuffer(charLocationTop, "  _", 0x0C);

	}
	
	
	else
	{
		writeToBuffer(charLocation, "/\\_/\\", 0x0C);

		writeToBuffer(charLocationMid, " (_)", 0x0C);

		writeToBuffer(charLocationTop, "  _", 0x0C);
	}


	
	
	//flushBufferToConsole();
}
 




void renderMainMenu()
{
	//Menu Title
	
	c.X = 0;
	c.Y = 0;

		string output;
		ifstream Menu;
		Menu.open("menu.txt");
		SetConsoleTitle(L"MAIN MENU");
		
		while (!Menu.eof())
		{

			getline(Menu, output);
			writeToBuffer(c, output);
			c.Y++;

		}
		Menu.close();

	
	
}

void renderPause()
{
	//clearBuffer();

	c.X = 0;
	c.Y = 0;
	ifstream PauseMenu;
	string Data;


	

	SetConsoleTitle(L"PAUSED");
	PauseMenu.open("pausemenu.txt");
	while (!PauseMenu.eof())
	{
		getline(PauseMenu, Data);
		writeToBuffer(c, Data);
		c.Y++;
	}
	

	

	PauseMenu.close();

	
}

void renderDead()
{
	ifstream deadscreen;
	string data;

	c.X = 0;
	c.Y = 0;
	SetConsoleTitle(L"YOU LOST");

	deadscreen.open("dead.txt");

	while (!deadscreen.eof())
	{
		getline(deadscreen, data);
		writeToBuffer(c, data);
		c.Y++;
	}

	deadscreen.close();
	
	string name;
	//gotoXY(32, 22);
	std::cin >> name;

	
}

void render()
{
	// Clears the buffer with this colour attribute
	clearBuffer(0x0F);

	switch (State)
	{
	case MAINMENU:
		renderMainMenu();
		break;
	case HIGHSCORE:
		
		LoadHS("Highscore.txt", HS);
		SortHS(HS);
		PrintHS(HS);
		break;

	case INGAME:
		renderGame();
		break;
	case PAUSE:
		renderPause();
		break;
	case DEAD:
		renderDead();
		break;
	case EXIT:
		renderExit();
		break;

	}
	// Writes the buffer to the console, hence you will see what you have written
	flushBufferToConsole();

}

void background()
{
	ifstream background;
	string BackGround;
	SetConsoleTitle(L"CATCHBALLS");
	background.open("background.txt");

	c.X = 0;
	c.Y = 1;

	
	while (!background.eof())

	{
		getline(background, BackGround);
		writeToBuffer(c, BackGround);
		c.Y++;

	}
	background.close();

	c.X = 0;
	c.Y = 5;
	writeToBuffer(c, score);
	
	

	
}

