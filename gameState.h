#pragma once
#include "sfwdraw.h"
#include <time.h>
#include <math.h>
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include "score.h"
using namespace sfw;

struct gameState
{
	int hit = 10;
	int test = 100;
	int score = 0;
	int wallhealth = 100;
	Paddle player;
	Ball ball1 = createBall();
	int font;
	
	float acc = 0;
	char c = '\0';

};

gameState createGameState()
{
	gameState gs;
	srand(time(0));
	while (gs.test > 0)
	{
		gs.test -= 1;
		drand(-1, 1);
	}
	gs.font = loadTextureMap("res/fontmap.png", 16, 16);
	return gs;
}

gameState updateGameState(gameState gs)
{
	gs.hit--;

	
	gs.acc += getDeltaTime();
	
	updatePaddle(gs.player);
	updateBall(gs.ball1, gs.player, gs.hit, gs.score);

}

gameState drawGameState(gameState gs)
{
	drawString(gs.font, "~BALLIN~", gs.ball1.Xpos, gs.ball1.Ypos, 10 + (cos(-gs.acc) * 20), 10 + (sin(-gs.acc) * 20), -gs.acc * 35, '\0', MAGENTA);
	drawString(gs.font, "Score: ", 50, 50, 15 + (cos(-gs.acc) / 2), 15 + (sin(-gs.acc) / 2), 0, '\0', BLACK);
	drawString(gs.font, "Score: ", 50, 50, 15 + -(cos(-gs.acc) / 2), 15 + -(sin(-gs.acc) / 2), 0, '\0', MAGENTA);
	drawScore(gs.font, gs.score, gs.acc);
	drawCircle(gs.ball1.Xpos, gs.ball1.Ypos, gs.ball1.size, 12, MAGENTA);
	drawPaddle(gs.player);
}