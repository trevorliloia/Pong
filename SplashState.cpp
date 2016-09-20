#include "SplashState.h"
#include "sfwdraw.h"

void SplashState::init(unsigned a_font)
{
	font = a_font;
}

void SplashState::play()
{
	timer = 3.f;
}

void SplashState::step()
{
	timer -= sfw::getDeltaTime();
}

void SplashState::draw() const
{
	sfw::drawString(font, "Winners Don't Do Drugs!", 400-(24*20/2), 300, 20, 20, 0, '\0', BLACK);
}

STATE SplashState::next() const
{
	// Transition
	if (timer < 0) return ENTER_MENU;

	return SPLASH;
}
