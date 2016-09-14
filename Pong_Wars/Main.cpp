#include "sfwdraw.h"
#include "GameState.h"
#include "Splash.h"


bool gameIsActive = true;

void main()
{
	// Create the window
	sfw::initContext(800, 600, "NSFW Draw");

	//Create the GameState
	GameState activeGame;

	unsigned font = sfw::loadTextureMap("./res/tonc_font.png", 16, 6);

	APP_STATE state = ENTER_SPLASH;
	Splash splash;
	splash.init(font);

	// Start the GameState loop
	while (gameIsActive && sfw::stepContext())
	{
		switch (state)
		{
		case ENTER_SPLASH:
			splash.play();
			state = SPLASH;
		case SPLASH:
			splash.step();
			splash.draw();
			state = splash.next(state);
			break;
		case GAMEPLAY:
			activeGame.update();
			activeGame.draw();
			break;
		case EXIT:
			gameIsActive = false;
			break;
		}

	}

	sfw::termContext();
}