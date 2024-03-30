#pragma once
#include "RenderState.h"
#include "utils.h"

void renderBackGround();
void clearScreen(u32 color);
void drawRectinPixels(int x0, int y0, int x1, int y1, u32 color);
void drawRect(double x, double y, double halfSizeX, double halfSizeY, u32 color);