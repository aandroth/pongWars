#pragma once

#include "constded.h"
#include <time.h>
#include "sfwdraw.h"

class Splash
{
	int splashFont;
	float currentTime;
public:
	void init(unsigned font);
	void play();
	void draw();
	void step();
	APP_STATE next(APP_STATE);
};


void Splash::init(unsigned font)
{
	splashFont = font;
	currentTime = 3.f;
}

void Splash::play()
{
	currentTime = 2.f;
}

void Splash::draw()
{
	sfw::drawString(splashFont, "GET READY TO PONG!!!!!!!!", 0, 600, 35, 35, 0, ' ');
	sfw::drawLine(0, 300, 500 * (currentTime / 3), 300, 0xffffff);
}
void Splash::step()
{
	currentTime -= sfw::getDeltaTime();
}

APP_STATE Splash::next(APP_STATE state)
{
	if (currentTime <= 0)
	{
		return GAMEPLAY;
	}
	else
	{
		return state;
	}
}
#pragma once
