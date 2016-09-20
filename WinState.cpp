#include "WinState.h"
#include "sfwdraw.h"

void WinState::init(unsigned a_font)
{
	font = a_font;
}

void WinState::play()
{
	timer = 3.f;
}

void WinState::step()
{
	timer -= sfw::getDeltaTime();
}

void WinState::draw() const
{
	sfw::drawString(font, "You Win! But at what cost?", 400 - (24 * 20 / 2), 300, 20, 20, 0, '\0', BLACK);
}

STATE WinState::next() const
{
	// Transition
	if (timer < 0) return ENTER_SPLASH;

	return VICTORY;
}
