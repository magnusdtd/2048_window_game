#include "utils.h"
#include "variables.h"

RenderState renderState;

void renderBackGround()
{
	u32* pixel = (u32*) renderState.memory;
	for (int y = 0; y < renderState.height; y++)
		for (int x = 0; x < renderState.width; x++)
			*pixel++ = x * y;
}

void clearScreen(u32 color)
{
	u32* pixel = (u32*) renderState.memory;
	for (int y = 0; y < renderState.height; y++)
		for (int x = 0; x < renderState.width; x++)
			*pixel++ = color;
}


void drawRectinPixels(int x0, int y0, int x1, int y1, u32 color)
{
	x0 = clamp(0, x0, renderState.width);
	x1 = clamp(0, x1, renderState.width);
	y0 = clamp(0, y0, renderState.height);
	y1 = clamp(0, y1, renderState.height);
	for (int y = y0; y < y1; y++)
	{
		u32* pixel = (u32*) renderState.memory + x0 + y * renderState.width;
		for (int x = x0; x < x1; x++)
			*pixel++ = color;
	}
}



void drawRect(double x, double y, double halfSizeX, double halfSizeY, u32 color)
{
	double renderScale = .5f;
	x *= renderState.height * renderScale;
	y *= renderState.height * renderScale;
	halfSizeX = renderState.height * renderScale;
	halfSizeY = renderState.height * renderScale;


	x += renderState.width / 2.f;
	y += renderState.height / 2.f;
	
	
	//Change to pixels
	int x0 = (int) x - halfSizeX;
	int x1 = (int) x + halfSizeX;
	int y0 = (int) y - halfSizeY;
	int y1 = (int) y + halfSizeY;

	drawRectinPixels(x0, y0, x1, y1, color);
}