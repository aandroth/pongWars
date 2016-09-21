#pragma once

#include "sfwdraw.h"
#include <string>
using std::string;
#include <iostream>
#include <vector>
using std::vector;

struct Vec2
{
	int x, y;
	Vec2(int, int);
};

Vec2::Vec2(int newX, int newY)
{
	x = newX;
	y = newY;
}

class Paddle
{
private:
	int xPos, yPos, yVel, width, height, speed;
	unsigned int color, texture;
	vector<Vec2> pointsVec;

public:
	void moveUp(int ceilingValue);
	void moveDown(int floorValue);

	void setPlayerPaddle_Normal();
	void setEnemyPaddle_Normal();
	void setEnemyPaddle_AngleBracket();

	void drawPaddle();

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

	bool collidedWithBall_Outer(int, int, int);
	int faceOfCollision_Inner(int, int, int);
	int xNormalOfFaceIndex(int index);
	int yNormalOfFaceIndex(int index);
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
		yVel = speed;
		yPos += yVel;
		for (int ii = 0; ii < pointsVec.size(); ++ii)
		{
			pointsVec[ii].y += yVel;
		}
	}
	std::cout << yVel << std::endl;
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
		yVel = -speed;
		yPos += yVel;
		for (int ii = 0; ii < pointsVec.size(); ++ii)
		{
			pointsVec[ii].y += yVel;
		}
	}
}

void Paddle::setPlayerPaddle_Normal()
{
	texture = sfw::loadTextureMap("./Images/Paddle.png");
	color = BLUE;
	xPos = 100;
	yPos = 200;
	width = 10;
	height = 100;
	speed = 8;

	pointsVec.push_back(Vec2(xPos, yPos));
	pointsVec.push_back(Vec2(xPos, yPos - height));
	pointsVec.push_back(Vec2(xPos + width, yPos - height));
	pointsVec.push_back(Vec2(xPos + width, yPos));
}

void Paddle::setEnemyPaddle_Normal()
{
	texture = sfw::loadTextureMap("./Images/Paddle.png");
	color = RED;
	xPos = 700;
	yPos = 200;
	width = 10;
	height = 100;
	speed = 8;

	pointsVec.push_back(Vec2(xPos, yPos));
	pointsVec.push_back(Vec2(xPos, yPos - height));
	pointsVec.push_back(Vec2(xPos + width, yPos - height));
	pointsVec.push_back(Vec2(xPos + width, yPos));
}

void Paddle::setEnemyPaddle_AngleBracket()
{
	texture = sfw::loadTextureMap("./Images/Paddle.png");
	color = RED;
	xPos = 700;
	yPos = 200;
	width = 100;
	height = 100;
	speed = 8;

	pointsVec.push_back(Vec2(xPos + width / 2, yPos));
	pointsVec.push_back(Vec2(xPos        ,     yPos - height / 2));
	pointsVec.push_back(Vec2(xPos + width/2,   yPos - height));
	pointsVec.push_back(Vec2(xPos + width,     yPos - height));
	pointsVec.push_back(Vec2(xPos + width / 2, yPos - height / 2));
	pointsVec.push_back(Vec2(xPos + width,     yPos));
}

void Paddle::drawPaddle()
{
	for (int ii = 0; ii < pointsVec.size()-1; ++ii)
	{
		sfw::drawLine(pointsVec[ii].x, pointsVec[ii].y, pointsVec[ii+1].x, pointsVec[ii+1].y, color);
	}
	sfw::drawLine(pointsVec[pointsVec.size() - 1].x, pointsVec[pointsVec.size() - 1].y, pointsVec[0].x, pointsVec[0].y, color);
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

bool Paddle::collidedWithBall_Outer(int b_X, int b_Y, int b_R)
{
	if ((b_X - b_R < height + width && b_X - b_R > yPos) &&
		((b_Y - b_R > yPos - height && b_Y - b_R < yPos) || (b_Y + b_R > yPos - height && b_Y + b_R < yPos)))
	{
		return true;
	}	
	else if ((b_X + b_R < xPos + width && b_X + b_R > xPos) &&
		((b_Y - b_R > yPos - height && b_Y - b_R < yPos) || (b_Y + b_R > yPos - height && b_Y + b_R < yPos)))
	{
		return true;
	}
	else if ((yPos < b_Y + b_R && yPos > b_Y - b_R) &&
		((xPos > b_X - b_R && xPos < b_X + b_R) || (xPos + width > b_X - b_R && xPos + width < b_X + b_R)))
	{
		return true;
	}
	else if ((yPos - height < b_Y + b_R && yPos - height > b_Y - b_R) &&
		((xPos > b_X - b_R && xPos < b_X + b_R) || (xPos + width > b_X - b_R && xPos + width < b_X + b_R)))
	{
		return true;
	}
	return false;
}

// Returns the index of the face that had a collision with the ball.
// Returns -1 if no collision detected
int Paddle::faceOfCollision_Inner(int circlex, int circley, int circleradius)
{
	for (int ii = 0; ii < pointsVec.size()-1; ++ii)
	{
		float a = (pointsVec[ii+1].x - pointsVec[ii].x)*(pointsVec[ii + 1].x - pointsVec[ii].x) + (pointsVec[ii + 1].y - pointsVec[ii].y)*(pointsVec[ii+1].y - pointsVec[ii].y);
		float b = 2 * (pointsVec[ii+1].x - pointsVec[ii].x)*(pointsVec[ii].x - circlex) + 2 * (pointsVec[ii+1].y - pointsVec[ii].y)*(pointsVec[ii].y - circley);
		float c = (pointsVec[ii].x - circlex)*(pointsVec[ii].x - circlex) + (pointsVec[ii].y - circley)*(pointsVec[ii].y - circley) - (circleradius*circleradius);
		float t1 = (-b + sqrt(b*b - 4 * a*c)) / (2 * a);
		float t2 = (-b - sqrt(b*b - 4 * a*c)) / (2 * a);
		//a = (linex2 - linex1)*(linex2 - linex1) + (liney2 - liney1)*(liney2 - liney1);
		//b = 2 * (linex2 - linex1)*(linex1 - circlex) + 2 * (liney2 - liney1)*(liney1 - circley);
		//c = (linex1 - circlex)*(linex1 - circlex) + (liney1 - circley)*(liney1 - circley) - (circleradius*circleradius);
		//t1 = (-b + sqrt(b*b - 4 * a*c)) / (2 * a);
		//t2 = (-b - sqrt(b*b - 4 * a*c)) / (2 * a);

		if ((t1 >= 0 && t1 <= 1) || (t2 >= 0 && t2 <= 1))
		{
			return ii;
		}
	}

	return -1;
}

// Returns the index of the face that had a collision with the ball.
// Returns -1 if no collision detected
int Paddle::xNormalOfFaceIndex(int index)
{
	if (index != pointsVec.size()-1)
	{
		return pointsVec[index + 1].y - pointsVec[index].y;
	}

	return pointsVec[index].y - pointsVec[0].y;
}

int Paddle::yNormalOfFaceIndex(int index)
{
	if (index != pointsVec.size() - 1)
	{
		return pointsVec[index + 1].x - pointsVec[index].x;
	}

	return pointsVec[index].x - pointsVec[0].x;
}