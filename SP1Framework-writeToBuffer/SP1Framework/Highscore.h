#ifndef _HIGHSCORE_H
#define _HIGHSCORE_H

#include <iostream>
#include <string>

using std::string;



struct Highscore
{
	string Name;
	int Score;
};


void LoadHS(string File, Highscore *Player);
void PrintHS(Highscore *Player);
void WriteHS(string File, Highscore *Player);
void SortHS(Highscore *Player);



#endif
