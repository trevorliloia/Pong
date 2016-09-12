
#include "sfwdraw.h"
#include <time.h>
#include <math.h>
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include "score.h"
#include "gameState.h"
using namespace sfw;

void main()
{
	initContext(800, 600, "NSFW Draw");
	setBackgroundColor(WHITE);

	gameState gs = createGameState();

	while (stepContext())
	{	
		updateGameState(gs);
		drawGameState(gs);
	}
	
	termContext();
}

