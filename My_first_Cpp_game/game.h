#pragma once
/* LIBRARY */
#include "platformCommon.h"

/* MACROS */
#define isDown(b) input->buttons[b].isDown
#define isPressed(b) (input->buttons[b].isDown && input->buttons[b].changed)
#define isReleased(b) (!input->buttons[b].isDown && input->buttons[b].changed)

/* FUNCTION */
void stimulateGame(Input* input, double deltaTime);