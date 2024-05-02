#pragma once
/* LIBRARY */
#include "platformCommon.h"
#include "variables.h"
#include "renderer.h"
#include <fstream>
#include <sqlite3.h>

/* MACROS */
#define isDown(button) input->buttons[button].isDown
#define isPressed(button) (input->buttons[button].isDown && input->buttons[button].changed)
#define isReleased(button) (!input->buttons[button].isDown && input->buttons[button].changed)
#define DATABASE "scores.txt"

/* CLASS Game*/
class Game {
	int score = 0;
	int order_number = 0;
	u64** table = nullptr;
	int mode = 4; // Default mode
	u64** prevTable = nullptr;
	Stack<u64*> gameStack;
public:
	void setScore(int score) { this->score = score; }
	int getScore() { return score; }
	void saveScore();
	int loadScoreAndGetMaxScore();
	void init();
	~Game();
	void addCell();
	void upMove();
	void downMove();
	void leftMove(); // It have bug must change later
	void rightMove(); // It have bug must change later
	bool isEqual();
	bool isOver();
	void setMode(int mode) { this->mode = mode; }
	int getMode() { return this->mode; }
	bool isTableNull() { return (this->table == nullptr) ? true : false; }
	void setPrevTable();
	bool isPrevTableNull() { return (this->prevTable == nullptr) ? true : false; }
	u64** getTable() { return this->table; }
	void newGame();
	void redo();
	void undo();
};

/* FUNCTION */;
void stimulateGameMenu(Input* input);
void stimulateGameIntro(Input* input);
void stimulateGamePlay(Input* input);
void stimulateGame(Input* input, float deltaTime);