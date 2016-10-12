#pragma once

#include "sfwdraw.h"
#include <string>
using std::string;
#include <iostream>
#include <vector>
using std::vector;
#include "Vec2.h"

class Paddle
{
private:
	Vec2 pos, vel, dim;
	int speed;
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

	bool collidedWithBall_Outer(Vec2, int);
	vector<int> facesOfCollision_Inner(Vec2, int);
	Vec2 perpVecOfFaceIndex(int index);
	int xOfPoint(int);
	int yOfPoint(int);
};

void Paddle::moveUp(int ceilingValue)
{
	if (pos.y >= ceilingValue)
	{
		pos.y = ceilingValue;
		vel.y = 0;
	}
	else
	{
		vel.y = speed;
		pos.y += vel.y;
		for (int ii = 0; ii < pointsVec.size(); ++ii)
		{
			pointsVec[ii].y += vel.y;
		}
	}
	std::cout << vel.y << std::endl;
}

void Paddle::moveDown(int floorValue)
{
	if (pos.y - dim.y <= floorValue)
	{
		pos.y = dim.y + floorValue;
		vel.y = 0;
	}
	else
	{
		vel.y = -speed;
		pos.y += vel.y;
		for (int ii = 0; ii < pointsVec.size(); ++ii)
		{
			pointsVec[ii].y += vel.y;
		}
	}
}

void Paddle::setPlayerPaddle_Normal()
{
	texture = sfw::loadTextureMap("./Images/Paddle.png");
	color = BLUE;
	pos.x = 100;
	pos.y = 350;
	dim.x = 10;
	dim.y = 100;
	speed = 8;

	pointsVec.push_back(Vec2(pos.x,         pos.y));
	pointsVec.push_back(Vec2(pos.x,         pos.y - dim.y));
	pointsVec.push_back(Vec2(pos.x + dim.x, pos.y - dim.y));
	pointsVec.push_back(Vec2(pos.x + dim.x, pos.y));
}

void Paddle::setEnemyPaddle_Normal()
{
	texture = sfw::loadTextureMap("./Images/Paddle.png");
	color = RED;
	pos.x = 700;
	pos.y = 350;
	dim.x = 10;
	dim.y = 100;
	speed = 8;
	;
	pointsVec.push_back(Vec2(pos.x,         pos.y));
	pointsVec.push_back(Vec2(pos.x,         pos.y - dim.y));
	pointsVec.push_back(Vec2(pos.x + dim.x, pos.y - dim.y));
	pointsVec.push_back(Vec2(pos.x + dim.x, pos.y));
}

void Paddle::setEnemyPaddle_AngleBracket()
{
	texture = sfw::loadTextureMap("./Images/Paddle.png");
	color = RED;
	pos.x = 600;
	pos.y = 400;
	dim.x = 100;
	dim.y = 100;
	speed = 8;

	pointsVec.push_back(Vec2(pos.x + dim.x / 2, pos.y));
	pointsVec.push_back(Vec2(pos.x,             pos.y - dim.y / 2));
	pointsVec.push_back(Vec2(pos.x + dim.x /2,  pos.y - dim.y));
	pointsVec.push_back(Vec2(pos.x + dim.x,     pos.y - dim.y));
	pointsVec.push_back(Vec2(pos.x + dim.x / 2, pos.y - dim.y / 2));
	pointsVec.push_back(Vec2(pos.x + dim.x,     pos.y));
}

void Paddle::drawPaddle()
{
	for (int ii = 0; ii < pointsVec.size()-1; ++ii)
	{
		sfw::drawLine(pointsVec[ii].x, pointsVec[ii].y, pointsVec[ii+1].x, pointsVec[ii+1].y, color);
	}
	sfw::drawLine(pointsVec[pointsVec.size() - 1].x, pointsVec[pointsVec.size() - 1].y, pointsVec[0].x, pointsVec[0].y, color);

	//sfw::drawCircle(pointsVec[1].x, pointsVec[1].y, 5, 12, BLACK);
}

void Paddle::set_xPos(int newX)
{
	pos.x = newX;
}
void Paddle::set_yPos(int newY)
{
	pos.y = newY;
}
int Paddle::get_xPos() const
{
	return pos.x;
}
int Paddle::get_yPos() const
{
	return pos.y;
}

void Paddle::set_yVel(int newY)
{
	vel.y = newY;
}
int Paddle::get_yVel() const
{
	return vel.y;
}

void Paddle::set_width(int newW)
{
	dim.x = newW;
}
void Paddle::set_height(int newH)
{
	dim.y = newH;
}
int Paddle::get_width() const
{
	return dim.x;
}
int Paddle::get_height() const
{
	return dim.y;
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

bool Paddle::collidedWithBall_Outer(Vec2 ballPos, int b_R)
{
	//std::cout << "b_Y + b_R: "     << ballPos.y + b_R << std::endl;
	//std::cout << "b_Y - b_R: "     << ballPos.y - b_R << std::endl;
	//std::cout << "b_Y: "           << ballPos.y << std::endl;
	//std::cout << "yPos: "          << pos.y << std::endl;
	//std::cout << "yPos - height: " << pos.y - dim.y << std::endl;
	//std::cout << "No collision detected" << std::endl;
	//system("pause");
	// right side
	if (ballPos.x - b_R > pos.x + dim.x)
	{
		//std::cout << "No collision detected" << std::endl;
		//system("pause");
		return false;
	}	
	// left side
	else if (ballPos.x + b_R < pos.x)
	{
		//std::cout << "No collision detected" << std::endl;
		//system("pause");
		return false;
	}
	// top side
	else if (ballPos.y - b_R > pos.y)
	{
		//std::cout << "No collision detected" << std::endl;
		//system("pause");
		return false;
	}
	// bottom side
	else if (ballPos.y + b_R < pos.y - dim.y)
	{
		//std::cout << "No collision detected" << std::endl;
		//system("pause");
		return false;
	}

	//std::cout << "Collision detected" << std::endl;
	//system("pause");
	return true;
}

// Returns the index of the face that had a collision with the ball.
// Returns -1 if no collision detected
vector<int> Paddle::facesOfCollision_Inner(Vec2 ballPos, int circleradius)
{
	vector<int> faces;

	for (int ii = 0; ii < pointsVec.size()-1; ++ii)
	{
		float a = (pointsVec[ii+1].x - pointsVec[ii].x)*(pointsVec[ii + 1].x - pointsVec[ii].x) + (pointsVec[ii + 1].y - pointsVec[ii].y)*(pointsVec[ii+1].y - pointsVec[ii].y);
		float b = 2 * (pointsVec[ii+1].x - pointsVec[ii].x)*(pointsVec[ii].x - ballPos.x) + 2 * (pointsVec[ii+1].y - pointsVec[ii].y)*(pointsVec[ii].y - ballPos.y);
		float c = (pointsVec[ii].x - ballPos.x)*(pointsVec[ii].x - ballPos.x) + (pointsVec[ii].y - ballPos.y)*(pointsVec[ii].y - ballPos.y) - (circleradius*circleradius);
		float t1 = (-b + sqrt(b*b - 4 * a*c)) / (2 * a);
		float t2 = (-b - sqrt(b*b - 4 * a*c)) / (2 * a);
		//a = (linex2 - linex1)*(linex2 - linex1) + (liney2 - liney1)*(liney2 - liney1);
		//b = 2 * (linex2 - linex1)*(linex1 - circlex) + 2 * (liney2 - liney1)*(liney1 - circley);
		//c = (linex1 - circlex)*(linex1 - circlex) + (liney1 - circley)*(liney1 - circley) - (circleradius*circleradius);
		//t1 = (-b + sqrt(b*b - 4 * a*c)) / (2 * a);
		//t2 = (-b - sqrt(b*b - 4 * a*c)) / (2 * a);

		if ((t1 >= 0 && t1 <= 1) || (t2 >= 0 && t2 <= 1) || (t1 >= 1 && t2 <= 0))
		{
			faces.push_back(ii);
		}
	}

	// Check the face from node pointsVec.size()-1 to node 0
	float a = (pointsVec[0].x - pointsVec[pointsVec.size() - 1].x)*(pointsVec[0].x - pointsVec[pointsVec.size() - 1].x) + (pointsVec[0].y - pointsVec[pointsVec.size() - 1].y)*(pointsVec[0].y - pointsVec[pointsVec.size() - 1].y);
	float b = 2 * (pointsVec[0].x - pointsVec[pointsVec.size() - 1].x)*(pointsVec[pointsVec.size() - 1].x - ballPos.x) + 2 * (pointsVec[0].y - pointsVec[pointsVec.size() - 1].y)*(pointsVec[pointsVec.size() - 1].y - ballPos.y);
	float c = (pointsVec[pointsVec.size() - 1].x - ballPos.x)*(pointsVec[pointsVec.size() - 1].x - ballPos.x) + (pointsVec[pointsVec.size() - 1].y - ballPos.y)*(pointsVec[pointsVec.size() - 1].y - ballPos.y) - (circleradius*circleradius);
	float t1 = (-b + sqrt(b*b - 4 * a*c)) / (2 * a);
	float t2 = (-b - sqrt(b*b - 4 * a*c)) / (2 * a);

	std::cout << "t1: " << t1 << std::endl;
	std::cout << "t2: " << t2 << std::endl;

	if ((t1 >= 0 && t1 <= 1) || (t2 >= 0 && t2 <= 1) || (t1 >= 1 && t2 <= 0))
	{
		faces.push_back(pointsVec.size() - 1);
	}

	if (faces.size() == 0)
		faces.push_back(-1);
	return faces;
}

// Returns the index of the face that had a collision with the ball.
// Returns -1 if no collision detected
Vec2 Paddle::perpVecOfFaceIndex(int index)
{
	if (index != pointsVec.size()-1)
	{
		return Vec2(pointsVec[index + 1].y - pointsVec[index].y, 
					-(pointsVec[index + 1].x - pointsVec[index].x));
	}

	return Vec2(pointsVec[0].y - pointsVec[index].y,
				-(pointsVec[0].x - pointsVec[index].x));
}

int Paddle::xOfPoint(int index)
{
	if (index == pointsVec.size())
		return pointsVec[0].x;

	return pointsVec[index].x;
}

int Paddle::yOfPoint(int index)
{
	if (index == pointsVec.size())
		return pointsVec[0].y;

	return pointsVec[index].y;
}