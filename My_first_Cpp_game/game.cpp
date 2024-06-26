/* LIBRARY */
#include "game.h"

enum GameMode {
	MODE_3 = 3,
	MODE_4 = 4,
	MODE_5 = 5,
};
GameMode THE_2048_MODE = MODE_3;
const int NUMBEROFMODE = 3;
int selectButton = MODE_3 - NUMBEROFMODE;
const u32 numberOfCellColor = 15;
u32 cellColor[15] {	0x666699,
					0xff9900,
					0x993333,
					0xff0000,
					0xcc0066,
					0x990099,
					0xcc00ff,
					0x6600ff,
					0x000066,
					0x0066ff,
					0x00ccff,
					0x00cc99,
					0x33cc33,
					0x99ffcc,
					0xccffff };
enum GameState {
	GM_MENU,
	GM_INTRO,
	GM_GAMEPLAY,
};
GameState currentGameState = GM_MENU;
bool isSaveScore = false;
int maxScore = 0;
bool isSave = false;

void Game::saveScore()
{
	// Open output file and append the content to the current content of the file.
	std::fstream output;
	output.open(DATABASE, std::ios::app);
	if (!output.is_open()) {
		std::cerr << "Can't open output file\n";
		return;
	}
	output << this->order_number++ << ": " << this->score << "\n";
	output.close();
}
int Game::loadScoreAndGetMaxScore()
{
	std::fstream input;
	input.open(DATABASE, std::ios::in);
	
	int temp_k = 0, tempScore, max_score = -INT_MAX; std::string tempStr;
	while (!input.eof()) {
		input >> tempStr;
		input >> tempScore;
		temp_k++;
		if (tempScore > max_score) max_score = tempScore;
	}
	this->order_number = temp_k;
	return (max_score == -INT_MAX) ? 0 : max_score;
}
void Game::init()
{
	this->score = 0;
	this->table = new u64* [this->mode];
	for (int i = 0; i < this->mode; i++)
		this->table[i] = new u64[this->mode];

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
Game::~Game() {
	if (this->table != nullptr)
	{
		for (int i = 0; i < THE_2048_MODE; i++)
			delete[] this->table[i];
		delete[] this->table;
		this->table = nullptr;
	}
	if (this->prevTable != nullptr)
	{
		for (int i = 0; i < this->mode; i++)
			delete[] this->prevTable[i];
		delete[] this->prevTable;
		this->prevTable = nullptr;
	}
}
void Game::addCell()
{
	int li, ri, mode = this->getMode();
	while (true)
	{
		li = rand() % mode;
		ri = rand() % mode;
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
						// update score
						this->score++;
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
						// update score
						this->score++;
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
						// update score
						this->score++;
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
						// update score
						this->score++;
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
} // Change this when implement undo / redo
/*********************************************************************************************************************/
bool Game::isOver()
{
	int n = this->mode;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++) {
			if (this->table[i][j] == 0)
				return false;
			if (i == n - 1 && j == n - 1)
				continue;
			else if (i == n - 1) {
				if (this->table[i][j] == this->table[i][j + 1])
					return false;
			}
			else if (j == n - 1) {
				if (this->table[i][j] == this->table[i + 1][j])
					return false;
			}
			else {
				if (this->table[i + 1][j] == this->table[i][j] || this->table[i][j + 1] == this->table[i][j])
					return false;
			}
		}
	

	return true;
}
void Game::setPrevTable()
{
	this->prevTable = new u64* [this->mode];
	for (int i = 0; i < this->mode; i++)
		this->prevTable[i] = new u64[this->mode];

	for (int i = 0; i < this->mode; i++)
		for (int j = 0; j < this->mode; j++)
			this->prevTable[i][j] = this->table[i][j];
}
void Game::newGame() {
	if (this->table != nullptr)
	{
		for (int i = 0; i < THE_2048_MODE; i++)
			delete[] this->table[i];
		delete[] this->table;
		this->table = nullptr;
	}
	if (this->prevTable != nullptr)
	{
		for (int i = 0; i < this->mode; i++)
			delete[] this->prevTable[i];
		delete[] this->prevTable;
		this->prevTable = nullptr;
	}
}
void Game::redo() {

}
void Game::undo() {

}
Game the_2048;

/* FUNCTION */
void stimulateGameMenu(Input* input) {
	if (isPressed(BUTTON_UP))
		(selectButton += (NUMBEROFMODE - 1)) %= NUMBEROFMODE;
	else if (isPressed(BUTTON_DOWN))
		(selectButton += (NUMBEROFMODE + 1)) %= NUMBEROFMODE;

	if (isPressed(BUTTON_ENTER))
	{
		the_2048.init();
		maxScore = the_2048.loadScoreAndGetMaxScore();
		currentGameState = GM_INTRO;
	}

	if (selectButton == (MODE_3 - NUMBEROFMODE))
	{
		// draw "3x3", "4x4" or "5x5" mode.
		drawText("MODE THREE", -18, -5, 0.7, 0x0099ff);
		drawText("MODE FOUR", -18, -15, 0.7, 0x666699);
		drawText("MODE FIVE", -18, -25, 0.7, 0x666699);
		the_2048.setMode(MODE_3);
	}
	else if (selectButton == (MODE_4 - NUMBEROFMODE))
	{
		// draw "3x3", "4x4" or "5x5" mode with different color.
		drawText("MODE THREE", -18, -5, 0.7, 0x666699);
		drawText("MODE FOUR", -18, -15, 0.7, 0x0099ff);
		drawText("MODE FIVE", -18, -25, 0.7, 0x666699);
		the_2048.setMode(MODE_4);
	}
	else
	{
		// draw "3x3", "4x4" or "5x5" mode with different color.
		drawText("MODE THREE", -18, -5, 0.7, 0x666699);
		drawText("MODE FOUR", -18, -15, 0.7, 0x666699);
		drawText("MODE FIVE", -18, -25, 0.7, 0x0099ff);
		the_2048.setMode(MODE_5);
	}

	drawNumber(2048, 45, 20, 7, 0x000000);
}
void stimulateGameIntro(Input* input) {
	if (isPressed(BUTTON_ENTER))
	{
		currentGameState = GM_GAMEPLAY;
		return;
	}
	if (isPressed(BUTTON_BACK))
		currentGameState = GM_MENU;

	// Draw introduction
	drawNumber(2048, 10, 30, 2, random(0, 0xffffff));
	drawText("PRESS ESC TO EXIT", -50, 8, 0.5, 0x9933ff);
	drawText("USE ARROW TO PLAY GAME", -50, 0, 0.5, 0x9933ff);
	drawText("PRESS ENTER TO CONTINUE", -50, -8, 0.5, 0x9933ff);
	drawText("PRESS BACKSPACE TO PLAY AGAIN", -50, -16, 0.5, 0x9933ff);
	drawText("ENJOY IT", -20, -35, 1, random(0, 0xffffff));

}
void stimulateGamePlay(Input* input) 
{
	// Set previous array to preTable variable in Game class
	if (!the_2048.isTableNull())
		the_2048.setPrevTable();

	// Get user input LEFT, RIGHT, UP OR DOWN
	bool isGetInput = false;
	if (isPressed(BUTTON_LEFT))
	{
		the_2048.leftMove();
		isGetInput = true;
	}
	if (isPressed(BUTTON_RIGHT))
	{
		the_2048.rightMove();
		isGetInput = true;

	}
	if (isPressed(BUTTON_UP))
	{
		the_2048.upMove();
		isGetInput = true;

	}
	if (isPressed(BUTTON_DOWN))
	{
		the_2048.downMove();
		isGetInput = true;
	}

	/*Half size should be 8 if MODE_5 is selected.
	Half size should be 10 if MODE_4 (default) is selected.*/
	if (the_2048.getMode() == MODE_5)
		drawTable(MODE_5, 8, 2, cellColor, numberOfCellColor, 0x3366ff, the_2048.getTable(), 0xffffff);
	else if (the_2048.getMode() == MODE_4)
		drawTable(MODE_4, 10, 2, cellColor, numberOfCellColor, 0x3366ff, the_2048.getTable(), 0xffffff);
	else
		drawTable(MODE_3, 12, 2, cellColor, numberOfCellColor, 0x3366ff, the_2048.getTable(), 0xffffff);

	// Draw current score and maxScore in history
	drawText("SCORE", -80, 30, 0.8, 0xEB7527);
	drawNumber(the_2048.getScore(), -70, 20, 1.1, 0x0EC2F4);
	drawText("MAX SCORE", -90, 0, 0.8, 0xff3300);
	drawNumber(maxScore, -70, -10, 1.1, 0xff3300);

	// Check the game is lose or not. If lose, auto save score
	if (!the_2048.isTableNull())
	{
		if (the_2048.isOver())
		{
			drawText("YOU LOSE", 50, 10, 0.6, 0xff0000);
			drawText("SAVED SCORE", 50, 0, 0.6, 0x3366ff);
			if (!isSaveScore) 
			{
				the_2048.saveScore();
				maxScore = the_2048.getScore() > maxScore ? the_2048.getScore() : maxScore;
				isSaveScore = !isSaveScore;
			}
			if (isPressed(BUTTON_BACK))
			{
				currentGameState = GM_MENU;
				isGetInput = true;
			}
			return;
		}
	}

	/*************************************************************************************************************/
	// Check isEqual, must CHANGE THIS !!!
	if (!the_2048.isTableNull() && !the_2048.isPrevTableNull() && isGetInput)
		if (!the_2048.isEqual())
			the_2048.addCell();
	/*************************************************************************************************************/
	

	//  Press save score button
	if (isPressed(BUTTON_SAVE)) 
	{
		the_2048.saveScore();
		maxScore = the_2048.getScore() > maxScore ? the_2048.getScore() : maxScore;
		isGetInput = false;
		isSave = true;
	}
	if (isSave && !isGetInput)
		drawText("SAVED SCORE", 50, 0, 0.6, 0x3366ff);
	if (isGetInput)
		isSave = false;

	// New game
	if (isPressed(BUTTON_BACK))
	{
		currentGameState = GM_MENU;
		the_2048.newGame();
		isGetInput = true;
	}
}
void stimulateGame(Input* input, float deltaTime)
{
	clearScreen(0xffffff);
	ShowCursor(true);
	showCursorPosition();

	if (isPressed(BUTTON_ESCAPE))
	{
		VirtualFree(renderState.memory, 0, MEM_RELEASE);
		renderState.memory = nullptr;
		running = false;
		return;
	}
	
	/* GAMEPLAY MENU */
	if (currentGameState == GM_GAMEPLAY) 
		stimulateGamePlay(input);

	/* INTRO MENU */
	if (currentGameState == GM_INTRO)
		stimulateGameIntro(input);

	/* MAIN MENU */
	if (currentGameState == GM_MENU)
		stimulateGameMenu(input);
}
