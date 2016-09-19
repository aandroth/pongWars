#pragma once

#include "sfwdraw.h"
#include <string>
using std::string;

class Paddle
{
private:
	int xPos, yPos, yVel, width, height, speed;
	unsigned int color, texture;

public:
	void moveUp(int ceilingValue);
	void moveDown(int floorValue);

	void setPlayerPaddle_Normal();
	void setEnemyPaddle_Normal();

	void set_xPos(int);
	void set_yPos(int);
	int get_xPos() const;
	int get_yPos() const;

	void set_yVel(int);
	int get_yVel() const;

	void set_width(int);
	void set_height(int);
	int get_width() const;
	int get_height() const;


	void set_speed(int);
	int get_speed() const;

	void set_color(unsigned);
	void set_texture(unsigned);
	unsigned get_color() const;
	unsigned get_texture() const;
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
	texture = sfw::loadTextureMap("./Images/Stripes.png", 10, 50);
	xPos = 100;
	yPos = 200;
	width = 10;
	height = 100;
	speed = 8;
}

void Paddle::setEnemyPaddle_Normal()
{
	texture = sfw::loadTextureMap("./Images/Paddle.png", 10, 50);
	xPos = 700;
	yPos = 200;
	width = 10;
	height = 100;
	speed = 8;
}

void Paddle::set_xPos(int newX)
{
	xPos = newX;
}
void Paddle::set_yPos(int newY)
{
	yPos = newY;
}
int Paddle::get_xPos() const
{
	return xPos;
}
int Paddle::get_yPos() const
{
	return yPos;
}

void Paddle::set_yVel(int newY)
{
	yVel = newY;
}
int Paddle::get_yVel() const
{
	return yVel;
}

void Paddle::set_width(int newW)
{
	width = newW;
}
void Paddle::set_height(int newH)
{
	height = newH;
}
int Paddle::get_width() const
{
	return width;
}
int Paddle::get_height() const
{
	return height;
}

void Paddle::set_speed(int newS)
{
	speed = newS;
}
int Paddle::get_speed() const
{
	return speed;
}

void Paddle::set_color(unsigned newC)
{
	color = newC;
}
void Paddle::set_texture(unsigned newT)
{
	texture = newT;
}
unsigned Paddle::get_color() const
{
	return color;
}
unsigned Paddle::get_texture() const
{
	return texture;
}