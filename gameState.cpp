#include "sfwdraw.h"
#include <time.h>
#include <math.h>
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include "score.h"
using namespace sfw;

#include "gameState.h"

double drand(float fMin, float fMax)
{
	srand(time(0));
	double flt = (double)rand() / RAND_MAX;
	return (fMin + flt * (fMax - fMin));
}

void drawPaddle(Paddle paddle)
{
	drawLine(paddle.Xpos - paddle.Xsize / 2, paddle.Ypos + paddle.Ysize / 2, paddle.Xpos + paddle.Xsize / 2, paddle.Ypos + paddle.Ysize / 2, CYAN);
	drawLine(paddle.Xpos - paddle.Xsize / 2, paddle.Ypos - paddle.Ysize / 2, paddle.Xpos + paddle.Xsize / 2, paddle.Ypos - paddle.Ysize / 2, CYAN);
	drawLine(paddle.Xpos - paddle.Xsize / 2, paddle.Ypos + paddle.Ysize / 2, paddle.Xpos - paddle.Xsize / 2, paddle.Ypos - paddle.Ysize / 2, CYAN);
	drawLine(paddle.Xpos + paddle.Xsize / 2, paddle.Ypos + paddle.Ysize / 2, paddle.Xpos + paddle.Xsize / 2, paddle.Ypos - paddle.Ysize / 2, CYAN);
}

Ball createBall()
{
	Ball ball;
	ball.direction.x = float(drand(-1, 1));
	ball.direction.y = float(drand(-1, 1));
	return ball;
}

void updatePaddle(Paddle &player)
{
	if (getKey('A'))
	{
		player.Xpos -= 8;
	}
	else if (getKey('D'))
	{
		player.Xpos += 8;
	}
}

void updateBall(Ball &ball, Paddle &player, int &hit, int &score)
{
	//printf("%f,%f \n", ball.direction.x * ball.speed, ball.direction.y * ball.speed);

	ball.Xpos += (ball.direction.x * ball.speed);
	ball.Ypos += (ball.direction.y * ball.speed);

	if (hit <= 0)
	{
		if (ball.Xpos < 20)
		{
			ball.direction.x = -(ball.direction.x);
		}
		else if (ball.Xpos > 780)
		{
			ball.direction.x = -(ball.direction.x);
		}

		if (ball.Ypos > 580)
		{
			ball.direction.y = -(ball.direction.y);
		}
		else if (ball.Ypos < 20)
		{
			ball.direction.y = -(ball.direction.y);
		}

		if (ball.Ypos <= (player.Ypos + (player.Ysize)) && ball.Xpos >= (player.Xpos - (player.Xsize)) && ball.Xpos <= (player.Xpos + (player.Xsize)))
		{
			ball.direction.y = -(ball.direction.y);
			ball.Ypos = player.Ypos + 50;
			score++;
		}

	}
}



gameState createGameState()
{
	gameState gs;
	gs.ball1 = createBall();
	while (gs.test > 0)
	{
		gs.test -= 1;
		drand(-1, 1);
	}
	gs.font = loadTextureMap("res/fontmap.png", 16, 16);
	return gs;
}

void updateGameState(gameState &gs)
{
	gs.hit--;

	gs.acc += getDeltaTime();

	updatePaddle(gs.player);
	updateBall(gs.ball1, gs.player, gs.hit, gs.score);
}

void drawGameState(gameState gs)
{
	drawString(gs.font, "~BALLIN~", gs.ball1.Xpos, gs.ball1.Ypos, 10 + (cos(-gs.acc) * 20), 10 + (sin(-gs.acc) * 20), -gs.acc * 35, '\0', MAGENTA);
	drawString(gs.font, "Score: ", 50, 50, 15 + (cos(-gs.acc) / 2), 15 + (sin(-gs.acc) / 2), 0, '\0', BLACK);
	drawString(gs.font, "Score: ", 50, 50, 15 + -(cos(-gs.acc) / 2), 15 + -(sin(-gs.acc) / 2), 0, '\0', MAGENTA);
	drawScore(gs.font, gs.score, gs.acc, 150, 50, 15);
	drawCircle(gs.ball1.Xpos, gs.ball1.Ypos, gs.ball1.size, 12, MAGENTA);
	drawPaddle(gs.player);
}




