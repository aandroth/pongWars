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
	unsigned background = sfw::loadTextureMap("./Images/Background.png");
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
	else
	{
		enemyPaddle.set_yVel(0);
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
	else
	{
		playerPaddle.set_yVel(0);
	}

	paddleCollisionController(playerPaddle, &gameBall);
	paddleCollisionController(enemyPaddle, &gameBall);
	boundaryCollisionController(&gameBall, ceilingValue, floorValue);

	gameBall.set_xPos(gameBall.get_xPos() + gameBall.get_xVel());
	gameBall.set_yPos(gameBall.get_yPos() + gameBall.get_yVel());
}

void GameState::draw()
{
	sfw::drawTexture(background, 400, 300, 800, 600);
	sfw::drawTexture(playerPaddle.get_texture(), playerPaddle.get_xPos(), playerPaddle.get_yPos(), playerPaddle.get_width(), playerPaddle.get_height(), 0, false, 0, CYAN);
	sfw::drawTexture(enemyPaddle.get_texture(), enemyPaddle.get_xPos(), enemyPaddle.get_yPos(), enemyPaddle.get_width(), enemyPaddle.get_height(), 0, false, 0, RED);

	//sfw::drawCircle(gameBall.get_xPos(), gameBall.get_yPos(), gameBall.get_radius(), 12, gameBall.get_color());
	sfw::drawTexture(background, gameBall.get_xPos(), gameBall.get_yPos(), gameBall.get_radius(), gameBall.get_radius());
	sfw::drawLine(gameBall.get_xPos(), gameBall.get_yPos(), gameBall.get_xVel()*2 + gameBall.get_xPos(), gameBall.get_yVel()*2 + gameBall.get_yPos(), RED);
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
		//ball->set_yVel(b_vel_Y + padd.get_yVel() / 2.0);
		//ball->set_xVel(-b_vel_X);
		//ball->set_xPos(b_X + 10);

		// Find normal of plane
		int x_Normal = padd.get_height();
		int y_Normal = 0;		
		x_Normal = x_Normal / (x_Normal + y_Normal);
		y_Normal = y_Normal / (x_Normal + y_Normal);

		// Move ball out of paddle
		ball->set_xPos(ball->get_radius() + padd.get_xPos() + padd.get_width());

		// Reflect the ball's vector
		ball->set_xVel((ball->get_xVel() - (2 * (ball->get_xVel()*x_Normal + ball->get_yVel()*y_Normal)*x_Normal)));
		ball->set_yVel((ball->get_yVel() - (2 * (ball->get_xVel()*x_Normal + ball->get_yVel()*y_Normal)*y_Normal)));
		ball->set_yVel(ball->get_yVel() + padd.get_yVel()*0.5);
	}
	else if (paddleLeftAndBallCollision(padd, *ball))
	{
		//ball->set_yVel(b_vel_Y + padd.get_yVel() / 2.0);
		//ball->set_xVel(-b_vel_X);
		//ball->set_xPos(b_X - 10);

		// Find normal of plane
		int x_Normal = -padd.get_height();
		int y_Normal = 0;
		x_Normal = x_Normal / (x_Normal + y_Normal);
		y_Normal = y_Normal / (x_Normal + y_Normal);

		// Move ball out of paddle
		ball->set_xPos(padd.get_xPos() - ball->get_radius());

		// Reflect the ball's vector
		ball->set_xVel((ball->get_xVel() - (2 * (ball->get_xVel()*x_Normal + ball->get_yVel()*y_Normal)*x_Normal)));
		ball->set_yVel((ball->get_yVel() - (2 * (ball->get_xVel()*x_Normal + ball->get_yVel()*y_Normal)*y_Normal)));
		ball->set_yVel(ball->get_yVel() + padd.get_yVel()*0.5);
	}
	if (paddleTopAndBallCollision(padd, *ball))
	{
		//ball->set_yVel(b_vel_Y + padd.get_yVel() / 2.0);
		//ball->set_yVel(-b_vel_Y);
		//ball->set_yPos(b_Y + 10);

		// Find normal of plane
		int x_Normal = 0;
		int y_Normal = -padd.get_width();
		x_Normal = x_Normal / (x_Normal + y_Normal);
		y_Normal = y_Normal / (x_Normal + y_Normal);

		// Move ball out of paddle
		ball->set_yPos(padd.get_yPos() + ball->get_radius());

		// Reflect the ball's vector
		ball->set_xVel((ball->get_xVel() - (2 * (ball->get_xVel()*x_Normal + ball->get_yVel()*y_Normal)*x_Normal)));
		ball->set_yVel((ball->get_yVel() - (2 * (ball->get_xVel()*x_Normal + ball->get_yVel()*y_Normal)*y_Normal)));
		ball->set_yVel(ball->get_yVel() + padd.get_yVel()*0.5);
	}
	else if (paddleBottomAndBallCollision(padd, *ball))
	{
		//ball->set_yVel(b_vel_Y + padd.get_yVel() / 2.0);
		//ball->set_yVel(-b_vel_Y);
		//ball->set_yPos(b_Y - 10);

		// Find normal of plane
		int x_Normal = 0;
		int y_Normal = -padd.get_width();
		x_Normal = x_Normal / (x_Normal + y_Normal);
		y_Normal = y_Normal / (x_Normal + y_Normal);

		// Move ball out of paddle
		ball->set_yPos(padd.get_yPos() - padd.get_height() - ball->get_radius());

		// Reflect the ball's vector
		ball->set_xVel((ball->get_xVel() - (2 * (ball->get_xVel()*x_Normal + ball->get_yVel()*y_Normal)*x_Normal)));
		ball->set_yVel((ball->get_yVel() - (2 * (ball->get_xVel()*x_Normal + ball->get_yVel()*y_Normal)*y_Normal)));
		ball->set_yVel(ball->get_yVel() + padd.get_yVel()*0.5);
	}
}

//void GameState::paddleCollisionController(Paddle padd, Ball * ball)
//{
//	if (paddleRightAndBallCollision(padd, *ball))
//	{
//		// Find normal of plane
//		int x_Normal = padd.get_yPos();
//		int y_Normal = padd.get_xPos();
//
//		x_Normal = x_Normal / (y_Normal + x_Normal);
//		x_Normal -= padd.get_xPos();
//		y_Normal = y_Normal / (y_Normal + x_Normal);
//		y_Normal -= padd.get_yPos();
//	}/**/
//	else if (paddleLeftAndBallCollision(padd, *ball))
//	{
//		ball->yVel += padd.yVel / 2.0;
//		ball->xVel = -ball->xVel;
//		ball->xPos -= 10;
//	}
//	if (paddleTopAndBallCollision(padd, *ball))
//	{
//		ball->yVel += padd.yVel * 2.0;
//		ball->yVel = -ball->yVel;
//		ball->yPos += 10;
//	}
//	else if (paddleBottomAndBallCollision(padd, *ball))
//	{
//		ball->yVel += padd.yVel * 2.0;
//		ball->yVel = -ball->yVel;
//		ball->yPos -= 10;
//	}
//}

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