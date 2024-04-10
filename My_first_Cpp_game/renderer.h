#pragma once
#include "RenderState.h"
#include "utils.h"

void renderBackGround();
void clearScreen(u32 color);
void drawRectinPixels(int x0, int y0, int x1, int y1, u32 color);
void drawRect(float x, float y, float halfSizeX, float halfSizeY, u32 color);
void drawArenaBorders(float arenaX, float arenaY, u32 color);
void drawNumber(int number, float x, float y, float size, u32 color);
void drawText(const char* text, float x, float y, float size, u32 color);
void drawTable(int mode, float half_size_of_each_cell, float distance_of_each_cell, u32 cell_color, u32 background_color, int** scores, u32 number_color);