/* LIBRARY */
#include "game.h"
#include "variables.h"
#include "renderer.h"

double playerPosX = 0.f;
double playerPosY = 0.f;

/* FUNCTION */
void stimulateGame(Input* input, double deltaTime)
{
	clearScreen(0xffffff);

	double speed = 50.f;

	if (isDown(BUTTON_UP))
		playerPosX -= speed * deltaTime;
	if (isDown(BUTTON_DOWN))
		playerPosX += speed * deltaTime;
	if (isDown(BUTTON_RIGHT))
		playerPosY -= speed * deltaTime;
	if (isDown(BUTTON_LEFT))
		playerPosY += speed * deltaTime;
	
	drawRect(playerPosY, playerPosX, 1, 1, 0x00ff22);
	//drawRect(-20, 20, 8, 3, 0xff2222);
}