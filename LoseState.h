#pragma once

#include "statesconst.h"

//Each State should / could have the following :
//init->First created.
//play->On transition.
//step->On the game loop.
//draw->On the game loop.
//next->returns the state we are transitioning to.


class LoseState
{
	float timer;
	unsigned font;

public:
	void init(unsigned font);
	void play();
	void step();
	void draw() const;
	STATE next() const;
};