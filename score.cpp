#include "sfwdraw.h"
#include <time.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "score.h"
using namespace sfw;

void drawScore(unsigned font, int score, float acc)
{
	char buffer[64] = { 0 };
	sprintf_s(buffer, "%d", score);
	drawString(font, buffer, 150, 50, 15 + (cos(-acc) * 2), 15 + (sin(-acc) * 2), 0, '\0', BLACK);
	drawString(font, buffer, 150, 50, 15 + -(cos(-acc) * 2), 15 + -(sin(-acc) * 2), 0, '\0', MAGENTA);

}

void drawWin(unsigned font)
{
}

void drawLose(unsigned font)
{
}
