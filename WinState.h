#pragma once

#include "statesconst.h"

//Each State should / could have the following :
//init->First created.
//play->On transition.
//step->On the game loop.
//draw->On the game loop.
//next->returns the state we are transitioning to.


class WinState
{
	float timer;
	unsigned font;
	unsigned winTex;

public:
	void init(unsigned font, unsigned winTex);
	void play();
	void step();
	void draw() const;
	STATE next() const;
};