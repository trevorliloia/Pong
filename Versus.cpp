#include "sfwdraw.h"
#include <time.h>
#include <math.h>
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include "score.h"
using namespace sfw;

#include "Versus.h"

double Versus::drand(float fMin, float fMax)
{
	srand(time(0));
	double flt = (double)rand() / RAND_MAX;
	return (fMin + flt * (fMax - fMin));
}

void Versus::drawPaddle(Paddle1 paddle) const
{
	drawLine(paddle.Xpos - paddle.Xsize / 2, paddle.Ypos + paddle.Ysize / 2, paddle.Xpos + paddle.Xsize / 2, paddle.Ypos + paddle.Ysize / 2, CYAN);
	drawLine(paddle.Xpos - paddle.Xsize / 2, paddle.Ypos - paddle.Ysize / 2, paddle.Xpos + paddle.Xsize / 2, paddle.Ypos - paddle.Ysize / 2, CYAN);
	drawLine(paddle.Xpos - paddle.Xsize / 2, paddle.Ypos + paddle.Ysize / 2, paddle.Xpos - paddle.Xsize / 2, paddle.Ypos - paddle.Ysize / 2, CYAN);
	drawLine(paddle.Xpos + paddle.Xsize / 2, paddle.Ypos + paddle.Ysize / 2, paddle.Xpos + paddle.Xsize / 2, paddle.Ypos - paddle.Ysize / 2, CYAN);

}

void Versus::createBall(Ball & ball)
{
	ball.direction.x = float(drand(-1, 1));
	ball.direction.y = float(drand(0, 1));
}

void Versus::updatePaddle(Paddle1 &player1, Paddle1 &player2)
{
	if (playing)
	{
		if (getKey('W'))
		{
			player1.Ypos += 8;
		}
		else if (getKey('S'))
		{
			player1.Ypos -= 8;
		}

		if (player1.Ypos > 600)
		{
			player1.Ypos = 0;
		}
		else if (player1.Ypos < 0)
		{
			player1.Ypos = 600;
		}


		if (getKey(KEY_UP))
		{
			player2.Ypos += 8;
		}
		else if (getKey(KEY_DOWN))
		{
			player2.Ypos -= 8;
		}

		if (player2.Ypos > 600)
		{
			player2.Ypos = 0;
		}
		else if (player2.Ypos < 0)
		{
			player2.Ypos = 600;
		}

	}

	if (getKey('P') && keyTime >= 50)
	{
		keyTime = 0;
		playing = !playing;
	}
	keyTime++;
}

void Versus::updateBall(Ball & ball, Paddle1 & player1, Paddle1 &player2, int & hit, int & score1, int &score2)
{
	if (playing)
	{
		ball.Xpos += (ball.direction.x * ball.speed) * sfw::getDeltaTime();
		ball.Ypos += (ball.direction.y * ball.speed) * sfw::getDeltaTime();


		if (ball.Xpos < 20)
		{
			score2++;
			ball.speed = 500;
			ball.Xpos = 400;
			ball.Ypos = 300;
		}
		else if (ball.Xpos > 780)
		{
			score1++;
			ball.speed = 500;
			ball.Xpos = 400;
			ball.Ypos = 300;
		}
		if (ball.Ypos > 580)
		{
			ball.direction.y = -(ball.direction.y);
			ball.direction.x = drand(ball.direction.x - .1, ball.direction.x + .1);
			ball.Ypos = 579;
		}
		if (ball.Ypos < 20)
		{
			ball.direction.y = -(ball.direction.y);
			ball.direction.x = drand(ball.direction.x - .1, ball.direction.x + .1);
			ball.Ypos = 21;

		}

		if (ball.Xpos <= (player1.Xpos + 20) && ball.Ypos > (player1.Ypos - 50) && ball.Ypos < (player1.Ypos + 50))
		{
			ball.direction.x = -(ball.direction.x);
			ball.direction.y = drand(ball.direction.y - .1, ball.direction.y + .1);
			ball.Xpos = player1.Xpos + 25;
		}

		if (ball.Xpos >= (player2.Xpos - 20) && ball.Ypos >(player2.Ypos - 50) && ball.Ypos < (player2.Ypos + 50))
		{
			ball.direction.x = -(ball.direction.x);
			ball.direction.y = drand(ball.direction.y - .1, ball.direction.y + .1);
			ball.Xpos = player2.Xpos - 25;
		}

	}
}

void Versus::createPaddle(Paddle1 & player, float Xpos)
{
	player.Xpos = Xpos;
}

void Versus::create()
{
	won = false;
	while (test > 0)
	{
		test -= 1;
		drand(-1, 1);
	}
	createBall(ball1);
	createPaddle(player1, 100);
	createPaddle(player2, 700);
	font = loadTextureMap("res/fontmap.png", 16, 16);
}

void Versus::update()
{
	hit--;
	if (playing)
	{
		acc += getDeltaTime();
		if (score1 >= 12)
		{
			won = true;
		}
		if (score2 >= 12)
		{
			lost = true;
		}
	}


	updatePaddle(player1, player2);
	updateBall(ball1, player1, player2, hit, score1, score2);
}

void Versus::draw() const
{
	drawString(font, "~BALLIN~", ball1.Xpos + -(cos(-acc) * 2), ball1.Ypos + -(sin(-acc) * 2), 10 + (cos(-acc) * 20), 10 + (sin(-acc) * 20), -acc * 35, '\0', BLUE);
	drawString(font, "~BALLIN~", ball1.Xpos + (cos(-acc) * 2), ball1.Ypos + (sin(-acc) * 2), 10 + (cos(-acc) * 20), 10 + (sin(-acc) * 20), -acc * 35, '\0', MAGENTA);
	
	drawString(font, "Score: ", 50, 50, 15 + (cos(-acc) / 2), 15 + (sin(-acc) / 2), 0, '\0', BLACK);
	drawString(font, "Score: ", 50, 50, 15 + -(cos(-acc) / 2), 15 + -(sin(-acc) / 2), 0, '\0', MAGENTA);
	drawScore(font, score1, acc, 150, 50, 15);
	drawScore(font, score2, acc, 650, 50, 15);
	drawCircle(ball1.Xpos + -(cos(-acc) * 2), ball1.Ypos + -(sin(-acc) * 2), ball1.size, 12, BLUE);
	drawCircle(ball1.Xpos + (cos(-acc) * 2), ball1.Ypos + (sin(-acc) * 2), ball1.size, 12, MAGENTA);
	drawPaddle(player1);
	drawPaddle(player2);

}

STATE Versus::next()
{
	if (won)
	{
		return ENTER_SPLASH;
	}
	return VERSUS;
}
