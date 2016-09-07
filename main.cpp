
#include "sfwdraw.h"
#include <time.h>
#include <math.h>
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

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
	float Ysize = 30;
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
	ball.direction.x = drand(-1,1);
	ball.direction.y = drand(-1,1);
	return ball;
}

void updateBall(Ball &ball)
{
	printf("%f,%f \n", ball.direction.x * ball.speed, ball.direction.y * ball.speed);

	ball.Xpos += (ball.direction.x * ball.speed);
	ball.Ypos += (ball.direction.y * ball.speed);
	
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
}

void main()
{
	srand(time(0));

	int test = 1000;

	while (test > 0)
	{
		test -= 1;
		drand(-1, 1);
	}
	Paddle player;
	Ball ball1 = createBall();
	
	initContext(800,600,"NSFW Draw");

	unsigned f = loadTextureMap("./res/tonc_font.png", 16, 6);
	unsigned d = loadTextureMap("./res/fontmap.png",16,16);
	unsigned r = loadTextureMap("./res/background.jpg");
	unsigned u = loadTextureMap("./res/crosshair.png");

	float acc = 0;
	char c = '\0';

	setBackgroundColor(WHITE);

	while (stepContext())
	{	
		if (getKey('A'))
		{
			player.Xpos -= 8;
		}
		else if (getKey('D'))
		{
			player.Xpos += 8;
		}

		if (getKey('S'))
		{
			player.Ypos -= 8;
		}
		else if (getKey('W'))
		{
			player.Ypos += 8;
		}


		//drawString(f, " !\"#$%&'()*+,./-\n0123456789:;<=>?\n@ABCDEFGHIJKLMNO\nPQRSTUVWXYZ[\\]^_\n`abcdefghijklmno\npqrstuvwxyz{|}~", 0, 600, 48, 48, 0, ' ');
		//drawTexture(r, 0, 600, 800, 600, 0, false,0, 0x88888888);

		acc += getDeltaTime();
		drawString(d, "~BALLIN~", ball1.Xpos, ball1.Ypos, 10 + (cos(-acc) * 20), 10 + (sin(-acc) * 20), -acc*35,'\0',MAGENTA);

		

	/*	drawString(d, "6", 400, 32, 24, 24);
		drawString(d, "12", 400, 600 - 32, 24, 24);
		drawString(d, "3", 800-32, 300, 24, 24);
		drawString(d, "9", 32, 300, 24, 24);
*/
		
		updateBall(ball1);


		drawCircle(ball1.Xpos, ball1.Ypos, ball1.size, 12, MAGENTA);
		drawPaddle(player);
		if(getMouseButton(MOUSE_BUTTON_RIGHT))
			drawTexture(u, getMouseX(), getMouseY(), getTextureWidth(u)/2.5, getTextureHeight(u)/2.5,45,true,0,0x88ffffff);
		else drawTexture(u, getMouseX(), getMouseY(), getTextureWidth(u)/2, getTextureHeight(u)/2);
	}

	termContext();
}

