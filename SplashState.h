#pragma once

#include "statesconst.h"

//Each State should / could have the following :
//init->First created.
//play->On transition.
//step->On the game loop.
//draw->On the game loop.
//next->returns the state we are transitioning to.


class SplashState
{
	float timer;
	unsigned font;
	unsigned drug;
public:
	void init(unsigned font, unsigned drug);
	void play();
	void step();
	void draw() const;
	STATE next() const;
};