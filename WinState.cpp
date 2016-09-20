#include "WinState.h"
#include "sfwdraw.h"

void WinState::init(unsigned a_font, unsigned a_win)
{
	font = a_font;
	winTex = a_win;
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
	sfw::drawTexture(winTex, 0, 600, sfw::getTextureWidth(winTex), sfw::getTextureHeight(winTex), 0.f, false);
}

STATE WinState::next() const
{
	// Transition
	if (timer < 0) return ENTER_SPLASH;

	return VICTORY;
}
