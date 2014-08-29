#ifndef _UI_H
#define _UI_H

struct Menu
{
	char**text; 
	int nLine; 
};

void init_menu();
void deinit_menu();
void load_menu(char *szFile, Menu* pMenu);
void render_menu(Menu* pMenu);



void render();              // renders the current state of the game to the console

void renderGame();

void recordFinalScore();

void renderName();













#endif