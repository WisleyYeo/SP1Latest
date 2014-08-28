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
extern COORD charLocationLegs;
extern COORD charLocation;
extern COORD charLocationMid;
extern COORD charLocationTop;
extern bool fHandup;



extern GameState State;

Highscore HS[10];

extern int score;



COORD c;

Menu mainMenu; 
Menu pauseMenu; 
Menu exitMenu; 
Menu backgroundMenu; 
Menu deadMenu;

// load the menu into memory 
void load_menu(char *szFile, Menu* pMenu)
{
	ifstream FileMenu;
	string Data;
	int i=0; 

	FileMenu.open(szFile);
	while (!FileMenu.eof())
	{
		getline(FileMenu, Data);
		i++; 
	}

	pMenu->text = new char*[i]; 
	pMenu->nLine = i; 
	i = 0; 
	FileMenu.close(); 
	FileMenu.open(szFile);	
	while (!FileMenu.eof())
	{
		getline(FileMenu, Data);
		pMenu->text[i] = new char[Data.length()+1]; 
		strcpy(pMenu->text[i],Data.c_str()); 
		pMenu->text[i][Data.length()] = 0; 
		i++; 
	}
}

// call init_menu in game.cpp to init the various menu
void init_menu()
{
	load_menu("menu.txt", &mainMenu); 
	load_menu("pausemenu.txt", &pauseMenu); 
	load_menu("background.txt", &backgroundMenu);		
	load_menu("ragequit.txt", &exitMenu);
	load_menu("dead.txt", &deadMenu);
}


// free all the memory used for the menu 
void free_menu(Menu*pMenu)
{
	for (int i=0; i<pMenu->nLine; i++)
	{
		delete pMenu->text[i]; 
		pMenu->text[i] = NULL; 
	}

	delete [] pMenu->text;
}

// call deinit_menu in game.cpp to free the memory allocated for various menus
void deinit_menu()
{
	free_menu(&mainMenu); 
	free_menu(&pauseMenu); 
	free_menu(&backgroundMenu);		
	free_menu(&exitMenu);
	free_menu(&deadMenu);
}

// render the menu 
void render_menu(Menu*pMenu)
{
	c.X = 0;
	c.Y = 1;

	for (int i=0; i<pMenu->nLine; i++)	
	{
		if (strlen(pMenu->text[i]))
			writeToBuffer(c, pMenu->text[i]);
		c.Y++;
	}

	
}

void renderGame()
{


	endfall();
	update_hand();
	check_ball_hand_position();




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
	c.X = ConsoleSize.X /2;
	c.Y = 0;
	writeToBuffer(c, ss.str());

	
	

	
	
	

	// render character

	if (fHandup == true)
	{
		
		writeToBuffer(charLocationLegs, " | | ", 0x0C);

		writeToBuffer(charLocation, " \\_/ ", 0x0C);

		writeToBuffer(charLocationMid, "\\(_)/", 0x0C);

		writeToBuffer(charLocationTop, "_", 0x0C);

	}
	
	
	else
	{
		writeToBuffer(charLocationLegs, " | | ", 0x0C);

		writeToBuffer(charLocation, "/\\_/\\", 0x0C);

		writeToBuffer(charLocationMid, " (_)", 0x0C);

		writeToBuffer(charLocationTop, "_", 0x0C);
	}


	
	
	//flushBufferToConsole();
}




void render()
{
	// Clears the buffer with this colour attribute
	clearBuffer(0x0F);

	init_menu();

	switch (State)
	{
	case MAINMENU:
		SetConsoleTitle(L"MAIN MENU");
		render_menu(&mainMenu);
		break;

	case HIGHSCORE:	
		LoadHS("Highscore.txt", HS);
		SortHS(HS);
		PrintHS(HS);
		break;

	case INGAME:
		SetConsoleTitle(L"CATCHBALLS");
		renderGame();
		render_menu(&backgroundMenu);
		break;

	case PAUSE:
		SetConsoleTitle(L"PAUSED");
		render_menu(&pauseMenu);
		break;

	case DEAD:
		SetConsoleTitle(L"YOU LOST !");
		render_menu(&deadMenu);
		//renderDead();
		break;

	case EXIT:
		SetConsoleTitle(L"RAGEQUITTING");
		render_menu(&exitMenu);
		deinit_menu();
		break;

	}
	// Writes the buffer to the console, hence you will see what you have written
	flushBufferToConsole();

}



