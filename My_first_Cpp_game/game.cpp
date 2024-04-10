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

	// Create 2 cells at first
	int Ax = random(0, this->mode - 1), Ay = random(0, this->mode - 1), Bx = 0, By = 0;
	while (true) // Loop until A != B;
	{
		Bx = random(0, this->mode - 1);
		By = random(0, this->mode - 1);
		if (Ax != Bx && Ay != By)
			break;
	}

	this->table[Ax][Ay] = 2;
	this->table[Bx][By] = 2;
}
void Game::freeMemory()
{
	if (this->table == nullptr)
		return;
	for (int i = 0; i < MODE_2048; i++)
		delete[] this->table[i];
	delete[] this->table;

	this->table = nullptr;
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
		/*Half size should be 8 if MODE_5 is selected.
		Half size should be 10 if MODE_4 (default) is selected.*/
		if (the_2048.getMode() == MODE_5)
			drawTable(the_2048.getMode(), 8, 2, 0xB34670, 0x6683D5, the_2048.getTable(), 0xffffff);
		else
			drawTable(the_2048.getMode(), 10, 2, 0xB34670, 0x6683D5, the_2048.getTable(), 0xffffff);


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
			the_2048.setMode(MODE_4);
		}
		else
		{
			// draw "5x5" or "4x4" mode with different color.
			drawText("MODE FOUR", -80, -10, 1, 0xaaaaaa);
			drawText("MODE FIVE", 20, -10, 1, 0xff0000);
			the_2048.setMode(MODE_5);
		}

		drawNumber(2048, 47, 20, 7, 0x000000);
	}
}