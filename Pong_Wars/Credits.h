#pragma once

#include "constded.h"
#include <time.h>
#include "sfwdraw.h"

class CreditsScreen
{
	bool stayOnScreen = true;
	int splashFont;

	unsigned back_button = sfw::loadTextureMap("./Images/BACK_Button.png");
	unsigned mouse = sfw::loadTextureMap("./Images/PLAY_Button.png", 5, 5);
	unsigned font = sfw::loadTextureMap("./res/tonc_font.png", 16, 6);

	void buttonPressed_Back();

public:
	void init();
	void draw();
	void step();
	bool next();
};

void CreditsScreen::buttonPressed_Back()
{
	stayOnScreen = false;
}

void CreditsScreen::init()
{
	stayOnScreen = true;
	splashFont = font;
}

void CreditsScreen::draw()
{
	sfw::drawString(font, "Programming and art:\n Aaron Andrews", 100, 550, 30, 30, 0, ' ');
	sfw::drawTexture(back_button, 50 + 100, 350 + 50, 200, 100);
	sfw::drawTexture(back_button, sfw::getMouseX(), sfw::getMouseY(), 10, 10);
}

void CreditsScreen::step()
{
	if (sfw::getMouseButton(0) &&
		(sfw::getMouseX() > 50 && sfw::getMouseX() < 450) &&
		(sfw::getMouseY() > 350 && sfw::getMouseY() < 450))
	{
		buttonPressed_Back();
	}
}

bool CreditsScreen::next()
{
	return stayOnScreen;
}
#pragma once
