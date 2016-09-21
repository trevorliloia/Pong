
#include "sfwdraw.h"
#include <Windows.h>
#include "MMSystem.h"
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
#include <mciapi.h>
#include "AsterState.h"
#pragma comment(lib, "Winmm.lib")
using namespace sfw;
using namespace std;

void CRTfilter(unsigned a_filter, unsigned a_edge, float &acc)
{
	acc += 10;
	drawTexture(a_filter, 0, 600 + (sin(acc) * 2), sfw::getTextureWidth(a_filter), sfw::getTextureHeight(a_filter), 0.f, false);
	drawTexture(a_edge, 0, 600, sfw::getTextureWidth(a_edge), sfw::getTextureHeight(a_edge), 0.f, false);
}

void main()
{
	
	float acc = 0;
	srand(time(NULL));
	int num = rand() % 20 + 1;
	switch (num)
	{
		case 1:
			initContext(800, 600, "Cathode Ray Bricks");
			break;
		case 2:
			initContext(800, 600, "Breaking A Brick With Your Skull Simulator");
			break;
		case 3:
			initContext(800, 600, "Worst Thing Since Canned Bread");
			break;
		case 4:
			initContext(800, 600, "and they don't stop comin and they don't stop comin and they don't stop comin and they don't stop comin and they don't stop comin and they don't stop comin and they don't stop comin and");
			break;
		case 5:
			initContext(800, 600, "Pat: The Destroyer");
			break;
		case 6:
			initContext(800, 600, "I dropped my monster condom for my magnum dong");
			break;
		case 7:
			initContext(800, 600, "i am trash man");
			break;
		case 8:
			initContext(800, 600, "410,757,864,520 Eaten Pies");
			break;
		case 9:
			initContext(800, 600, "Taaaaaake Meeeeee Ooooon");
			break;
		case 10:
			initContext(800, 600, "Taaaaaake Oooooon Meeeee");
			break;
		case 11:
			initContext(800, 600, "Whose Brick is it Anyway");
			break;
		case 12:
			initContext(800, 600, "Head Wound: Revengeance");
			break;
		case 13:
			initContext(800, 600, "I love maymays");
			break;
		case 14:
			initContext(800, 600, "Carpal Tunnel Simulator");
			break;
		case 15:
			initContext(800, 600, "It's hard to come up with so many titles");
			break;
		case 16:
			initContext(800, 600, "Help! I'm trapped in a game title factory!");
			break;
		case 17:
			initContext(800, 600, "Don't Stop Me Now; I'm having a good time, having a good time, having a good time, having a good time, having a good time");
			break;
		case 18:
			initContext(800, 600, "Let's go clubbing! Seal clubbing!");
			break;
		case 19:
			initContext(800, 600, "Inject the memes into my bloodstream");
			break;
		case 20:
			initContext(800, 600, "Harambe is disappointed");
			break;
		default:
			initContext(800, 600, "No idea how, but it's broken.");
			break;
	}
	
	setBackgroundColor(WHITE);

	unsigned font = loadTextureMap("res/fontmap.png", 16, 16);
	unsigned loseTex = loadTextureMap("res/pat.png");
	unsigned winTex = loadTextureMap("res/wario.png");
	unsigned drug = loadTextureMap("res/drug.png");
	unsigned edge = loadTextureMap("res/crtedge.png");
	unsigned filter = loadTextureMap("res/crtfilter.png");
	unsigned brick = loadTextureMap("res/brick.png");
	unsigned paddle = loadTextureMap("res/paddle.png");
	unsigned paddle2 = loadTextureMap("res/paddle2.png");
	
	LoseState lose;
	SplashState splash;
	GameState gs;
	MenuState menu;
	Versus versus;
	WinState win;

	win.init(font, winTex);
	lose.init(font, loseTex);
	splash.init(font, drug);
	gs.create(paddle);
	menu.init(font, brick);
	STATE current = ENTER_SPLASH;
	bool running = true;

	while (stepContext() && running)
	{	
		switch (current)
		{
		case ENTER_SPLASH: 
			splash.play();
			PlaySound("res/splash", NULL, SND_ASYNC);
		case SPLASH:
			splash.step();
			splash.draw();
			
			current = splash.next();
			break;

		case ENTER_MENU: menu.play();
			PlaySound("res/life", NULL, SND_ASYNC);
		case MENU:
			menu.step();
			menu.draw();
			
			current = menu.next();
			break;

		case ENTER_GAME: gs.create(paddle);
			PlaySound("res/mouth", NULL, SND_ASYNC);
		case GAME:
			gs.update();
			gs.draw();
			
			current = gs.next();
			break;
		case ENTER_VERSUS: versus.create(paddle2);
			PlaySound("res/stop", NULL, SND_ASYNC);
		case VERSUS:
			versus.update();
			versus.draw();
			
			current = versus.next();
			break;
		case ENTER_VICTORY: win.play();
			PlaySound("res/ding", NULL, SND_ASYNC);
			PlaySound("res/dong", NULL, SND_ASYNC);
		case VICTORY:
			win.step();
			win.draw();
			
			current = win.next();
			break;
		case ENTER_LOSE: lose.play();
			PlaySound("res/fail", NULL, SND_ASYNC);
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

