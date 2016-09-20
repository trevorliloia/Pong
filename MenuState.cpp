#include "MenuState.h"
#include "sfwdraw.h"
#include <stdio.h>
using namespace sfw;

void MenuState::init(unsigned a_font)
{
	font = a_font;
}

void MenuState::play()
{
	timer = 3.f;
	game = false;
	versus = false;
	quit = false;
}

void MenuState::step()
{
	timer -= sfw::getDeltaTime();
	if (getKey('P'))
	{
		game = true;
	}
	if (getKey('V'))
	{
		versus = true;
	}
	if (getKey('Q'))
	{
		quit = true;
	}
}

void MenuState::draw() const
{
	drawString(font, "[P]lay or [V]ersus? \nPlease Don't [Q]uit.", 200, 300, 20, 20, 0, '\0', BLACK);
}

STATE MenuState::next() const
{
	if (game)
	{
		return ENTER_GAME;
	}
	if (versus)
	{
		return ENTER_VERSUS;
	}
	if (quit)
	{
		return QUIT;
	}
	return MENU;
}
