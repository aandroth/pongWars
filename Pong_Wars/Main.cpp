#include "sfwdraw.h"
#include "GameState.h"
#include "Splash.h"


bool gameIsActive = true;



int usesRemaining(float manaPool, float costPerCast)
{
	return floor(manaPool / costPerCast);
}

void main()
{
	// Create the window
	sfw::initContext(800, 600, "NSFW Draw");

	//Create the GameState
	GameState activeGame;

	unsigned font = sfw::loadTextureMap("./res/tonc_font.png", 16, 6);
	unsigned background = sfw::loadTextureMap("./Images/Background.png", 1, 1);
	APP_STATE state = ENTER_SPLASH;
	Splash splash;
	splash.init(font);

	printf("%d", usesRemaining(6.2, 1.9));
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
