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
	if (sfw::getKey('R'))
	{
		gameBall.set_xPos(400);
	}
	// Move Enemy paddle
	if (enemyPaddle.get_yPos() < gameBall.getPos().y)
	{
		enemyPaddle.moveUp(ceilingValue);
	}
	else if (enemyPaddle.get_yPos() - enemyPaddle.get_height() > gameBall.getPos().y)
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

	gameBall.setPos(gameBall.getPos() + gameBall.getVel());
}

void GameState::draw()
{
	sfw::drawTexture(playerPaddle.get_texture(), playerPaddle.get_xPos(), playerPaddle.get_yPos(), playerPaddle.get_width(), playerPaddle.get_height(), 0, false, 0, WHITE);
	sfw::drawTexture(enemyPaddle.get_texture(), enemyPaddle.get_xPos(), enemyPaddle.get_yPos(), enemyPaddle.get_width(), enemyPaddle.get_height(), 0, false, 0, RED);
	sfw::drawCircle(gameBall.getPos().x, gameBall.getPos().y, gameBall.get_radius(), 12, gameBall.get_color());

	sfw::drawTexture(background, 400, 300, 800, 600);
	//sfw::drawTexture(playerPaddle.get_texture(), playerPaddle.get_xPos(), playerPaddle.get_yPos(), playerPaddle.get_width(), playerPaddle.get_height(), 0, false, 0, CYAN);
	//sfw::drawTexture(enemyPaddle.get_texture(), enemyPaddle.get_xPos(), enemyPaddle.get_yPos(), enemyPaddle.get_width(), enemyPaddle.get_height(), 0, false, 0, RED);
	playerPaddle.drawPaddle();
	enemyPaddle.drawPaddle();

	sfw::drawCircle(gameBall.getPos().x, gameBall.getPos().y, gameBall.get_radius(), 12, gameBall.get_color());
	//sfw::drawTexture(gameBall.get_texture(), gameBall.get_xPos(), gameBall.get_yPos(), gameBall.get_radius(), gameBall.get_radius());
	sfw::drawLine(gameBall.getPos().x, gameBall.getPos().y, gameBall.get_xVel() + gameBall.getPos().x, gameBall.get_yVel() + gameBall.getPos().y, RED);
	sfw::drawString(font, std::to_string(playerPoints).c_str(), 0, 600, 48, 48, 0, ' ');
	//sfw::drawString(font, std::to_string(gameBall.get_xVel()).c_str(), 0, 600, 48, 48, 0, ' ');
	//sfw::drawString(font, std::to_string(gameBall.get_yVel()).c_str(), 0, 500, 48, 48, 0, ' ');
}

void GameState::boundaryCollisionController(Ball * ball, int ceilingVal, int floorVal)
{
	if (ball->getPos().x + gameBall.get_radius() > 800)
	{
		//playerPoints += 1;
		//gameBall.set_xVel(4);
		//gameBall.set_yVel(0);
		//gameBall.set_xPos(400);
		//gameBall.set_yPos(300);
		gameBall.set_xVel(-abs(gameBall.get_xVel()));
	}
	else if (ball->getPos().x < 0)
	{
		//gameIsActive = false;
		gameBall.set_xVel(abs(gameBall.get_xVel()));
	}

	if (ball->getPos().y + gameBall.get_radius() >= ceilingVal)
	{
		gameBall.set_yVel(-abs(ball->getVel().y));
		gameBall.set_yPos(gameBall.getPos().y - 10);
	}
	else if (ball->getPos().y - gameBall.get_radius() <= floorVal)
	{
		gameBall.set_yVel(abs(ball->getPos().y));
		gameBall.set_yPos(gameBall.getPos().y + 10);
	}
}

void GameState::paddleCollisionController(Paddle padd, Ball * ball)
{
	if (padd.collidedWithBall_Outer(ball->getPos(), ball->get_radius()))
	{
		vector<int> faces;
		faces = padd.facesOfCollision_Inner(ball->getPos(), ball->get_radius());
		std::cout << "faces.size(): " << faces.size() << std::endl;

		if (faces[0] != -1)
		{
			for (int ii = 0; ii < faces.size(); ++ii)
			{
				std::cout << "faces[" << ii << "]: " << faces[ii] << std::endl;
			}

			// Reflect the ball's vector
			//float oldX = ball->get_xVel(), oldY = ball->get_yVel();
			Vec2 oldVel = ball->getVel();

			for (int ii = 0; ii < faces.size(); ++ii)
			{
				std::cout << "face: " << faces[ii] << std::endl;

				std::cout << "ball y: " << ball->getPos().y << std::endl;
				// Get normal of plane
				Vec2 normalVec = normal(padd.perpVecOfFaceIndex(faces[ii]));

				std::cout << "ball->get_xVel(): " << ball->get_xVel() << std::endl;
				std::cout << "ball->get_yVel(): " << ball->get_yVel() << std::endl;
				Vec2 newVel = Vec2((ball->get_xVel() - (2.0 * (dot(oldVel, normalVec) * normalVec.x))),
								   (ball->get_yVel() - (2.0 * (dot(oldVel, normalVec) * normalVec.y))));

				std::cout << "dot(oldVel, normalVec): " << dot(oldVel, normalVec) << std::endl;
				std::cout << "normalVec.y: " << normalVec.y << std::endl;
				std::cout << "(dot(oldVel, normalVec) * normalVec.y): " << (dot(oldVel, normalVec) * normalVec.y) << std::endl;
				std::cout << "(2.0 * (dot(oldVel, normalVec) * normalVec.y)): " << (2.0 * (dot(oldVel, normalVec) * normalVec.y)) << std::endl;
				std::cout << "(oldVel.y - (2.0 * (dot(oldVel, normalVec) * normalVec.y))): " << (oldVel.y - (2.0 * (dot(oldVel, normalVec) * normalVec.y))) << std::endl;

				//oldVel.y - (2.0 * (dot(oldVel, normalVec) * normalVec.y)))

				ball->setVel(newVel);
				std::cout << "reflect xVel: " << ball->get_xVel() << std::endl;
				std::cout << "reflect yVel: " << ball->get_yVel() << std::endl;
				ball->set_yVel(ball->get_yVel() + padd.get_yVel());

				// Move ball out of paddle
				//moveBallOutsideOfPaddle(*ball, padd, 1);
				std::cout << "normalVec*15.0: " << (normalVec.y*15.0) << std::endl;
				ball->setPos(ball->getPos() + normalVec*15.0);
				std::cout << "ball y: " << ball->getPos().y << std::endl;

				std::cout << std::endl;
				std::cout << std::endl;
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

bool GameState::gameplayIsActive()
{
	return gameIsActive;
}