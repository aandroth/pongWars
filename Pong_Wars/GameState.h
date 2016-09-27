#pragma once

#include <string>
using std::string;
#include "Paddle.h"
#include "Ball.h"
#include "sfwdraw.h"
#include <iostream>

class GameState
{
public:
	GameState();
	void update();
	void draw();
	bool gameplayIsActive();

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
	void moveBallOutsideOfPaddle(Ball, Paddle, int);
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
	//enemyPaddle.setEnemyPaddle_Normal();
	enemyPaddle.setEnemyPaddle_AngleBracket();
	gameBall.setBall_Normal();

	font = sfw::loadTextureMap("./res/tonc_font.png", 16, 6);
}

void GameState::update()
{
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
	sfw::drawTexture(playerPaddle.get_texture(), playerPaddle.get_xPos(), playerPaddle.get_yPos(), playerPaddle.get_width(), playerPaddle.get_height(), 0, false, 0, WHITE);
	sfw::drawTexture(enemyPaddle.get_texture(), enemyPaddle.get_xPos(), enemyPaddle.get_yPos(), enemyPaddle.get_width(), enemyPaddle.get_height(), 0, false, 0, RED);
	sfw::drawCircle(gameBall.get_xPos(), gameBall.get_yPos(), gameBall.get_radius(), 12, gameBall.get_color());

	sfw::drawTexture(background, 400, 300, 800, 600);
	//sfw::drawTexture(playerPaddle.get_texture(), playerPaddle.get_xPos(), playerPaddle.get_yPos(), playerPaddle.get_width(), playerPaddle.get_height(), 0, false, 0, CYAN);
	//sfw::drawTexture(enemyPaddle.get_texture(), enemyPaddle.get_xPos(), enemyPaddle.get_yPos(), enemyPaddle.get_width(), enemyPaddle.get_height(), 0, false, 0, RED);
	playerPaddle.drawPaddle();
	enemyPaddle.drawPaddle();

	sfw::drawCircle(gameBall.get_xPos(), gameBall.get_yPos(), gameBall.get_radius(), 12, gameBall.get_color());
	//sfw::drawTexture(gameBall.get_texture(), gameBall.get_xPos(), gameBall.get_yPos(), gameBall.get_radius(), gameBall.get_radius());
	//fw::drawLine(gameBall.get_xPos(), gameBall.get_yPos(), gameBall.get_xVel()*2 + gameBall.get_xPos(), gameBall.get_yVel()*2 + gameBall.get_yPos(), RED);
	sfw::drawString(font, std::to_string(playerPoints).c_str(), 0, 600, 48, 48, 0, ' ');
	//sfw::drawString(font, std::to_string(gameBall.get_xVel()).c_str(), 0, 600, 48, 48, 0, ' ');
	//sfw::drawString(font, std::to_string(gameBall.get_yVel()).c_str(), 0, 500, 48, 48, 0, ' ');


}

void GameState::boundaryCollisionController(Ball * ball, int ceilingVal, int floorVal)
{
	int b_X = ball->get_xPos(), b_vel_X = ball->get_xVel();
	int b_Y = ball->get_yPos(), b_vel_Y = ball->get_yVel();

	if (b_X + gameBall.get_radius() > 800)
	{
		//playerPoints += 1;
		//gameBall.set_xVel(4);
		//gameBall.set_yVel(0);
		//gameBall.set_xPos(400);
		//gameBall.set_yPos(300);
		gameBall.set_xVel(-abs(gameBall.get_xVel()));
	}
	else if (b_X < 0)
	{
		//gameIsActive = false;
		gameBall.set_xVel(abs(gameBall.get_xVel()));
	}

	if (b_Y + gameBall.get_radius() >= ceilingVal)
	{
		gameBall.set_yVel(-abs(b_vel_Y));
		gameBall.set_yPos(b_Y - 10);
	}
	else if (b_Y - gameBall.get_radius() <= floorVal)
	{
		gameBall.set_yVel(abs(b_vel_Y));
		gameBall.set_yPos(b_Y + 10);
	}
}

void GameState::paddleCollisionController(Paddle padd, Ball * ball)
{
	int b_X = ball->get_xPos(), b_vel_X = ball->get_xVel();
	int b_Y = ball->get_yPos(), b_vel_Y = ball->get_yVel();

	if (padd.collidedWithBall_Outer(ball->get_xPos(), ball->get_yPos(), ball->get_radius()))
	{
		vector<int> faces;
		faces = padd.facesOfCollision_Inner(ball->get_xPos(), ball->get_yPos(), ball->get_radius());
		
		if (faces[0] != -1)
		{
			// Reflect the ball's vector
			float oldX = ball->get_xVel(), oldY = ball->get_yVel();

			for (int ii = 0; ii < faces.size(); ++ii)
			{
				std::cout << "face: " << faces[ii] << std::endl;
				// Get normal of plane
				float x_Normal = padd.xNormalOfFaceIndex(faces[ii]);
				float y_Normal = -padd.yNormalOfFaceIndex(faces[ii]);
				float normalizedX, normalizedY;
				std::cout << "x: " << x_Normal << std::endl;
				std::cout << "y: " << y_Normal << std::endl;

				normalizedX = (x_Normal / sqrt(x_Normal*x_Normal + y_Normal*y_Normal));
				normalizedY = (y_Normal / sqrt(x_Normal*x_Normal + y_Normal*y_Normal));

				std::cout << "original x: " << ball->get_xVel() << std::endl;
				std::cout << "original y: " << ball->get_yVel() << std::endl;
				float newX = oldX - (2.0 * (oldX*normalizedX + oldY*normalizedY)*normalizedX);
				float newY = oldY - (2.0 * (oldX*normalizedX + oldY*normalizedY)*normalizedY);
				ball->set_xVel(newX);
				ball->set_yVel(newY);
				std::cout << "reflect x: " << ball->get_xVel() << std::endl;
				std::cout << "reflect y: " << ball->get_yVel() << std::endl;
				std::cout << "normalizedX x: " << normalizedX << std::endl;
				std::cout << "normalizedY y: " << normalizedY << std::endl;
				std::cout << "normalizedY y: " << normalizedY << std::endl;
				ball->set_yVel(ball->get_yVel() + padd.get_yVel());

				// Move ball out of paddle
				//moveBallOutsideOfPaddle(*ball, padd, 1);
				ball->set_xPos(ball->get_xPos() + 14 * normalizedX);
				ball->set_yPos(ball->get_yPos() + 14 * normalizedY);
			}
		}
	}
}

void GameState::moveBallOutsideOfPaddle(Ball ball, Paddle padd, int faceIndex)
{
	// Get normal of plane
	float x_Normal = -3; // padd.xNormalOfFaceIndex(faceIndex);
	float y_Normal = -2; // -padd.yNormalOfFaceIndex(faceIndex);
	float normalizedX, normalizedY;

	normalizedX = (x_Normal / sqrt(x_Normal*x_Normal + y_Normal*y_Normal));
	normalizedY = (y_Normal / sqrt(x_Normal*x_Normal + y_Normal*y_Normal));

	Vec2 paddPoint0 = Vec2(3, 4);// padd.xOfPoint(faceIndex), padd.yOfPoint(faceIndex));
	Vec2 paddPoint1 = Vec2(6, 2);// padd.xOfPoint(faceIndex + 1), padd.yOfPoint(faceIndex + 1));

	float x_difference = -6; // ball.get_xPos() - padd.xOfPoint(faceIndex + 1);
	float y_difference =  0;// ball.get_yPos() - padd.yOfPoint(faceIndex + 1);

	Vec2 r = Vec2(3, 2);
	Vec2 s = Vec2(-3, 2);

	//float x_cross = (x_difference * ball.get_radius() * (-normalizedY)) - (y_difference * ball.get_radius() * (-normalizedX));
	float x_cross = (y_difference * r.x - x_difference * r.y);
	//float depth = x_cross / (padd.xOfPoint(faceIndex) *ball.get_radius() * (-normalizedY) - padd.yOfPoint(faceIndex) * ball.get_radius() * (-normalizedX));
	float depth = x_cross / (r.x * s.y - r.y * s.x);

	std::cout << "cross: " << x_cross << std::endl;
	std::cout << "depth: " << depth << std::endl;
}

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


bool GameState::gameplayIsActive()
{
	return gameIsActive;
}