#ifndef _BALL_H
#define _BALL_H

#include <vector>

using std::vector;

void ballfall(float x,float y);
void ballinit();
void ballpulse(float x);
void endfall();

struct ball
{
	int x;
	int ballpos;
	bool inplay;
};




#endif