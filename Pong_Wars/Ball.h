#pragma once

#include <string>
using std::string;

class Ball
{
public:
	int xPos, yPos, xVel, yVel, radius;
	unsigned int color;

	void setBall_Normal();
};

void Ball::setBall_Normal()
{
	xPos = 200;
	yPos = 250;
	xVel = 9;
	yVel = 9;
	radius = 10;
	color = WHITE;
}