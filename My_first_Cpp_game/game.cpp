/* LIBRARY */
#include "game.h"
#include "variables.h"
#include "renderer.h"

float playerPosX = 0.f;
float playerPosY = 0.f;
int TableSize;
bool selectButton;
enum GameMode {
	GM_MENU,
	GM_GAMEPLAY,
};

GameMode currentGameMode = GM_MENU;

/* FUNCTION */
void stimulateGame(Input* input, float deltaTime)
{
	clearScreen(0xffffff);

	float speed = 5000.f;

	if (currentGameMode == GM_GAMEPLAY) 
	{
		if (isPressed(BUTTON_UP))
			playerPosX -= speed * deltaTime;
		if (isPressed(BUTTON_DOWN))
			playerPosX += speed * deltaTime;
		if (isPressed(BUTTON_RIGHT))
			playerPosY -= speed * deltaTime;
		if (isPressed(BUTTON_LEFT))
			playerPosY += speed * deltaTime;

		drawRect(playerPosY, playerPosX, 1, 1, 0x00ff22);
		drawNumber(115, -10, 40, 5.f, 0xbbffbb);
	} 
	else
	{
		if (isPressed(BUTTON_LEFT) || isPressed(BUTTON_RIGHT))
			selectButton = !selectButton;

		if (isPressed(BUTTON_ENTER))
		{
			currentGameMode = GM_GAMEPLAY;

		}

		if (selectButton == 0) 
		{
			drawRect(20, 0, 10, 10, 0xff0000);
			drawRect(-20, 0, 10, 10, 0xaaaaaa);
		}
		else
		{
			drawRect(20, 0, 10, 10, 0xaaaaaa);
			drawRect(-20, 0, 10, 10, 0xff0000);
		}
	}
}