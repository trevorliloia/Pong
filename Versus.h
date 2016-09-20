#pragma once

#include "sfwdraw.h"
#include "score.h"
#include "statesconst.h"

using namespace sfw;


class Versus
{

	struct vec2
	{
		float x;
		float y;
	};

	struct Paddle1
	{
		float Xpos;
		float Ypos = 100;
		float Xsize = 40;
		float Ysize = 100;
		float powerCore = 1;
		bool stretch;
		bool blast = false;
		float blastTimer = 20;

	};

	struct Paddle2 
	{
		float Xpos2 = 400;
		float Ypos2 = 100;
		float Xsize2 = 100;
		float Ysize2 = 40;
		float powerCore2 = 1;
		bool stretch2;
		bool blast2 = false;
		float blastTimer2 = 20;

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

	int hit = 10;
	int test = 100;
	int score1 = 0;
	int score2 = 0;
	int wallhealth = 20;
	Paddle1 player1;
	Paddle1 player2;
	Ball ball1;
	int font;
	int keyTime = 50;
	bool playing = true;
	bool lost = false;
	bool won = false;
	float acc = 0;
	char c = '\0';
public:
	double drand(float fMin, float fMax);
	void drawPaddle(Paddle1 paddle) const;
	void createBall(Ball &ball);
	void updatePaddle(Paddle1 &player1, Paddle1 &player2);
	void updateBall(Ball &ball, Paddle1 &player1, Paddle1 &player2, int &hit, int &score1, int &score2);
	void createPaddle(Paddle1 &player, float Xpos);

	void create();
	void update();
	void draw() const;

	STATE next();
};
