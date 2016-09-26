#include "sfwdraw.h"
#include "GameState.h"

//#include "Splash.h"

#include "Splash.h"
#include "Menu.h"
#include "GameOver.h"
#include "Credits.h"
#include <iostream>

bool gameIsActive = true;

int usesRemaining(float manaPool, float costPerCast)
{
	return floor(manaPool / costPerCast);
}

int main()
{
	// Create the window
	sfw::initContext(800, 600, "NSFW Draw");

	//Create the GameState
	GameState activeGame;

	unsigned font = sfw::loadTextureMap("./res/tonc_font.png", 16, 6);
	unsigned background = sfw::loadTextureMap("./Images/Background.png", 1, 1);
	
	//int linex1 = 50, linex2 = 200, liney1 = 280, liney2 = 180;
	//int circlex = 200, circley = 200, circleradius = 50;

	//float a = (linex2 - linex1)*(linex2 - linex1) + (liney2 - liney1)*(liney2 - liney1);
	//float b = 2*(linex2 - linex1)*(linex1 - circlex) + 2 * (liney2 - liney1)*(liney1 - circley);
	//float c = (linex1 - circlex)*(linex1 - circlex) + (liney1 - circley)*(liney1 - circley) - (circleradius*circleradius);
	//float t1 = (-b + sqrt(b*b - 4 * a*c)) / (2 * a);
	//float t2 = (-b - sqrt(b*b - 4 * a*c)) / (2 * a);



	//APP_STATE state = ENTER_SPLASH;
	//Splash splash;
	//splash.init(font);
	APP_STATE state = GAMEPLAY;
	Splash splash;
	splash.init(font);
	Menu menu;
	GameOver gameOver;
	CreditsScreen credits;

	// Start the GameState loop
	while (gameIsActive && sfw::stepContext())
	{
		switch (state)
		{
		case MENU:
			menu.step();
			menu.draw();
			if (menu.next() == STAY){}
			else if (menu.next() == PLAY) { state = ENTER_SPLASH; }
			else if (menu.next() == CREDITS) { credits.init(); state = SHOW_CREDITS; }
			else { return 0; }
			break;
		case SHOW_CREDITS:
			credits.draw();
			credits.step();
			if (credits.next()) {}
			else { menu.init(); state = MENU; }
			break;
		case ENTER_SPLASH:
			splash.play();
			state = SPLASH;
		case SPLASH:
			splash.step();
			splash.draw();
			state = splash.next(state);
			break;
		case ENTER_GAMEPLAY:
			activeGame.update();
			activeGame.draw();
			break;
		case GAMEPLAY:
			activeGame.update();
			activeGame.draw();
			if (activeGame.gameplayIsActive()) {}
			else { state = GAMEOVER; }
			break;
		case GAMEOVER:
			gameOver.step();
			gameOver.draw();
			if (gameOver.next()) {}
			else { state = EXIT; }
			break;
		case EXIT:
			return 0;
		}
	}
	
	sfw::termContext();
	return 0;
}
