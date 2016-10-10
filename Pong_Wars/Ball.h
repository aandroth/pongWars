#pragma once

#include <string>
using std::string;

class Ball
{
private:
	int xPos, yPos, xVel, yVel, radius;
	unsigned int color;
	unsigned texture;

public:
	void setBall_Normal();
	void set_xPos(int);
	void set_yPos(int);
	int get_xPos() const;
	int get_yPos() const;

	void set_xVel(int);
	void set_yVel(int);
	int get_xVel() const;
	int get_yVel() const;

	void set_radius(int);
	int get_radius() const;

	void set_color(unsigned int);
	int get_color() const;

	unsigned int get_texture();
};

void Ball::setBall_Normal()
{
	xPos = 100;
	yPos = 50;
	xVel = 0;
	yVel = 38;
	radius = 20;
	color = BLACK;
	texture = sfw::loadTextureMap("./Images/Ball.png");
}

void Ball::set_xPos(int newX)
{
	xPos = newX;
}
void Ball::set_yPos(int newY)
{
	yPos = newY;
}
int Ball::get_xPos() const
{
	return xPos;
}
int Ball::get_yPos() const
{
	return yPos;
}

void Ball::set_xVel(int newX)
{
	if (newX == 0)
	{
		xVel = 4;
	}
	else
	{
		if (abs(newX) > 10)
		{
			newX = 10 * (newX / abs(newX));
		}
		else if (abs(newX) < 4)
		{
			newX = 4 * (newX / abs(newX));
		}
		xVel = newX;
	}
}
void Ball::set_yVel(int newY)
{
	if (newY == 0)
	{
		yVel = 0;
	}
	else
	{
		if (abs(newY) > 10)
		{
			newY = 10 * (newY / abs(newY));
		}
		//else if (abs(newY) < 4)
		//{
		//	newY = 4 * (newY / abs(newY));
		//}
		yVel = newY;
	}
}
int Ball::get_xVel() const
{
	return xVel;
}
int Ball::get_yVel() const
{
	return yVel;
}

void Ball::set_radius(int newR)
{
	radius = newR;
}
int Ball::get_radius() const
{
	return radius;
}

void Ball::set_color(unsigned int newC)
{
	color = newC;
}
int Ball::get_color() const
{
	return color;
}

unsigned int Ball::get_texture()
{
	return texture;
}