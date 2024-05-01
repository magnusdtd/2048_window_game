#pragma once
/* LIBRARY */
#include "platformCommon.h"

/* MACROS */
#define isDown(button) input->buttons[button].isDown
#define isPressed(button) (input->buttons[button].isDown && input->buttons[button].changed)
#define isReleased(button) (!input->buttons[button].isDown && input->buttons[button].changed)

/* CLASS Game*/
class Game {
	int score = 0;
	int order_number = 0;
	int** table = nullptr;
	int mode = 4; // Default mode
	int** prevTable = nullptr;
public:
	void setScore(int score) { this->score = score; }
	int getScore() { return score; }
	void saveScore();
	void init();
	~Game();
	void addCell();
	void upMove();
	void downMove();
	void leftMove();
	void rightMove();
	bool isEqual();
	bool isOver();
	void setMode(int mode) { this->mode = mode; }
	int getMode() { return this->mode; }
	bool isTableNull() { return (this->table == nullptr) ? true : false; }
	void setPrevTable();
	bool isPrevTableNull() { return (this->prevTable == nullptr) ? true : false; }
	int** getTable() { return this->table; }
};

/* FUNCTION */;
void stimulateGameMenu(Input* input);
void stimulateGameIntro(Input* input);
void stimulateGamePlay(Input* input);
void stimulateGame(Input* input, float deltaTime);