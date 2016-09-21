#pragma once

#include "constded.h"
#include <time.h>
#include "sfwdraw.h"

class Menu
{
	MENU_STATE state = STAY;
	int splashFont;
	float currentTime;

	unsigned credits_button = sfw::loadTextureMap("./Images/CREDITS_Button.png");
	unsigned play_button = sfw::loadTextureMap("./Images/PLAY_Button.png");
	unsigned exit_button = sfw::loadTextureMap("./Images/EXIT_Button.png");
	unsigned mouse = sfw::loadTextureMap("./Images/PLAY_Button.png", 10, 10);

	void buttonPressed_Credits();
	void buttonPressed_Play();
	void buttonPressed_Exit();

public:
	void init();
	void play();
	void draw();
	void step();
	MENU_STATE next();
};

void Menu::buttonPressed_Credits()
{
	state = CREDITS;
}

void Menu::buttonPressed_Play()
{
	state = PLAY;
}

void Menu::buttonPressed_Exit()
{
	state = EXIT_MENU;
}

void Menu::init()
{
	state = STAY;
}

void Menu::play()
{
	currentTime = 2.f;
}

void Menu::draw()
{
	sfw::drawTexture(credits_button, 250 + 100, 500 + 50, 200, 100);
	sfw::drawTexture(play_button, 250+100, 350+50, 200, 100);
	sfw::drawTexture(exit_button, 250+100, 100+50, 200, 100);
	sfw::drawTexture(exit_button, sfw::getMouseX(), sfw::getMouseY(), 10, 10);
}
void Menu::step()
{
	if (sfw::getMouseButton(0) &&
		(sfw::getMouseX() > 250 && sfw::getMouseX() < 450) &&
		(sfw::getMouseY() > 350 && sfw::getMouseY() < 450))
	{
		buttonPressed_Play();
	}
	else if (sfw::getMouseButton(0) &&
		(sfw::getMouseX() > 250 && sfw::getMouseX() < 450) &&
		(sfw::getMouseY() > 100 && sfw::getMouseY() < 200))
	{
		buttonPressed_Exit();
	}
	else if (sfw::getMouseButton(0) &&
		(sfw::getMouseX() > 250 && sfw::getMouseX() < 450) &&
		(sfw::getMouseY() > 500 && sfw::getMouseY() < 600))
	{
		buttonPressed_Credits();
	}
}

MENU_STATE Menu::next()
{
	return state;
}
#pragma once
