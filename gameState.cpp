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
	drawLine(paddle.Xpos - paddle.Xsize / 2, paddle.Ypos + paddle.Ysize / 2, paddle.Xpos + paddle.Xsize / 2, paddle.Ypos + paddle.Ysize / 2, BLACK);
	drawLine(paddle.Xpos - paddle.Xsize / 2, paddle.Ypos - paddle.Ysize / 2, paddle.Xpos + paddle.Xsize / 2, paddle.Ypos - paddle.Ysize / 2, BLACK);
	for (int i = 0; i < 40; ++i)
	{
		drawLine(paddle.Xpos - paddle.Xsize / 2, (paddle.Ypos + paddle.Ysize / 2) - i, paddle.Xpos + paddle.Xsize / 2, (paddle.Ypos + paddle.Ysize / 2) - i, BLACK);
	}
	drawLine(paddle.Xpos - paddle.Xsize / 2, paddle.Ypos + paddle.Ysize / 2, paddle.Xpos - paddle.Xsize / 2, paddle.Ypos - paddle.Ysize / 2, BLACK);
	drawLine(paddle.Xpos + paddle.Xsize / 2, paddle.Ypos + paddle.Ysize / 2, paddle.Xpos + paddle.Xsize / 2, paddle.Ypos - paddle.Ysize / 2, BLACK);
}

void GameState::createBall(Ball &ball)
{
	ball.Xpos = 400;
	ball.Ypos = 300;
	ball.direction.x = float(drand(-1, 1));
	ball.direction.y = float(drand(0, 1));
}

void GameState::updatePaddle(Paddle &player)
{
	if (playing)
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


		if (getKey(' ') && player.powerCore > 0)
		{
			--player.powerCore;
			player.Xsize = 150;
			stretch = 50;
		}
		else
		{
			player.Xsize = 100;
			stretch = 0;
		}


		if (getKey('W') && player.powerCore >= 100)
		{
			player.powerCore -= 100;
			player.blast = true;
		}
	}

	if (getKey('P') && keyTime >= 50)
	{
		keyTime = 0;
		playing = !playing;
	}
	keyTime++;
}

void GameState::updateBall(Ball &ball, Paddle &player, int &hit, int &score)
{
	//printf("%f,%f \n", ball.direction.x * ball.speed, ball.direction.y * ball.speed);

	//frame locked:
		// we are updating without respect to the actual passage of time
	if (playing)
	{
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
		if (ball.Ypos <= (player.Ypos + (player.Ysize)) && ball.Ypos >= (player.Ypos - 10) && ball.Xpos >= (player.Xpos - (player.Xsize / 1.5)) && ball.Xpos <= (player.Xpos + (player.Xsize / 1.5)))
		{
			ball.direction.y = -(ball.direction.y);
			ball.direction.x = drand(ball.direction.x - .1, ball.direction.x + .1);
			ball.Ypos = player.Ypos + 55;
			score++;
			ball.speed = 500 + (score * 15);

		}

		if (ball.Ypos < 0 && score >= 5)
		{
			score -= 5;
			ball.Xpos = 400;
			ball.Ypos = 300;
			ball.speed = 500;
			ball.direction.y = .5;
		}
		else if (ball.Ypos < 0 && score < 5)
		{
			lost = true;
		}

	}

	
	
}

void GameState::create(unsigned a_paddle) 
{
	paddle = a_paddle;
	won = false;
	lost = false;
	wallhealth = 20;
	score = 0;
	while (test > 0)
	{
		test -= 1;
		drand(-1, 1);
	}
	createBall(ball1);
	font = loadTextureMap("res/fontmap.png", 16, 16);
}

void GameState::update() 
{
	hit--;
	if (playing)
	{
		if (player.powerCore < 100)
		{
			player.powerCore += (sfw::getDeltaTime() * 5);
		}
		acc += getDeltaTime();
		if (wallhealth <= 0)
		{
			won = true;
		}
	}
	

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
	drawTexture(paddle, player.Xpos - (player.Xsize / 2), player.Ypos + (player.Ysize / 2), getTextureWidth(paddle), getTextureHeight(paddle), 0.f, false);

	for (int i = 0; i < player.powerCore; i++)
	{
		if (player.powerCore < 100)
		{ 
			drawLine(550 + i, 60, 550 + i, 40, CYAN); 
		}
		else
		{
			drawLine(550 + i, 60, 550 + i, 40, RED);
		}
		
	}	
	if (player.blast == true)
	{
		drawLine(0, 35, 800, 35, GREEN);
	}
	drawString(font, "Power", 540, 50, 15 + -(cos(-acc) / 2), 15 + -(sin(-acc) / 2), 0, '\0', BLACK);
}




STATE GameState::next()
{
	if (won)
	{
		return ENTER_VICTORY;
	}
	if (lost)
	{
		return ENTER_LOSE;
	}

	return GAME;
}