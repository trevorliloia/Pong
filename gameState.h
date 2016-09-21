#pragma once

#include "sfwdraw.h"
#include "score.h"
#include "statesconst.h"

using namespace sfw;


class GameState 
{

	struct vec2
	{
		float x;
		float y;
	};

	struct Paddle
	{
		float Xpos = 400;
		float Ypos = 100;
		float Xsize = 100;
		float Ysize = 40;
		float powerCore = 1;
		bool stretch;
		bool blast = false;
		float blastTimer = 20;

	};

	struct Ball
	{
		float Xpos = 400;
		float Ypos = 300;
		float size = 30;
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


	unsigned paddle;
	int hit = 10;
	int test = 100;
	int score = 0;
	int wallhealth = 20;
	Paddle player;
	Ball ball1;
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
	void drawPaddle(Paddle paddle) const;
	void createBall(Ball &ball);
	void updatePaddle(Paddle &player);
	void updateBall(Ball &ball, Paddle &player, int &hit, int &score);


	void create(unsigned paddle);
	void update();
	void draw() const;

	STATE next();
};
