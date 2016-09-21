#pragma once

#include "constded.h"
#include <time.h>
#include "sfwdraw.h"

class GameOver
{
	bool stayOnScreen = true;
	int splashFont;

	unsigned exit_button = sfw::loadTextureMap("./Images/EXIT_Button.png");
	unsigned mouse = sfw::loadTextureMap("./Images/PLAY_Button.png", 10, 10);
	unsigned font = sfw::loadTextureMap("./res/tonc_font.png", 16, 6);

	void buttonPressed_Exit();

public:
	void init(unsigned font);
	void draw();
	void step();
	bool next();
};

void GameOver::buttonPressed_Exit()
{
	stayOnScreen = false;
}

void GameOver::init(unsigned font)
{
	splashFont = font;
}

void GameOver::draw()
{
	sfw::drawString(font, "Game Over", 100, 450, 50, 50, 0, ' ');
	sfw::drawTexture(exit_button, 250 + 100, 100 + 50, 200, 100);
	sfw::drawTexture(exit_button, sfw::getMouseX(), sfw::getMouseY(), 10, 10);
}

void GameOver::step()
{
	if (sfw::getMouseButton(0) &&
		(sfw::getMouseX() > 250 && sfw::getMouseX() < 450) &&
		(sfw::getMouseY() > 100 && sfw::getMouseY() < 200))
	{
		buttonPressed_Exit();
	}
}

bool GameOver::next()
{
	return stayOnScreen;
}
#pragma once
