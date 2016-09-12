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
	bool paddleAndBallCollisionX(Paddle, Ball);
	bool paddleAndBallCollisionY(Paddle, Ball);
};

GameState::GameState()
{
	playerPoints = 0;
	ceilingValue = 600;
	floorValue = 10;

	gameIsActive = true;

	playerPaddle.texture = sfw::loadTextureMap("./Images/Paddle.png", 10, 50);
	playerPaddle.xPos = 100;
	playerPaddle.yPos = 200;
	playerPaddle.width = 10;
	playerPaddle.height = 100;
	playerPaddle.speed = 8;

	enemyPaddle.texture = sfw::loadTextureMap("./Images/Paddle.png", 10, 50);
	enemyPaddle.xPos = 700;
	enemyPaddle.yPos = 200;
	enemyPaddle.width = 10;
	enemyPaddle.height = 100;
	enemyPaddle.speed = 8;

	gameBall.xPos = 200;
	gameBall.yPos = 250;
	gameBall.xVel = 9;
	gameBall.yVel = 9;
	gameBall.radius = 10;
	gameBall.color = WHITE;

	font = sfw::loadTextureMap("./res/tonc_font.png", 16, 6);

	sfw::setBackgroundColor(BLACK);
}

void GameState::update()
{
	playerPoints += 1;

	// Move Enemy paddle
	if (enemyPaddle.yPos < gameBall.yPos)
	{
		enemyPaddle.moveUp(ceilingValue);
	}
	else if (enemyPaddle.yPos - enemyPaddle.height > gameBall.yPos)
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

	gameBall.xPos += gameBall.xVel;
	gameBall.yPos += gameBall.yVel;
}

void GameState::draw()
{
	sfw::drawTexture(playerPaddle.texture, playerPaddle.xPos, playerPaddle.yPos, playerPaddle.width, playerPaddle.height, 0, false, 0, WHITE);
	sfw::drawTexture(enemyPaddle.texture, enemyPaddle.xPos, enemyPaddle.yPos, enemyPaddle.width, enemyPaddle.height, 0, false, 0, RED);
	sfw::drawCircle(gameBall.xPos, gameBall.yPos, gameBall.radius, 12, gameBall.color);

	sfw::drawString(font, std::to_string(playerPoints).c_str(), 0, 600, 48, 48, 0, ' ');
}


void GameState::boundaryCollisionController(Ball * ball, int ceilingVal, int floorVal)
{
	if (gameBall.xPos + gameBall.radius > 800)
	{
		gameBall.xVel = -gameBall.xVel;
	}
	else if (gameBall.xPos < 0)
	{
		//gameIsActive = false;
		gameBall.xVel = -gameBall.xVel;
	}

	if ((gameBall.yPos + gameBall.radius >= ceilingVal) ||
		(gameBall.yPos - gameBall.radius <= floorVal))
	{
		gameBall.yVel = -gameBall.yVel;
	}
}

void GameState::paddleCollisionController(Paddle padd, Ball * ball)
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
	if ((ball.xPos - ball.radius < padd.xPos + padd.width && ball.xPos - ball.radius > padd.xPos) &&
		((ball.yPos - ball.radius > padd.yPos - padd.height && ball.yPos - ball.radius < padd.yPos) || (ball.yPos + ball.radius > padd.yPos - padd.height && ball.yPos + ball.radius < padd.yPos)))
	{
		return true;
	}
	return false;
}

bool GameState::paddleLeftAndBallCollision(Paddle padd, Ball ball)
{
	if ((ball.xPos + ball.radius < padd.xPos + padd.width && ball.xPos + ball.radius > padd.xPos) &&
		((ball.yPos - ball.radius > padd.yPos - padd.height && ball.yPos - ball.radius < padd.yPos) || (ball.yPos + ball.radius > padd.yPos - padd.height && ball.yPos + ball.radius < padd.yPos)))
	{
		return true;
	}
	return false;
}

bool GameState::paddleTopAndBallCollision(Paddle padd, Ball ball)
{
	if ((padd.yPos < ball.yPos + ball.radius && padd.yPos > ball.yPos - ball.radius) &&
		((padd.xPos > ball.xPos - ball.radius && padd.xPos < ball.xPos + ball.radius) || (padd.xPos + padd.width > ball.xPos - ball.radius && padd.xPos + padd.width < ball.xPos + ball.radius)))
	{
		return true;
	}
	return false;
}

bool GameState::paddleBottomAndBallCollision(Paddle padd, Ball ball)
{
	if ((padd.yPos - padd.height < ball.yPos + ball.radius && padd.yPos - padd.height > ball.yPos - ball.radius) &&
		((padd.xPos > ball.xPos - ball.radius && padd.xPos < ball.xPos + ball.radius) || (padd.xPos + padd.width > ball.xPos - ball.radius && padd.xPos + padd.width < ball.xPos + ball.radius)))
	{
		return true;
	}
	return false;
}

bool GameState::paddleAndBallCollisionX(Paddle padd, Ball ball)
{
	// Detect if the ball hit the front face of the paddle

	if (((gameBall.yPos + gameBall.radius >= padd.yPos - padd.height && gameBall.yPos + gameBall.radius <= padd.yPos) || // Ball top is between y's of paddle
		(gameBall.yPos - gameBall.radius >= padd.yPos - padd.height && gameBall.yPos - gameBall.radius <= padd.yPos)) && // Ball bottom is between y's of paddle
		((gameBall.xPos - gameBall.radius <= padd.xPos + padd.width && gameBall.xPos - gameBall.radius >= padd.xPos) || // Ball left is between x's of paddle
		(gameBall.xPos + gameBall.radius <= padd.xPos + padd.width && gameBall.xPos + gameBall.radius >= padd.xPos)))    // Ball right is between x's of paddle
	{
		return true;
	}
	return false;
}

bool GameState::paddleAndBallCollisionY(Paddle padd, Ball ball)
{
	// Detect if the ball hit the top or bottom face of the paddle
	if (((padd.xPos >= gameBall.xPos - gameBall.radius && padd.xPos <= gameBall.xPos + gameBall.radius) || // Ball top is between y's of paddle
		(padd.xPos + padd.width >= gameBall.xPos - gameBall.radius && padd.xPos + padd.width <= gameBall.xPos + gameBall.radius)) && // Ball bottom is between y's of paddle
		((padd.yPos >= gameBall.yPos - gameBall.radius && padd.yPos <= gameBall.yPos + gameBall.radius) || // Ball top is between y's of paddle
		(padd.yPos - padd.height >= gameBall.yPos - gameBall.radius && padd.yPos - padd.height <= gameBall.yPos + gameBall.radius)))    // Ball right is between x's of paddle
	{
		return true;
	}

	return false;
}