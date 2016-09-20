#include "LoseState.h"
#include "sfwdraw.h"

void LoseState::init(unsigned a_font, unsigned a_loseTex)
{
	font = a_font;
	loseTex = a_loseTex;
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
	sfw::drawTexture(loseTex, 0, 600, sfw::getTextureWidth(loseTex), sfw::getTextureHeight(loseTex),0.f, false);
}

STATE LoseState::next() const
{
	if (timer < 0) return ENTER_SPLASH;

	return LOSE;
}
