#include "ball.h"
#include "UI.h"
#include "game.h"
#include "Framework\console.h"
#include <iostream>
#include <vector>

using std::vector;
using std::cout;


double balltimer = 1.0;
double pulsetimer = 1.0;
extern int score;
extern double elapsedTime;
extern COORD ConsoleSize;
extern COORD charLocationLegs;
extern COORD charLocation;
extern COORD charLocationMid;
extern COORD charLocationTop;

COORD dudeLocationLegs;
COORD dudeLocation;
COORD dudeLocationMid;
COORD dudeLocationTop;

extern COORD c;


vector<ball> ballwave;

void ballpulse(double x)
{
	if (elapsedTime > pulsetimer)
	{
		ballwave[rand() %ballwave.size()].inplay += 1;
		pulsetimer += x;
	}
}


void ballinit()
{
	dudeLocationLegs.X = ConsoleSize.X / 2 + 5;
	dudeLocationLegs.Y = 6;

	dudeLocation.X = ConsoleSize.X / 2 + 4;
	dudeLocation.Y = 5;
	
	dudeLocationMid.X = ConsoleSize.X / 2 + 5;
	dudeLocationMid.Y = 4;

	dudeLocationTop.X = ConsoleSize.X / 2 + 6;
	dudeLocationTop.Y = 3;
	gen_ball();
}

void gen_ball()
{
	for (size_t i = 0; i < 21; ++i)
	{
		ball BALL;
		ballwave.push_back(BALL);
		if (i == 0 || i == 7 || i == 14)
		{
			ballwave[i].x = 24;
		}
		else
		{
			ballwave[i].x = ballwave[i-1].x + 7;
		}
		ballwave[i].ballpos = 2;
		ballwave[i].inplay = 0;
	}
}

void ballfall(double x,double y)
{
	ballpulse(x);
	for (size_t i = 0; i < 21; ++i)
	{
		if (ballwave[i].ballpos < ConsoleSize.Y && ballwave[i].inplay != 0)
		{
			if (elapsedTime > balltimer)
			{
				ballwave[i].ballpos += 2;
			}
			c.X = ballwave[i].x;
			c.Y = ballwave[i].ballpos;

			
			writeToBuffer(c, " O ", 0x34);

		}
		else if (ballwave[i].ballpos >= ConsoleSize.Y - 1)
		{
			ballwave[i].inplay = 0;
			ballwave[i].ballpos = 2;
			score -= 1;
		}
	}
	if (elapsedTime > balltimer)
	{
		balltimer += y;
	}
	
}


void endfall()
{
	if (elapsedTime > 1000)
	{
		ballfall(0.1,0.1);
	}
	else if (elapsedTime > 100)
	{
		ballfall(2,0.5);
	}
	else if (elapsedTime > 80)
	{
		ballfall(2,0.6);
	}
	else if(elapsedTime > 60)
	{
		ballfall(2,0.7);
	}
	else if (elapsedTime > 40)
	{
		ballfall(2,0.8);
	}
	else if (elapsedTime > 20)
	{
		ballfall(2,0.9);
	}
	else
	{
		ballfall(2,1.0);
	}
	balldude();
}

void reset()
{
	elapsedTime = 0;
	balltimer = 0;
	pulsetimer = 0;
	score = 0;
	for (size_t i = 0; i < 21; ++i)
	{
		ballwave[i].ballpos = 2;
		ballwave[i].inplay = 0;
	}
	
	charLocationLegs.X = ConsoleSize.X / 2 + 4;
	charLocationLegs.Y = ConsoleSize.Y - 1;

	charLocation.X = ConsoleSize.X / 2 + 4;
	charLocation.Y = ConsoleSize.Y - 2;
	
	charLocationMid.X = ConsoleSize.X / 2 + 4;
	charLocationMid.Y = ConsoleSize.Y - 3;

	charLocationTop.X = ConsoleSize.X / 2 + 6;
	charLocationTop.Y = ConsoleSize.Y - 4;
}

void balldude()
{

	for (size_t i = 0; i < 21; ++i)
	{

		if (ballwave[i].ballpos == 4 && ballwave[i].inplay != 0)
		{
			dudeLocationLegs.X = ballwave[i].x + 3;

			dudeLocation.X = ballwave[i].x + 3;

			dudeLocationMid.X = ballwave[i].x + 2;

			dudeLocationTop.X = ballwave[i].x + 4;

			writeToBuffer(dudeLocationLegs, "| | ", 0x3A);
			writeToBuffer(dudeLocation, "\\_/\\", 0x3A);
			writeToBuffer(dudeLocationMid, "\\(_)", 0x3A);
			writeToBuffer(dudeLocationTop, "_", 0x3A);
		}
		else if(ballwave[i].ballpos == 6 && ballwave[i].inplay != 0)
		{
			dudeLocationLegs.X = ballwave[i].x + 3;

			dudeLocation.X = ballwave[i].x + 2;

			dudeLocationMid.X = ballwave[i].x + 3;

			dudeLocationTop.X = ballwave[i].x + 4;

			writeToBuffer(dudeLocationLegs, "| | ", 0x3A);
			writeToBuffer(dudeLocation, "/\\_/\\", 0x3A);
			writeToBuffer(dudeLocationMid, "(_)", 0x3A);
			writeToBuffer(dudeLocationTop, "_", 0x3A);
		}

	}
	
}