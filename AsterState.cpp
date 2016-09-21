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
	drawTexture(ship, player.Xpos, player.Ypos, sfw::getTextureWidth(ship), sfw::getTextureHeight(ship), player.rotation, false);
	for (int i = 0; i < shots.listSize; ++i)
	{
		drawTexture(shot, shots.listItems[i].Xpos, shots.listItems[i].Ypos, getTextureWidth(shot), getTextureWidth(shot), shots.listItems[i].rotation, false);
	}
}

void AsterState::createRock(Rock &rocks)
{
	rocks.Xpos = 400 + float(drand(-350, 350));
	rocks.Ypos = 300 + float(drand(-250, 250));
	rocks.direction.x = float(drand(-1, 1));
	rocks.direction.y = float(drand(0, 1));
}

void AsterState::updateShip(Ship & player)
{
	if (playing)
	{
		if (getKey('A'))
		{
			player.rotation += 4;
			player.Xpos -= (float)(cos((player.rotation + 90) * PI / 180));
			player.Ypos -= (float)(sin((player.rotation + 90) * PI / 180));
		}
		else if (getKey('D'))
		{
			player.rotation -= 4;
			player.Xpos += (float)cos((player.rotation + 90) * PI / 180);
			player.Ypos += (float)sin((player.rotation + 90) * PI / 180);
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
		player.direction.x = (float)cos((player.rotation + 90) * PI / 180);
		player.direction.y = (float)sin((player.rotation + 90) * PI / 180);
		if (getKey('W'))
		{
			player.speed += 20;
		}
		if (getKey('S'))
		{
			player.speed -= 20;
		}

		player.Xpos += (player.direction.x * player.speed) * sfw::getDeltaTime();
		player.Ypos += (player.direction.y * player.speed) * sfw::getDeltaTime();
		
		if (player.speed != 0)
		{
			player.speed -= (player.speed / 100);
		}
		else if (player.speed < -200)
		{
			player.speed = -200;
		}
		else if (player.speed > 200)
		{
			player.speed = 200;
		}
		else
		{
			player.speed--;
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

		if (getKey(' ') && keyTime >= 20)
		{
			keyTime = 0;
			createBullet(shots, shots.listSize, player);
			shots.listSize++;
		}

		for (int i = 0; i < shots.listSize; ++i)
		{
			shots.listItems[i].Xpos += (shots.listItems[i].direction.x * shots.listItems[i].speed) * sfw::getDeltaTime();
			shots.listItems[i].Ypos += (shots.listItems[i].direction.y * shots.listItems[i].speed) * sfw::getDeltaTime();
		}
		
	}

	if (getKey('P') && keyTime >= 50)
	{
		keyTime = 0;
		playing = !playing;
	}
	keyTime++;
}

void AsterState::updateRock(Rock &rocks, MiniRock &minirocks, Ship & player, int & hit, int & score)
{
	if (playing)
	{
		rocks.Xpos += (rocks.direction.x * rocks.speed);
		rocks.Ypos += (rocks.direction.y * rocks.speed);


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

void AsterState::createBullet(List & shots, int i, Ship player)
{
	shots.listItems[i].Xpos = player.Xpos;
	shots.listItems[i].Ypos = player.Ypos;
	shots.listItems[i].rotation = player.rotation;
	shots.listItems[i].direction.x = (float)cos((player.rotation + 90) * PI / 180);
	shots.listItems[i].direction.y = (float)sin((player.rotation + 90) * PI / 180);
}

void AsterState::create(unsigned &shipT, unsigned &shotT, unsigned &rockT, unsigned &miniT)
{
	ship = shipT;
	shot = shotT;
	rock = rockT;
	mini = miniT;
	player.direction.x = float(drand(-1, 1));
	player.direction.y = float(drand(0, 1));
	for (int i = 0; i < 10; ++i)
	{
		srand(drand(-20, 20));
		createRock(rocks[i]);
	}
}

void AsterState::update()
{
	updateShip(player);
	for (int i = 0; i < 10; ++i)
	{
		updateRock(rocks[i], minirocks[i], player, hit, score);
	}
	
}

void AsterState::draw() const
{
	drawShip(player);
	for (int i = 0; i < 10; ++i)
	{
		drawTexture(rock, rocks[i].Xpos, rocks[i].Ypos, getTextureWidth(rock), getTextureHeight(rock), 0.f, false);
	}
}

STATE AsterState::next()
{
	return STATE();
}
