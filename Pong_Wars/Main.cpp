#include "sfwdraw.h"
#include "GameState.h"
#include "Splash.h"
#include <iostream>

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
	
	//int linex1 = 50, linex2 = 200, liney1 = 280, liney2 = 180;
	//int circlex = 200, circley = 200, circleradius = 50;

	//float a = (linex2 - linex1)*(linex2 - linex1) + (liney2 - liney1)*(liney2 - liney1);
	//float b = 2*(linex2 - linex1)*(linex1 - circlex) + 2 * (liney2 - liney1)*(liney1 - circley);
	//float c = (linex1 - circlex)*(linex1 - circlex) + (liney1 - circley)*(liney1 - circley) - (circleradius*circleradius);
	//float t1 = (-b + sqrt(b*b - 4 * a*c)) / (2 * a);
	//float t2 = (-b - sqrt(b*b - 4 * a*c)) / (2 * a);



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

	//// Move Player paddle
	//if (sfw::getKey(KEY_UP))
	//{
	//	++liney2;
	//}
	//else if (sfw::getKey(KEY_DOWN))
	//{
	//	--liney2;
	//}


	//if (sfw::getKey(KEY_LEFT))
	//{
	//	++linex2;
	//}
	//else if (sfw::getKey(KEY_RIGHT))
	//{
	//	--linex2;
	//}

	//a = (linex2 - linex1)*(linex2 - linex1) + (liney2 - liney1)*(liney2 - liney1);
	//b = 2 * (linex2 - linex1)*(linex1 - circlex) + 2 * (liney2 - liney1)*(liney1 - circley);
	//c = (linex1 - circlex)*(linex1 - circlex) + (liney1 - circley)*(liney1 - circley) - (circleradius*circleradius);
	//t1 = (-b + sqrt(b*b - 4 * a*c)) / (2 * a);
	//t2 = (-b - sqrt(b*b - 4 * a*c)) / (2 * a);

	//	sfw::drawCircle(circlex, circley, circleradius, 12, WHITE);
	//	sfw::drawLine(linex1, liney1, linex2, liney2, RED);

	//	
	//	sfw::drawCircle((t2*(linex2 - linex1) + linex1), (t2*(liney2 - liney1) + liney1), 5, 12, YELLOW);
	//	sfw::drawCircle((t1*(linex2 - linex1) + linex1), (t1*(liney2 - liney1) + liney1), 5, 12, YELLOW);

	//	sfw::drawString(font, std::to_string(t1).c_str(), 0, 600, 48, 48, 0, ' ');
	//	sfw::drawString(font, std::to_string(t2).c_str(), 0, 500, 48, 48, 0, ' ');

	//	if ((t1 >= 0 && t1 <= 1) || (t2 >= 0 && t2 <= 1))
	//	{
	//		sfw::drawString(font, "Hit", 0, 400, 48, 48, 0, ' ');
	//	}
	//	else
	//	{
	//		sfw::drawString(font, "Miss", 0, 400, 48, 48, 0, ' ');
	//	}
	}
	


	sfw::termContext();
}
