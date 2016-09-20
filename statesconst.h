#pragma once


enum STATE
{
	ENTER_SPLASH, SPLASH,
	ENTER_MENU, MENU,
	ENTER_VERSUS, VERSUS,
	ENTER_GAME, GAME,
	ENTER_LOSE, LOSE,
	ENTER_VICTORY, VICTORY,
	ENTER_QUIT, QUIT
};


/*
	Each State should/could have the following:
		init -> First created.
		play -> On transition.
		step -> On the game loop.
		draw -> On the game loop.
		next -> returns the state we are transitioning to.
*/