#include "game.h"
#include "variables.h"
#include "renderer.h"

void stimulateGame(Input* input)
{
	clearScreen(0xff5500);
	if (input->buttons[BUTTON_UP].isDown)
		drawRect(.01, .5, .5, .5, 0x00ff22);
	drawRect(.15, .5, .2, .2, 0xff0000);
}