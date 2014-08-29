#include "game.h"
#include "highscore.h"
#include "Framework\console.h"
#include "ball.h"
#include "catch.h"
#include "UI.h"
#include "time.h"
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
extern vector<ball> ballwave;
bool fHandup = false;
extern COORD charLocation;
extern double elapsedTime;
int score =0;
double catchtimer;

extern GameState State;


void hand_down()
{
	if (elapsedTime > catchtimer)
	{
		fHandup = false;
	}
}

void check_ball_hand_position()
{
	for (size_t i = 0; i < 21; ++i)
	{
		if (ballwave[i].inplay != 0)
		{

			if (ballwave[i].ballpos >= charLocation.Y - 1  && ballwave[i].x == charLocation.X + 1)
			{		
				ballwave[i].inplay = 0;
				ballwave[i].ballpos = 2;
				
				if (fHandup == true)
				{
					Beep(12500, 70);
					Beep(13000, 70);
					Beep(13500, 70);
					Beep(14000, 70);
					score += 3;	
				}
				else
				{
					
						Beep(800, 62);
						Beep(600, 62);
						Beep(400, 62);
						Beep(200, 62);
			
					State = DEAD;
					
				}	 
			}	
		}
	}
}

