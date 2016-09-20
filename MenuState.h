#pragma once

#include "statesconst.h"

//Each State should / could have the following :
//init->First created.
//play->On transition.
//step->On the game loop.
//draw->On the game loop.
//next->returns the state we are transitioning to.


class MenuState
{
	float timer;
	unsigned font;
	unsigned brick;
	bool game =  false;
	bool versus = false;
	bool quit = false;
	bool charEntered = false;
	char favLetter;
	char menuItem;

public:
	void init(unsigned font, unsigned brick);
	void play();
	void step();
	void draw() const;
	STATE next() const;
};