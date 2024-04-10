#pragma once
/* LIBRARY */
#include "platformCommon.h"

/* MACROS */
#define isDown(button) input->buttons[button].isDown
#define isPressed(button) (input->buttons[button].isDown && input->buttons[button].changed)
#define isReleased(button) (!input->buttons[button].isDown && input->buttons[button].changed)
#define MODE_4 4
#define MODE_5 5

/* CLASS Game*/
class Game {
	int score;
	int order_number = 0;
	int** table = nullptr;
	int mode = 4;
public:
	void setScore(int score) { this->score = score; }
	int getScore() {return score;}
	void saveScore();
	void __init__();
	void freeMemory();
	void addCell();
	void upMove();
	void downMove();
	void leftMove();
	void rightMove();
	bool isEqual(int** temp);
	bool isOver();
	void setMode(int mode) { this->mode = mode; }
	int getMode() { return this->mode; }
	int** getTable() { return this->table; }
};

/* FUNCTION */
void __init__();
void stimulateGame(Input* input, float deltaTime);