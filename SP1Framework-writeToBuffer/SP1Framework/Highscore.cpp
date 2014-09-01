#include "Highscore.h"
#include "Framework\console.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>


using std::string;
using std::cout;
using std::endl;

extern COORD c;








void LoadHS(string File, Highscore *Player) //Load contents from text file, stores in memory
{
	int i = 0;
	std::ifstream Highscore(File);

	if (Highscore.is_open())
	{
		while (!Highscore.eof())
		{

			Highscore >> Player[i].Name;
			Highscore >> Player[i].Score;
			i++;
		}
	}
	Highscore.close();
} 

void PrintHS(Highscore *Player) //Prints name and score from memory
{
	int i = 0;
	int j = 1;
	std::ostringstream ss;

	SetConsoleTitle(L"HIGHSCORES");

	c.X = 0;
	c.Y = 0;

	writeToBuffer(c, "---HIGHSCORES---",0x0D);

	
	c.X = 0;
	c.Y = 1;


	while (Player[i].Name.length() != 0 && j <= 10)
	{

		
		ss.str("");
		ss << j << ". " << Player[i].Name << " " << Player[i].Score;
		writeToBuffer(c, ss.str(),0x0D);
		i++;
		j++;
		c.Y++;
	}

	c.X = 0;
	c.Y = 20;
	writeToBuffer(c, "[F1] Return To Main Menu",0x0A);
	c.Y++;
	writeToBuffer(c, "[ESC] Exit Game",0x0A);




}


void SortHS(Highscore *Player) //Sorts highscore from top to bottom, highest score to lowest score
{
	for (int i = 0; i < 100; i++)
	{
		for (int j = i + 1; j < 100; j++)
		{
			if (Player[i].Score < Player[j].Score)//Basically pushes the highest score top and pushes the lowest to the bottom
			{
				string TempName = Player[i].Name;
				int TempScore = Player[i].Score;
				Player[i].Name = Player[j].Name;
				Player[i].Score = Player[j].Score;
				Player[j].Name = TempName;
				Player[j].Score = TempScore;
				
			}
		}

	}
	
}


