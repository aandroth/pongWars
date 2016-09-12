
#include "sfwdraw.h"
#include "GameState.h"


bool gameIsActive = true;

void main()
{
	// Create the window
	sfw::initContext(800, 600, "NSFW Draw");

	//Create the GameState
	GameState activeGame;

	// Start the GameState loop
	while (gameIsActive && sfw::stepContext())
	{
		activeGame.update();

		activeGame.draw();
	}

	sfw::termContext();
}