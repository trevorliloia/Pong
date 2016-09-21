#include "MenuState.h"
#include "sfwdraw.h"
#include <stdio.h>
using namespace sfw;

void MenuState::init(unsigned a_font, unsigned a_brick)
{
	font = a_font;
	brick = a_brick;
}

void MenuState::play()
{
	timer = 3.f;
	game = false;
	versus = false;
	quit = false;
	aster = false;
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
	if (getKey('A') && getKey('S'))
	{
		aster = true;
	}
}

void MenuState::draw() const
{
	drawString(font, "[P]lay or [V]ersus? \nPlease Don't [Q]uit.", 200, 300, 20, 20, 0, '\0', BLACK);
	drawTexture(brick, 0, 600, sfw::getTextureWidth(brick), sfw::getTextureHeight(brick), 0.f, false);
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
	if (aster)
	{
		return ENTER_ASTER;
	}
	return MENU;
}
