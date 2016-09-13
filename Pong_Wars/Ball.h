#pragma once

#include <string>
using std::string;

class Ball
{
private:
	int xPos, yPos, xVel, yVel, radius;
	unsigned int color;

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
	xVel = newX;
}
void Ball::set_yVel(int newY)
{
	yVel = newY;
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