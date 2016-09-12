#pragma once
#include "sfwdraw.h"
#include <time.h>
#include <math.h>
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include "score.h"
#include "gameState.h"
using namespace sfw;

double drand(float fMin, float fMax);
void drawPaddle(Paddle paddle);
Ball createBall();
void updatePaddle(Paddle player);
void updateBall(Ball &ball, Paddle &player, int &hit, int &score);
gameState createGameState();
gameState updateGameState(gameState gs);
gameState drawGameState(gameState gs);