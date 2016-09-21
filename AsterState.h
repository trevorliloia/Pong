#pragma once

#include "sfwdraw.h"
#include "score.h"
#include "statesconst.h"

using namespace sfw;


class AsterState
{

	struct vec2
	{
		float x;
		float y;
	};

	struct Ship
	{
		float rotation = 0;
		vec2 direction;
		float speed = 500;
		float accel = 0;
		float Xpos = 400;
		float Ypos = 300;
		float Xsize = 30;
		float Ysize = 30;
		float powerCore = 1;
		int health = 100;
		int hitTImer = 20;
		bool blast = false;
		float blastTimer = 20;
		vec2 bullet[160];
	};

	struct Rock
	{
		float Xpos;
		float Ypos;
		float size = 50;
		float speed = 500;
		vec2 direction;
		float damage = 2;
	};

	struct MiniRock
	{
		float Xpos;
		float Ypos;
		float size = 25;
		float speed = 500;
		vec2 direction;
		float damage = 1;
	};

	struct Walls
	{
		float leftWall;
		float rightWall;
		float topWall;
	};


	unsigned ship;
	unsigned rock;
	unsigned mini;
	int hit = 10;
	int test = 100;
	int score = 0;
	int wallhealth = 20;
	Ship player;
	Rock rocks[80];
	MiniRock minirocks[80];
	int font;
	int stretch = 0;
	int keyTime = 50;
	bool playing = true;
	bool lost = false;
	bool won = false;
	float acc = 0;
	char c = '\0';
public:
	double drand(float fMin, float fMax);
	void drawShip(Ship player) const;
	void createRock(Rock rocks);
	void updateShip(Ship &player);
	void updateRock(Rock rocks, MiniRock minirocks, Ship &player, int &hit, int &score);


	void create(unsigned ship, unsigned rock, unsigned mini);
	void update();
	void draw() const;

	STATE next();
};
