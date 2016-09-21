#include "SplashState.h"
#include "sfwdraw.h"

void SplashState::init(unsigned a_font, unsigned a_drug)
{
	font = a_font;
	drug = a_drug;
}

void SplashState::play()
{
	timer = 4.5f;
}

void SplashState::step()
{
	timer -= sfw::getDeltaTime();
}

void SplashState::draw() const
{
	sfw::drawString(font, "Winners Don't Do Drugs!", 400-(24*20/2), 300, 20, 20, 0, '\0', BLACK); 
	sfw::drawTexture(drug, 0, 600, sfw::getTextureWidth(drug), sfw::getTextureHeight(drug), 0.f, false);
}

STATE SplashState::next() const
{
	// Transition
	if (timer < 0) return ENTER_MENU;

	return SPLASH;
}
