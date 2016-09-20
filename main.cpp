
#include "sfwdraw.h"
#include <time.h>
#include <math.h>
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include "score.h"
#include "gameState.h"
#include "SplashState.h"
#include "MenuState.h"
#include "main.h"
#include "Versus.h"
#include "WinState.h"
#include "LoseState.h"
using namespace sfw;

void CRTfilter(unsigned a_filter, unsigned a_edge, float &acc)
{
	acc += 10;
	drawTexture(a_filter, 0, 600 + (sin(acc) * 2), sfw::getTextureWidth(a_filter), sfw::getTextureHeight(a_filter), 0.f, false);
	drawTexture(a_edge, 0, 600, sfw::getTextureWidth(a_edge), sfw::getTextureHeight(a_edge), 0.f, false);
}

void main()
{
	float acc = 0;
	initContext(800, 600, "Breaking A Brick Wall With Your Skull Simulator");
	setBackgroundColor(WHITE);

	unsigned font = loadTextureMap("res/fontmap.png", 16, 16);
	unsigned loseTex = loadTextureMap("res/pat.png");
	unsigned winTex = loadTextureMap("res/wario.png");
	unsigned drug = loadTextureMap("res/drug.png");
	unsigned edge = loadTextureMap("res/crtedge.png");
	unsigned filter = loadTextureMap("res/crtfilter.png");
	unsigned brick = loadTextureMap("res/brick.png");
	
	LoseState lose;
	SplashState splash;
	GameState gs;
	MenuState menu;
	Versus versus;
	WinState win;

	win.init(font, winTex);
	lose.init(font, loseTex);
	splash.init(font, drug);
	gs.create();
	menu.init(font, brick);
	STATE current = ENTER_SPLASH;
	bool running = true;

	while (stepContext() && running)
	{	
		switch (current)
		{
		case ENTER_SPLASH: splash.play();
		case SPLASH:
			splash.step();
			splash.draw();
			
			current = splash.next();
			break;

		case ENTER_MENU: menu.play();
		case MENU:
			menu.step();
			menu.draw();
			
			current = menu.next();
			break;

		case ENTER_GAME: gs.create();
		case GAME:
			gs.update();
			gs.draw();
			
			current = gs.next();
			break;
		case ENTER_VERSUS: versus.create();
		case VERSUS:
			versus.update();
			versus.draw();
			
			current = versus.next();
			break;
		case ENTER_VICTORY: win.play();
		case VICTORY:
			win.step();
			win.draw();
			
			current = win.next();
			break;
		case ENTER_LOSE: lose.play();
		case LOSE:
			lose.step();
			lose.draw();
			
			current = lose.next();
			break;
		case QUIT:
			running = false;
			break;

		}
		CRTfilter(filter, edge, acc);
		//GameState::updateGameState(gs);
		//GameState::drawGameState(gs);
	}

	termContext();
}

