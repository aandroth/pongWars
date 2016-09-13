#pragma once

#include <string>
using std::string;
#include "Paddle.h"
#include "Ball.h"
#include "sfwdraw.h"

class GameState
{
public:
	GameState();
	void update();
	void draw();

private:
	Paddle playerPaddle, enemyPaddle;
	Ball gameBall;
	unsigned font, playerPoints;
	int ceilingValue = 600, floorValue = 10;
	bool gameIsActive;

	// Colision detection functions
	void boundaryCollisionController(Ball * ball, int ceilingVal, int floorVal);
	void paddleCollisionController(Paddle padd, Ball * ball);
	bool paddleRightAndBallCollision(Paddle padd, Ball ball);
	bool paddleLeftAndBallCollision(Paddle padd, Ball ball);
	bool paddleTopAndBallCollision(Paddle padd, Ball ball);
	bool paddleBottomAndBallCollision(Paddle padd, Ball ball);
};

GameState::GameState()
{
	playerPoints = 0;
	ceilingValue = 600;
	floorValue = 10;

	gameIsActive = true;

	playerPaddle.setPlayerPaddle_Normal();
	enemyPaddle.setEnemyPaddle_Normal();
	gameBall.setBall_Normal();

	font = sfw::loadTextureMap("./res/tonc_font.png", 16, 6);

	sfw::setBackgroundColor(BLACK);
}

void GameState::update()
{
	playerPoints += 1;

	// Move Enemy paddle
	if (enemyPaddle.get_yPos() < gameBall.get_yPos())
	{
		enemyPaddle.moveUp(ceilingValue);
	}
	else if (enemyPaddle.get_yPos() - enemyPaddle.get_height() > gameBall.get_yPos())
	{
		enemyPaddle.moveDown(floorValue);
	}

	// Move Player paddle
	if (sfw::getKey(KEY_UP))
	{
		playerPaddle.moveUp(ceilingValue);
	}
	else if (sfw::getKey(KEY_DOWN))
	{
		playerPaddle.moveDown(floorValue);
	}

	paddleCollisionController(playerPaddle, &gameBall);
	paddleCollisionController(enemyPaddle, &gameBall);
	boundaryCollisionController(&gameBall, ceilingValue, floorValue);

	gameBall.set_xPos(gameBall.get_xPos() + gameBall.get_xVel());
	gameBall.set_yPos(gameBall.get_yPos() + gameBall.get_yVel());
}

void GameState::draw()
{
	sfw::drawTexture(sfw::loadTextureMap("./Images/Paddle.png", 10, 50), playerPaddle.get_xPos(), playerPaddle.get_yPos(), playerPaddle.get_width(), playerPaddle.get_height(), 0, false, 0, WHITE);
	sfw::drawTexture(sfw::loadTextureMap("./Images/Paddle.png", 10, 50), enemyPaddle.get_xPos(), enemyPaddle.get_yPos(), enemyPaddle.get_width(), enemyPaddle.get_height(), 0, false, 0, RED);
	sfw::drawCircle(gameBall.get_xPos(), gameBall.get_yPos(), gameBall.get_radius(), 12, gameBall.get_color());

	sfw::drawString(font, std::to_string(playerPoints).c_str(), 0, 600, 48, 48, 0, ' ');
}


void GameState::boundaryCollisionController(Ball * ball, int ceilingVal, int floorVal)
{
	int b_X = ball->get_xPos(), b_vel_X = ball->get_xVel();
	int b_Y = ball->get_yPos(), b_vel_Y = ball->get_yVel();

	if (b_X + gameBall.get_radius() > 800)
	{
		gameBall.set_xVel(-b_vel_X);
	}
	else if (b_X < 0)
	{
		//gameIsActive = false;
		gameBall.set_xVel(-b_vel_X);
	}

	if (b_Y + gameBall.get_radius() >= ceilingVal)
	{
		gameBall.set_yVel(-b_vel_Y);
		gameBall.set_yPos(b_Y - 10);
	}
	else if (b_Y - gameBall.get_radius() <= floorVal)
	{
		gameBall.set_yVel(-b_vel_Y);
		gameBall.set_yPos(b_Y + 10);
	}
}

void GameState::paddleCollisionController(Paddle padd, Ball * ball)
{
	int b_X = ball->get_xPos(), b_vel_X = ball->get_xVel();
	int b_Y = ball->get_yPos(), b_vel_Y = ball->get_yVel();

	if (paddleRightAndBallCollision(padd, *ball))
	{
		ball->set_yVel(b_vel_Y + padd.get_yVel() / 2.0);
		ball->set_xVel(-b_vel_X);
		ball->set_xPos(b_X + 10);
	}
	else if (paddleLeftAndBallCollision(padd, *ball))
	{
		ball->set_yVel(b_vel_Y + padd.get_yVel() / 2.0);
		ball->set_xVel(-b_vel_X);
		ball->set_xPos(b_X - 10);
	}
	if (paddleTopAndBallCollision(padd, *ball))
	{
		ball->set_yVel(b_vel_Y + padd.get_yVel() / 2.0);
		ball->set_yVel(-b_vel_Y);
		ball->set_yPos(b_Y + 10);
	}
	else if (paddleBottomAndBallCollision(padd, *ball))
	{
		ball->set_yVel(b_vel_Y + padd.get_yVel() / 2.0);
		ball->set_yVel(-b_vel_Y);
		ball->set_yPos(b_Y - 10);
	}
}

// Find normal of plane

// 

/*
void paddleCollisionController(Paddle padd, Ball * ball)
{
	if (paddleRightAndBallCollision(padd, *ball))
	{
		ball->yVel += padd.yVel / 2.0;
		ball->xVel = -ball->xVel;
		ball->xPos += 10;
	}
	else if (paddleLeftAndBallCollision(padd, *ball))
	{
		ball->yVel += padd.yVel / 2.0;
		ball->xVel = -ball->xVel;
		ball->xPos -= 10;
	}
	if (paddleTopAndBallCollision(padd, *ball))
	{
		ball->yVel += padd.yVel * 2.0;
		ball->yVel = -ball->yVel;
		ball->yPos += 10;
	}
	else if (paddleBottomAndBallCollision(padd, *ball))
	{
		ball->yVel += padd.yVel * 2.0;
		ball->yVel = -ball->yVel;
		ball->yPos -= 10;
	}
}*/

bool GameState::paddleRightAndBallCollision(Paddle padd, Ball ball)
{
	int b_X = ball.get_xPos(), b_vel_X = ball.get_xVel();
	int b_Y = ball.get_yPos(), b_vel_Y = ball.get_yVel();
	int b_R = ball.get_radius();

	int p_X = padd.get_xPos(), p_Y = padd.get_yPos();
	int p_W = padd.get_width(), p_H = padd.get_height();

	if ((b_X - b_R < p_X + p_W && b_X - b_R > p_X) &&
		((b_Y - b_R > p_Y - p_H && b_Y - b_R < p_Y) || (b_Y + b_R > p_Y - p_H && b_Y + b_R < p_Y)))
	{
		return true;
	}
	return false;
}

bool GameState::paddleLeftAndBallCollision(Paddle padd, Ball ball)
{
	int b_X = ball.get_xPos(), b_vel_X = ball.get_xVel();
	int b_Y = ball.get_yPos(), b_vel_Y = ball.get_yVel();
	int b_R = ball.get_radius();

	int p_X = padd.get_xPos(), p_Y = padd.get_yPos();
	int p_W = padd.get_width(), p_H = padd.get_height();

	if ((b_X + b_R < p_X + p_W && b_X + b_R > p_X) &&
		((b_Y - b_R > p_Y - p_H && b_Y - b_R < p_Y) || (b_Y + b_R > p_Y - p_H && b_Y + b_R < p_Y)))
	{
		return true;
	}
	return false;
}

bool GameState::paddleTopAndBallCollision(Paddle padd, Ball ball)
{
	int b_X = ball.get_xPos(), b_vel_X = ball.get_xVel();
	int b_Y = ball.get_yPos(), b_vel_Y = ball.get_yVel();
	int b_R = ball.get_radius();

	int p_X = padd.get_xPos(), p_Y = padd.get_yPos();
	int p_W = padd.get_width(), p_H = padd.get_height();

	if ((p_Y < b_Y + b_R && p_Y > b_Y - b_R) &&
		((p_X > b_X - b_R && p_X < b_X + b_R) || (p_X + p_W > b_X - b_R && p_X + p_W < b_X + b_R)))
	{
		return true;
	}
	return false;
}

bool GameState::paddleBottomAndBallCollision(Paddle padd, Ball ball)
{
	int b_X = ball.get_xPos(), b_vel_X = ball.get_xVel();
	int b_Y = ball.get_yPos(), b_vel_Y = ball.get_yVel();
	int b_R = ball.get_radius();

	int p_X = padd.get_xPos(), p_Y = padd.get_yPos();
	int p_W = padd.get_width(), p_H = padd.get_height();

	if ((p_Y - p_H < b_Y + b_R && p_Y - p_H > b_Y - b_R) &&
		((p_X > b_X - b_R && p_X < b_X + b_R) || (p_X + p_W > b_X - b_R && p_X + p_W < b_X + b_R)))
	{
		return true;
	}
	return false;
}