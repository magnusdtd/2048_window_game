#pragma once

#ifndef _PLATFORMCOMMON_H_
#define _PLATFORMCOMMON_H_
struct ButtonScale
{
	bool isDown;
	bool changed;
};

enum
{
	BUTTON_UP,
	BUTTON_DOWN,
	BUTTON_LEFT,
	BUTTON_RIGHT,
	BUTTON_ENTER,
	BUTTON_ESCAPE,

	BUTTON_COUNT, // Should be the last item
};

struct Input
{
	ButtonScale buttons[BUTTON_COUNT];
};

#endif