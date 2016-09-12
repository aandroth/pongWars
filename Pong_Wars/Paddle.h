#pragma once

#include "sfwdraw.h"
#include <string>
using std::string;

class Paddle
{
public:
	int xPos, yPos, yVel, width, height, speed;
	unsigned int color, texture;

	void moveUp(int ceilingValue);
	void moveDown(int floorValue);

	void setPlayerPaddle_Normal();
	void setEnenmyPaddle_Normal();
};

void Paddle::moveUp(int ceilingValue)
{
	if (yPos >= ceilingValue)
	{
		yPos = ceilingValue;
		yVel = 0;
	}
	else
	{
		yPos += speed;
		yVel = speed;
	}
}

void Paddle::moveDown(int floorValue)
{
	if (yPos - height <= floorValue)
	{
		yPos = height + floorValue;
		yVel = 0;
	}
	else
	{
		yPos -= speed;
		yVel = -speed;
	}
}

void Paddle::setPlayerPaddle_Normal()
{
	texture = sfw::loadTextureMap("./Images/Paddle.png", 10, 50);
	xPos = 100;
	yPos = 200;
	width = 10;
	height = 100;
	speed = 8;
}

void Paddle::setEnenmyPaddle_Normal()
{
	texture = sfw::loadTextureMap("./Images/Paddle.png", 10, 50);
	xPos = 700;
	yPos = 200;
	width = 10;
	height = 100;
	speed = 8;
}