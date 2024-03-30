#pragma once
/* This file store libaries, global variable and structs.
*/
#include <windows.h>

struct RenderState {
	void* memory;
	int width, height;
	BITMAPINFO bitmapInfo;

};


