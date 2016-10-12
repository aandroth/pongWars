#pragma once

#include <string>
using std::string;
#include "Vec2.h"

class Ball
{
private:
	Vec2 pos, vel;
	int radius;
	unsigned int color;
	unsigned texture;

public:
	void setBall_Normal();
	void set_xPos(int);
	void set_yPos(int);
	void setPos(Vec2);
	int get_xPos() const;
	Vec2 getPos() const;

	void set_xVel(int);
	void set_yVel(int);
	void Ball::setVel(Vec2 newVel);
	int get_xVel() const;
	int get_yVel() const;
	Vec2 getVel();

	void set_radius(int);
	int get_radius() const;

	void set_color(unsigned int);
	int get_color() const;

	unsigned int get_texture();
};

void Ball::setBall_Normal()
{
	pos.x = 100;
	pos.y = 50;
	vel.x = 0;
	vel.y = 38;
	radius = 20;
	color = BLACK;
	texture = sfw::loadTextureMap("./Images/Ball.png");
}

void Ball::set_xPos(int newX)
{
	pos.x = newX;
}
void Ball::set_yPos(int newY)
{
	pos.y = newY;
}
void Ball::setPos(Vec2 newPos)
{
	pos = newPos;
}
int Ball::get_xPos() const
{
	return pos.x;
}
Vec2 Ball::getPos() const
{
	return pos;
}

void Ball::set_xVel(int newX)
{
	if (newX == 0)
	{
		vel.x = 4;
	}
	else
	{
		if (abs(newX) > 20)
		{
			newX = 20 * (newX / abs(newX));
		}
		else if (abs(newX) < 4)
		{
			newX = 4 * (newX / abs(newX));
		}
		vel.x = newX;
	}
}
void Ball::set_yVel(int newY)
{
	if (newY == 0)
	{
		vel.y = 0;
	}
	else
	{
		if (abs(newY) > 20)
		{
			newY = 20 * (newY / abs(newY));
		}
		vel.y = newY;
	}
}
void Ball::setVel(Vec2 newVel)
{
	if (newVel.x == 0)
	{
		vel.x = 0;
	}
	else
	{
		if (abs(newVel.x) > 20)
		{
			newVel.x = 20 * (newVel.x / abs(newVel.x));
		}
		vel.x = newVel.x;
	}

	if (newVel.y == 0)
	{
		vel.y = 0;
	}
	else
	{
		if (abs(newVel.y) > 20)
		{
			newVel.y = 20 * (newVel.y / abs(newVel.y));
		}
		vel.y = newVel.y;
	}
}



int Ball::get_xVel() const
{
	return vel.x;
}
int Ball::get_yVel() const
{
	return vel.y;
}
Vec2 Ball::getVel()
{
	return vel;
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