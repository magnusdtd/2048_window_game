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

	for (int i = 0; i < this->mode; i++)
		delete[] this->prevTable[i];
	delete[] this->prevTable;

	this->table = nullptr;
	this->prevTable = nullptr;
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
			this->table[li][ri] = 2;
			break;
		}
	}

}
void Game::upMove()
{
	int li, ri;
	for (int j = 0; j < this->mode; j++)
	{
		li = 0; ri = j;
		for (int i = 1; i < this->mode; i++)
		{
			if (this->table[i][j] != 0)
			{
				if (this->table[i - 1][j] == 0 || this->table[i - 1][j] == this->table[i][j])
				{
					if (this->table[li][ri] == this->table[i][j])
					{
						this->table[li][ri] *= 2;
						this->table[i][j] = 0;
					}
					else if (this->table[li][ri] == 0)
					{
						this->table[li][ri] = this->table[i][j];
						this->table[i][j] = 0;
					}
					else
					{
						this->table[++li][ri] = this->table[i][j];
						this->table[i][j] = 0;
					}
				}
				else li++;
			}
		}
	}
}
void Game::downMove()
{ 
	int li, ri;
	for (int j = 0; j < this->mode; j++)
	{
		li = this->mode - 1, ri = j;
		for (int i = this->mode - 2; i >= 0; i--)
		{
			if (this->table[i][j] != 0)
			{
				if (this->table[i + 1][j] == 0 || this->table[i + 1][j] == this->table[i][j])
				{
					if (this->table[li][ri] == this->table[i][j])
					{
						this->table[li][ri] *= 2;
						this->table[i][j] = 0;
					}
					else
					{
						if (this->table[li][ri] == 0)
						{
							this->table[li][ri] = this->table[i][j];
							this->table[i][j] = 0;
						}
						else
						{
							this->table[--li][ri] = this->table[i][j];
							this->table[i][j] = 0;
						}
					}
				}
				else li--;
			}
		}
	}
}
void Game::leftMove()
{
	int li, ri;
	for (int i = 0; i < this->mode; i++)
	{
		li = i, ri = 0;
		for (int j = 1; j < this->mode; j++)
		{
			if (this->table[i][j] != 0)
			{
				if (this->table[i][j - 1] == 0 || this->table[i][j - 1] == this->table[i][j])
				{
					if (this->table[li][ri] == this->table[i][j])
					{
						this->table[li][ri] *= 2;
						this->table[i][j] = 0;
					}
					else
					{
						if (this->table[li][ri] == 0)
						{
							this->table[li][ri] = this->table[i][j];
							this->table[i][j] = 0;
						}
						else
						{
							this->table[li][++ri] = this->table[i][j];
							this->table[i][j] = 0;
						}
					}
				}
				else ri++;
			}
		}
	}
}
void Game::rightMove()
{
	int li, ri;
	for (int i = 0; i < this->mode; i++)
	{
		li = i, ri = this->mode - 1;
		for (int j = this->mode - 2; j >= 0; j--)
		{
			if (this->table[i][j] != 0)
			{
				if (this->table[i][j + 1] == 0 || this->table[i][j + 1] == this->table[i][j])
				{
					if (this->table[li][ri] == this->table[i][j])
					{
						this->table[li][ri] *= 2;
						this->table[i][j] = 0;
					}
					else
					{
						if (this->table[li][ri] == 0)
						{
							this->table[li][ri] = this->table[i][j];
							this->table[i][j] = 0;
						}
						else
						{
							this->table[li][--ri] = this->table[i][j];
							this->table[i][j] = 0;
						}
					}
				}
				else ri--;
			}
		}
	}
}
/*********************************************************************************************************************/
bool Game::isEqual()
{
	for (int i = 0; i < this->mode; i++)
		for (int j = 0; j < this->mode; j++)
			if (this->prevTable[i][j] != this->table[i][j])
				return false;
	return true;
}
/*********************************************************************************************************************/
bool Game::isOver()
{

	bool flag1 = false, flag2 = false;
	for (int i = 0; i < this->mode; i++)
		for (int j = 0; j < this->mode; j++)
			if (this->table[i][j] == 0)
			{
				flag1 = true;
				break;
			}

	for (int i = 0; i < this->mode - 1; i++)
		for (int j = 0; j < this->mode - 1; j++)
			if (this->table[i + 1][j] == this->table[i][j] || this->table[i][j + 1] == this->table[i][j])
			{
				flag2 = true;
				break;
			}

	if (flag1 || flag2)
		return false;
	return true;
}
void Game::setPrevTable()
{
	this->prevTable = new int* [this->mode];
	for (int i = 0; i < this->mode; i++)
		this->prevTable[i] = new int[this->mode];

	for (int i = 0; i < this->mode; i++)
		for (int j = 0; j < this->mode; j++)
			this->prevTable[i][j] = this->table[i][j];
}

Game the_2048;

/* FUNCTION */
void stimulateGame(Input* input, float deltaTime)
{
	clearScreen(0xffffff);
	ShowCursor(true);

	if (isPressed(BUTTON_ESCAPE))
	{
		VirtualFree(renderState.memory, 0, MEM_RELEASE);
		renderState.memory = nullptr;
		the_2048.freeMemory();
		running = false;
		return;
	}
	

	if (currentGameMode == GM_GAMEPLAY) 
	{
		// Set previous array to preTable variable in Game class
		if (!the_2048.isTableNull())
			the_2048.setPrevTable();

		// Get user input LEFT, RIGHT, UP OR DOWN
		bool getInput = false;
		if (isPressed(BUTTON_LEFT)) 
		{
			the_2048.leftMove();
			getInput = true;
		}
		if (isPressed(BUTTON_RIGHT)) 
		{
			the_2048.rightMove();
			getInput = true;

		}
		if (isPressed(BUTTON_UP))
		{
			the_2048.upMove();
			getInput = true;

		}
		if (isPressed(BUTTON_DOWN))
		{
			the_2048.downMove();
			getInput = true;
		}

		
		/*************************************************************************************************************/
		// Check isEqual, must CHANGE THIS !!!
		if (!the_2048.isTableNull() && !the_2048.isPrevTableNull() && getInput)
			if (!the_2048.isEqual())
				the_2048.addCell();
		/*************************************************************************************************************/


		/*Half size should be 8 if MODE_5 is selected.
		Half size should be 10 if MODE_4 (default) is selected.*/
		if (the_2048.getMode() == MODE_5)
			drawTable(the_2048.getMode(), 8, 2, 0xB34670, 0x6683D5, the_2048.getTable(), 0xffffff);
		else
			drawTable(the_2048.getMode(), 10, 2, 0xB34670, 0x6683D5, the_2048.getTable(), 0xffffff);

		// Check the game is lose or not
		if (!the_2048.isTableNull())
		{
			if (the_2048.isOver())
			{
				drawText("YOU LOSE", -10, -10, 1, 0xf401e0);
				return;
			}
		}
	} 
	else
	{
		if (isPressed(BUTTON_LEFT) || isPressed(BUTTON_RIGHT))
			selectButton = !selectButton;

		if (isPressed(BUTTON_ENTER))
		{
			the_2048.__init__();
			currentGameMode = GM_GAMEPLAY;
		}

		if (selectButton == 0) 
		{
			// draw "4x4" or "5x5" mode.
			drawText("MODE FOUR", -70, -10, 1, 0xff0000);
			drawText("MODE FIVE", 10, -10, 1, 0xaaaaaa);
			the_2048.setMode(MODE_4);
		}
		else
		{
			// draw "5x5" or "4x4" mode with different color.
			drawText("MODE FOUR", -70, -10, 1, 0xaaaaaa);
			drawText("MODE FIVE", 10, -10, 1, 0xff0000);
			the_2048.setMode(MODE_5);
		}

		drawNumber(2048, 47, 20, 7, 0x000000);
	}
}