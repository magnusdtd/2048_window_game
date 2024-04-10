/* LIBRARY */
#include "game.h"
#include "variables.h"
#include "renderer.h"
#include <iostream>
#include <fstream>

float playerPosX = 0.f;
float playerPosY = 0.f;
bool selectButton;
float arenaHalfSizeX = 85, arenaHalfSizeY = 45;
int a[4][4];
int MODE_2048 = 4;

enum GameMode {
	GM_MENU,
	GM_GAMEPLAY,
};
GameMode currentGameMode = GM_MENU;

void Game::saveScore()
{
	// Open output file and append the content to the current content of the file.
	std::fstream output;
	output.open("scores.txt", std::ios::app);
	if (!output.is_open()) {
		std::cerr << "Can't open output file\n";
		return;
	}
	output << this->order_number++ << ": " << this->score << "\n";
	output.close();

}
void Game::__init__()
{
	this->table = new int* [this->mode];
	for (int i = 0; i < this->mode; i++)
		this->table[i] = new int[this->mode];

	for (int i = 0; i < this->mode; i++)
		for (int j = 0; j < this->mode; j++)
			this->table[i][j] = 0;
}
void Game::freeMemory()
{
	if (this->table == nullptr)
		return;
	for (int i = 0; i < MODE_2048; i++)
		delete[] this->table[i];
	delete[] this->table;
}
void Game::addCell()
{
	int li, ri;
	while (true)
	{
		li = rand() % 4;
		ri = rand() % 4;
		if (this->table[li][ri] == 0)
		{
			a[li][ri] = 2;
			break;
		}
	}

}
void Game::upMove()
{

}
void Game::downMove()
{

}
void Game::leftMove()
{

}
void Game::rightMove()
{

}
int Game::isEqual()
{
	return 0;
}
bool Game::isOver()
{
	return 0;
}

Game the_2048;

/* FUNCTION */
void stimulateGame(Input* input, float deltaTime)
{
	drawArenaBorders(arenaHalfSizeX, arenaHalfSizeY, 0xffffff);
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

		/*Half size should be 8 if MODE_5 is selected.
		Half size should be 10 if MODE_4 is selected.*/
		drawTable(MODE_4, 10, 2, 0xB34670, 0x6683D5, a, 0xffffff);

		drawRect(playerPosY, playerPosX, 1, 1, 0x00ff22);


	} 
	else
	{
		if (isPressed(BUTTON_LEFT) || isPressed(BUTTON_RIGHT))
			selectButton = !selectButton;

		if (isPressed(BUTTON_ENTER))
		{
			the_2048.__init__();
			currentGameMode = GM_GAMEPLAY;
			// 
		}

		if (selectButton == 0) 
		{
			// draw "4x4" or "5x5" mode.
			drawText("MODE FOUR", -80, -10, 1, 0xff0000);
			drawText("MODE FIVE", 20, -10, 1, 0xaaaaaa);
			the_2048.setMode(4);
		}
		else
		{
			// draw "5x5" or "4x4" mode with different color.
			drawText("MODE FOUR", -80, -10, 1, 0xaaaaaa);
			drawText("MODE FIVE", 20, -10, 1, 0xff0000);
			the_2048.setMode(5);
		}

		drawNumber(2048, 47, 20, 7, 0x000000);
	}
}