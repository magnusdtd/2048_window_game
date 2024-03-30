#pragma once

#ifndef _RENDERSTATE_H_
#define _RENDERSTATE_H_
#include "windows.h"
struct RenderState {
	void* memory;
	int width, height;
	BITMAPINFO bitmapInfo;

};

#endif