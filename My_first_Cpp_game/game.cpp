/* LIBRARY */
#include "game.h"
#include "variables.h"
#include "renderer.h"

float playerPosX = 0.f;
float playerPosY = 0.f;
int TableSize;
bool selectButton;
float arenaHalfSizeX = 85, arenaHalfSizeY = 45;

enum GameMode {
	GM_MENU,
	GM_GAMEPLAY,
};

GameMode currentGameMode = GM_MENU;

/* FUNCTION */
void stimulateGame(Input* input, float deltaTime)
{
	/*clearScreen(0xffffff);*/
	drawArenaBorders(arenaHalfSizeX, arenaHalfSizeY, 0xffffff);
	//drawRect(0, 0, arenaHalfSizeX, arenaHalfSizeY, 0x30A7CA);
	ShowCursor(true);


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
			// 
		}

		if (selectButton == 0) 
		{
			drawText("SINGLE PLAYER", -80, -10, 1, 0xff0000);
			drawText("MULTIPLAYER", 20, -10, 1, 0xaaaaaa);
		}
		else
		{
			drawText("SINGLE PLAYER", -80, -10, 1, 0xaaaaaa);
			drawText("MULTIPLAYER", 20, -10, 1, 0xff0000);
		}

		drawNumber(2048, 47, 20, 7, 0x000000);
	}
}