
#include "sfwdraw.h"
#include <time.h>
#include <math.h>
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include "score.h"
#include "gameState.h"
using namespace sfw;

struct vec2
{
	float x;
	float y;
};

struct Paddle 
{
	float Xpos = 400;
	float Xsize = 100;
	float Ypos = 100;
	float Ysize = 40;
	float powerCore = 0;
	bool stretch;
	bool blast;
	float stretchSize;
	float blastPower;
	
};

struct Ball
{
	float Xpos = 400;
	float Ypos = 300;
	float size = 30;
	float speed = 10;
	vec2 direction;
	float damage = 1;
};

struct Walls
{
	float leftWall;
	float rightWall;
	float topWall;
};

double drand(float fMin, float fMax)
{
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
	ball.direction.x = drand(-1.1,1.1);
	ball.direction.y = drand(-1.1,1.1);
	return ball;
}

void updatePaddle(Paddle player)
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

void updateBall(Ball &ball, Paddle &player,int &hit, int &score)
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
				score++;
				hit = 50;
		}

	}
}

void main()
{
	initContext(800, 600, "NSFW Draw");
	setBackgroundColor(WHITE);

	gameState gs = createGameState();

	while (stepContext())
	{	
		updateGameState(gs);
		drawGameState(gs);
	}
	
	termContext();
}

