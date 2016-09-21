#include "AsterState.h"
#include "sfwdraw.h"
#include <time.h>
#include <math.h>
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include "score.h"
using namespace sfw;

double AsterState::drand(float fMin, float fMax)
{
	srand(time(0));
	double flt = (double)rand() / RAND_MAX;
	return (fMin + flt * (fMax - fMin));
}

void AsterState::drawShip(Ship player) const
{

}

void AsterState::createRock(Rock rocks)
{
	rocks.Xpos = 400;
	rocks.Ypos = 300;
	rocks.direction.x = float(drand(-1, 1));
	rocks.direction.y = float(drand(0, 1));
}

void AsterState::updateShip(Ship & player)
{
	if (playing)
	{
		if (getKey('A'))
		{
			player.rotation--;
		}
		else if (getKey('D'))
		{
			player.rotation++;
		}

		if (player.Xpos > 800)
		{
			player.Xpos = 0;
		}
		else if (player.Xpos < 0)
		{
			player.Xpos = 800;
		}
		if (player.Ypos > 600)
		{
			player.Ypos = 0;
		}
		else if (player.Ypos < 0)
		{
			player.Ypos = 600;
		}
		if (getKey('W'))
		{
			player.Xpos += (player.direction.x * player.speed);
			player.Ypos += (player.direction.y * player.speed);
		}

		if (getKey(' ') && player.powerCore > 10)
		{
			player.powerCore -= 10;
			player.blast = true;
			player.blastTimer = 10;
		}
		else
		{
			player.blastTimer--;
		}


		
	}

	if (getKey('P') && keyTime >= 50)
	{
		keyTime = 0;
		playing = !playing;
	}
	keyTime++;
}

void AsterState::updateRock(Rock rocks, MiniRock minirocks, Ship & player, int & hit, int & score)
{
	if (playing)
	{
		rocks.Xpos += (rocks.direction.x * rocks.speed) * sfw::getDeltaTime();
		rocks.Ypos += (rocks.direction.y * rocks.speed) * sfw::getDeltaTime();


		if (rocks.Xpos < 0)
		{
			rocks.Xpos = 799;
		}
		else if (rocks.Xpos > 800)
		{
			rocks.Xpos = 1;
		}
		if (rocks.Ypos > 600)
		{
			rocks.Ypos = 1;
		}
		if (rocks.Ypos < 0)
		{
			rocks.Ypos = 599;
		}


	}
}

void AsterState::create(unsigned shipT, unsigned rockT, unsigned miniT)
{
}

void AsterState::update()
{
}

void AsterState::draw() const
{
}

STATE AsterState::next()
{
	return STATE();
}
