/* LIBRARY */
#include "game.h"
#include "variables.h"
#include "renderer.h"

double playerPosX = 0.f;
double playerPosY = 0.f;

/* FUNCTION */
void stimulateGame(Input* input)
{
	clearScreen(0xffffff);
	if (isPressed(BUTTON_UP))
		playerPosX += 0.5f;
	if (isPressed(BUTTON_DOWN))
		playerPosX -= 0.5f;
	if (isPressed(BUTTON_RIGHT))
		playerPosY += 0.5f;
	if (isPressed(BUTTON_LEFT))
		playerPosY -= 0.5f;
	
	drawRect(playerPosY, playerPosX, 1, 1, 0x00ff22);
	//drawRect(-20, 20, 8, 3, 0xff2222);
}