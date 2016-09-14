
#include "sfwdraw.h"
#include <time.h>
#include <math.h>
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include "score.h"
#include "gameState.h"
#include "main.h"
using namespace sfw;

void main()
{
	initContext(800, 600, "Nausous Neons and the Asthmatic Apparition");
	setBackgroundColor(WHITE);
	GameState gs;
	gs.create();

	while (stepContext())
	{	
		gs.update();
		gs.draw();
		//GameState::updateGameState(gs);
		//GameState::drawGameState(gs);
	}

	termContext();
}

