#include "LoseState.h"
#include "sfwdraw.h"

void LoseState::init(unsigned a_font)
{
	font = a_font;
}

void LoseState::play()
{
	timer = 3.f;
}

void LoseState::step()
{
	timer -= sfw::getDeltaTime();
}

void LoseState::draw() const
{
	sfw::drawString(font, "You Lose! That's okay, though!", 400 - (24 * 20 / 2), 300, 20, 20, 0, '\0', BLACK);

}

STATE LoseState::next() const
{
	if (timer < 0) return ENTER_SPLASH;

	return LOSE;
}
