#include "sfwdraw.h"
#include <time.h>
#include <math.h>
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include "score.h"
using namespace sfw;

#include "gameState.h"

double GameState::drand(float fMin, float fMax)
{
	srand(time(0));
	double flt = (double)rand() / RAND_MAX;
	return (fMin + flt * (fMax - fMin));
}

void GameState::drawPaddle(Paddle paddle) const
{
	drawLine(paddle.Xpos - paddle.Xsize / 2, paddle.Ypos + paddle.Ysize / 2, paddle.Xpos + paddle.Xsize / 2, paddle.Ypos + paddle.Ysize / 2, CYAN);
	drawLine(paddle.Xpos - paddle.Xsize / 2, paddle.Ypos - paddle.Ysize / 2, paddle.Xpos + paddle.Xsize / 2, paddle.Ypos - paddle.Ysize / 2, CYAN);
	drawLine(paddle.Xpos - paddle.Xsize / 2, paddle.Ypos + paddle.Ysize / 2, paddle.Xpos - paddle.Xsize / 2, paddle.Ypos - paddle.Ysize / 2, CYAN);
	drawLine(paddle.Xpos + paddle.Xsize / 2, paddle.Ypos + paddle.Ysize / 2, paddle.Xpos + paddle.Xsize / 2, paddle.Ypos - paddle.Ysize / 2, CYAN);
}

void GameState::createBall(Ball &ball)
{
	ball.direction.x = float(drand(-1, 1));
	ball.direction.y = float(drand(-1, 1));
}

void GameState::updatePaddle(Paddle &player)
{
	if (getKey('A'))
	{
		player.Xpos -= 8;
	}
	else if (getKey('D'))
	{
		player.Xpos += 8;
	}

	if (player.Xpos > 800)
	{
		player.Xpos = 0;
	}
	else if (player.Xpos < 0)
	{
		player.Xpos = 800;
	}
}

void GameState::updateBall(Ball &ball, Paddle &player, int &hit, int &score)
{
	//printf("%f,%f \n", ball.direction.x * ball.speed, ball.direction.y * ball.speed);

	//frame locked:
		// we are updating without respect to the actual passage of time
	ball.Xpos += (ball.direction.x * ball.speed) * sfw::getDeltaTime();
	ball.Ypos += (ball.direction.y * ball.speed) * sfw::getDeltaTime();

	
		if (ball.Xpos < 20)
		{
			ball.direction.x = -(ball.direction.x);			
			ball.direction.y = drand(ball.direction.y - 1, ball.direction.y + 1);
			ball.Xpos = 21;
		}
		else if (ball.Xpos > 780)
		{
			ball.direction.x = -(ball.direction.x);
			ball.direction.y = drand(ball.direction.y - .1, ball.direction.y + .1);
			ball.Xpos = 779;
		}

		if (ball.Ypos > 580)
		{
			ball.direction.y = -(ball.direction.y);
			ball.direction.x = drand(ball.direction.x - .1, ball.direction.x + .1);
			wallhealth--;
			ball.Ypos = 579;
		}

		if (ball.Ypos <= (player.Ypos + (player.Ysize)) && ball.Xpos >= (player.Xpos - (player.Xsize/1.5)) && ball.Xpos <= (player.Xpos + (player.Xsize/1.5)))
		{
			ball.direction.y = -(ball.direction.y);
			ball.direction.x = drand(ball.direction.x - .1, ball.direction.x + .1);
			ball.Ypos = player.Ypos + 55;
			score++;
			ball.speed = 500 + (score * 15);
			
		}

}

void GameState::create() 
{
	createBall(ball1);
	while (test > 0)
	{
		test -= 1;
		drand(-1, 1);
	}
	font = loadTextureMap("res/fontmap.png", 16, 16);
}

void GameState::update() 
{
	hit--;
	if (player.powerCore < 100)
	{
		player.powerCore += (sfw::getDeltaTime() * 5);
	}
	acc += getDeltaTime();

	updatePaddle(player);
	updateBall(ball1, player, hit, score);

}

void GameState::draw() const
{
	drawString(font, "~BALLIN~", ball1.Xpos + -(cos(-acc) * 2), ball1.Ypos + -(sin(-acc) * 2), 10 + (cos(-acc) * 20), 10 + (sin(-acc) * 20), -acc * 35, '\0', BLUE);
	drawString(font, "~BALLIN~", ball1.Xpos + (cos(-acc) * 2), ball1.Ypos + (sin(-acc) * 2), 10 + (cos(-acc) * 20), 10 + (sin(-acc) * 20), -acc * 35, '\0', MAGENTA);
	drawScore(font, wallhealth, acc, 150, 500, 20);
	drawString(font, "Score: ", 50, 50, 15 + (cos(-acc) / 2), 15 + (sin(-acc) / 2), 0, '\0', BLACK);
	drawString(font, "Score: ", 50, 50, 15 + -(cos(-acc) / 2), 15 + -(sin(-acc) / 2), 0, '\0', MAGENTA);
	drawScore(font, score, acc, 150, 50, 15);
	drawCircle(ball1.Xpos + -(cos(-acc) * 2), ball1.Ypos + -(sin(-acc) * 2), ball1.size, 12, BLUE);
	drawCircle(ball1.Xpos + (cos(-acc) * 2), ball1.Ypos + (sin(-acc) * 2), ball1.size, 12, MAGENTA);
	drawPaddle(player);

	for (int i = 0; i < player.powerCore; i++)
	{
		drawLine(550 + i, 60, 550 + i, 40, CYAN);
	}	
	drawString(font, "Power", 540, 50, 15 + -(cos(-acc) / 2), 15 + -(sin(-acc) / 2), 0, '\0', BLACK);
}




