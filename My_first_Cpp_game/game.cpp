/* LIBRARY */
#include "game.h"
#include "variables.h"
#include "renderer.h"

float playerPosX = 0.f;
float playerPosY = 0.f;
bool selectButton;
float arenaHalfSizeX = 85, arenaHalfSizeY = 45;

enum GameMode {
	GM_MENU,
	GM_GAMEPLAY,
};
GameMode currentGameMode = GM_MENU;

class Game {
	int score;
	int** a = nullptr;
private:
	void setScore(int score)
	{
		this->score = score;
	}
	int getScore()
	{
		return score;
	}
	void printTable()
	{

	}
	void saveScore()
	{

	}

};



/* FUNCTION */
void stimulateGame(Input* input, float deltaTime)
{
	/*clearScreen(0xffffff);*/
	drawArenaBorders(arenaHalfSizeX, arenaHalfSizeY, 0xffffff);
	//drawRect(0, 0, arenaHalfSizeX, arenaHalfSizeY, 0x30A7CA);
	ShowCursor(true);


	float speed = 50.f;

	if (currentGameMode == GM_GAMEPLAY) 
	{
		if (isDown(BUTTON_UP))
			playerPosX -= speed * deltaTime;
		if (isDown(BUTTON_DOWN))
			playerPosX += speed * deltaTime;
		if (isDown(BUTTON_RIGHT))
			playerPosY -= speed * deltaTime;
		if (isDown(BUTTON_LEFT))
			playerPosY += speed * deltaTime;


		drawTable(0x1277C4, MODE_4, 10, 2);

		drawRect(playerPosY, playerPosX, 1, 1, 0x00ff22);
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
			// draw "3x3" or "4x4" mode.
			drawText("SINGLE PLAYER", -80, -10, 1, 0xff0000);
			drawText("MULTIPLAYER", 20, -10, 1, 0xaaaaaa);
		}
		else
		{
			// draw "3x3" or "4x4" mode with different color.
			drawText("SINGLE PLAYER", -80, -10, 1, 0xaaaaaa);
			drawText("MULTIPLAYER", 20, -10, 1, 0xff0000);
		}

		drawNumber(2048, 47, 20, 7, 0x000000);
	}
}