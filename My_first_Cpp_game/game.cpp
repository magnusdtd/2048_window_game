/* LIBRARY */
#include "game.h"
#include "variables.h"
#include "renderer.h"

float playerPosX = 0.f;
float playerPosY = 0.f;

/* FUNCTION */
void stimulateGame(Input* input, float deltaTime)
{
	clearScreen(0xffffff);

	float speed = 5000.f;

	if (isPressed(BUTTON_UP))
		playerPosX -= speed * deltaTime;
	if (isPressed(BUTTON_DOWN))
		playerPosX += speed * deltaTime;
	if (isPressed(BUTTON_RIGHT))
		playerPosY -= speed * deltaTime;
	if (isPressed(BUTTON_LEFT))
		playerPosY += speed * deltaTime;
	
	drawRect(playerPosY, playerPosX, 1, 1, 0x00ff22);
	drawNumber(15, -10, 40, 1.f, 0x000000);
	//drawRect(-20, 20, 8, 3, 0xff2222);
}