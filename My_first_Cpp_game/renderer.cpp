#include "utils.h"
#include "variables.h"

RenderState renderState;
float renderScale;

void renderBackGround()
{
	u32* pixel = (u32*) renderState.memory;
	for (int y = 0; y < renderState.height; y++)
		for (int x = 0; x < renderState.width; x++)
			*pixel++ = x * y;
}

void clearScreen(u32 color)
{
	if (renderState.memory == nullptr)
		return;
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
		if (renderState.memory == nullptr)
			return;
		for (int x = x0; x < x1; x++)
			*pixel++ = color;
	}
}

void drawRect(float x, float y, float halfSizeX, float halfSizeY, u32 color)
{
	float renderScale = 0.01f;
	x *= renderState.height * renderScale;
	y *= renderState.height * renderScale;
	halfSizeX *= renderState.height * renderScale;
	halfSizeY *= renderState.height * renderScale;

	// Set x, y to O(0, 0)
	x += renderState.width / 2.f;
	y += renderState.height / 2.f;
	
	
	//Change to pixels
	int x0 = (int) x - (int) halfSizeX;
	int x1 = (int) x + (int) halfSizeX;
	int y0 = (int) y - (int) halfSizeY;
	int y1 = (int) y + (int) halfSizeY;

	drawRectinPixels(x0, y0, x1, y1, color);
}

/* Draw ten numbers from 0 to 9 */
void drawNumber(int number, float x, float y, float size, u32 color)
{
	float halfSize = size * .5f;

	bool drewNumber = false;
	while (number || !drewNumber) 
	{
		drewNumber = true;
		int digit = number % 10;
		number = number / 10;

		switch (digit) 
		{
			case 0: 
			{
				drawRect(x - size, y, halfSize, 2.5f * size, color);
				drawRect(x + size, y, halfSize, 2.5f * size, color);
				drawRect(x, y + size * 2.f, halfSize, halfSize, color);
				drawRect(x, y - size * 2.f, halfSize, halfSize, color);
				x -= size * 4.f;
			} break;

			case 1: 
			{
				drawRect(x + size, y, halfSize, 2.5f * size, color);
				x -= size * 2.f;
			} break;

			case 2: 
			{
				drawRect(x, y + size * 2.f, 1.5f * size, halfSize, color);
				drawRect(x, y, 1.5f * size, halfSize, color);
				drawRect(x, y - size * 2.f, 1.5f * size, halfSize, color);
				drawRect(x + size, y + size, halfSize, halfSize, color);
				drawRect(x - size, y - size, halfSize, halfSize, color);
				x -= size * 4.f;
			} break;

			case 3: 
			{
				drawRect(x - halfSize, y + size * 2.f, size, halfSize, color);
				drawRect(x - halfSize, y, size, halfSize, color);
				drawRect(x - halfSize, y - size * 2.f, size, halfSize, color);
				drawRect(x + size, y, halfSize, 2.5f * size, color);
				x -= size * 4.f;
			} break;

			case 4: 
			{
				drawRect(x + size, y, halfSize, 2.5f * size, color);
				drawRect(x - size, y + size, halfSize, 1.5f * size, color);
				drawRect(x, y, halfSize, halfSize, color);
				x -= size * 4.f;
			} break;

			case 5: 
			{
				drawRect(x, y + size * 2.f, 1.5f * size, halfSize, color);
				drawRect(x, y, 1.5f * size, halfSize, color);
				drawRect(x, y - size * 2.f, 1.5f * size, halfSize, color);
				drawRect(x - size, y + size, halfSize, halfSize, color);
				drawRect(x + size, y - size, halfSize, halfSize, color);
				x -= size * 4.f;
			} break;

			case 6: 
			{
				drawRect(x + halfSize, y + size * 2.f, size, halfSize, color);
				drawRect(x + halfSize, y, size, halfSize, color);
				drawRect(x + halfSize, y - size * 2.f, size, halfSize, color);
				drawRect(x - size, y, halfSize, 2.5f * size, color);
				drawRect(x + size, y - size, halfSize, halfSize, color);
				x -= size * 4.f;
			} break;

			case 7: 
			{
				drawRect(x + size, y, halfSize, 2.5f * size, color);
				drawRect(x - halfSize, y + size * 2.f, size, halfSize, color);
				x -= size * 4.f;
			} break;

			case 8: 
			{
				drawRect(x - size, y, halfSize, 2.5f * size, color);
				drawRect(x + size, y, halfSize, 2.5f * size, color);
				drawRect(x, y + size * 2.f, halfSize, halfSize, color);
				drawRect(x, y - size * 2.f, halfSize, halfSize, color);
				drawRect(x, y, halfSize, halfSize, color);
				x -= size * 4.f;
			} break;

			case 9: 
			{
				drawRect(x - halfSize, y + size * 2.f, size, halfSize, color);
				drawRect(x - halfSize, y, size, halfSize, color);
				drawRect(x - halfSize, y - size * 2.f, size, halfSize, color);
				drawRect(x + size, y, halfSize, 2.5f * size, color);
				drawRect(x - size, y + size, halfSize, halfSize, color);
				x -= size * 4.f;
			} break;
		}

	}
}

/* Define 28 letters to be used in drawTextFunction */
const char* letters[][7] =
{
	" 00",
	"0  0",
	"0  0",
	"0000",
	"0  0",
	"0  0",
	"0  0",

	"000",
	"0  0",
	"0  0",
	"000",
	"0  0",
	"0  0",
	"000",

	" 000",
	"0",
	"0",
	"0",
	"0",
	"0",
	" 000",

	"000",
	"0  0",
	"0  0",
	"0  0",
	"0  0",
	"0  0",
	"000",

	"0000",
	"0",
	"0",
	"000",
	"0",
	"0",
	"0000",

	"0000",
	"0",
	"0",
	"000",
	"0",
	"0",
	"0",

	" 000",
	"0",
	"0",
	"0 00",
	"0  0",
	"0  0",
	" 000",

	"0  0",
	"0  0",
	"0  0",
	"0000",
	"0  0",
	"0  0",
	"0  0",

	"000",
	" 0",
	" 0",
	" 0",
	" 0",
	" 0",
	"000",

	" 000",
	"   0",
	"   0",
	"   0",
	"0  0",
	"0  0",
	" 000",

	"0  0",
	"0  0",
	"0 0",
	"00",
	"0 0",
	"0  0",
	"0  0",

	"0",
	"0",
	"0",
	"0",
	"0",
	"0",
	"0000",

	"00 00",
	"0 0 0",
	"0 0 0",
	"0   0",
	"0   0",
	"0   0",
	"0   0",

	"00  0",
	"0 0 0",
	"0 0 0",
	"0 0 0",
	"0 0 0",
	"0 0 0",
	"0  00",

	"0000",
	"0  0",
	"0  0",
	"0  0",
	"0  0",
	"0  0",
	"0000",

	" 000",
	"0  0",
	"0  0",
	"000",
	"0",
	"0",
	"0",

	" 000 ",
	"0   0",
	"0   0",
	"0   0",
	"0 0 0",
	"0  0 ",
	" 00 0",

	"000",
	"0  0",
	"0  0",
	"000",
	"0  0",
	"0  0",
	"0  0",

	" 000",
	"0",
	"0 ",
	" 00",
	"   0",
	"   0",
	"000 ",

	"000",
	" 0",
	" 0",
	" 0",
	" 0",
	" 0",
	" 0",

	"0  0",
	"0  0",
	"0  0",
	"0  0",
	"0  0",
	"0  0",
	" 00",

	"0   0",
	"0   0",
	"0   0",
	"0   0",
	"0   0",
	" 0 0",
	"  0",

	"0   0 ",
	"0   0",
	"0   0",
	"0 0 0",
	"0 0 0",
	"0 0 0",
	" 0 0 ",

	"0   0",
	"0   0",
	" 0 0",
	"  0",
	" 0 0",
	"0   0",
	"0   0",

	"0   0",
	"0   0",
	" 0 0",
	"  0",
	"  0",
	"  0",
	"  0",

	"0000",
	"   0",
	"  0",
	" 0",
	"0",
	"0",
	"0000",

	"",
	"",
	"",
	"",
	"",
	"",
	"0",

	"   0",
	"  0",
	"  0",
	" 0",
	" 0",
	"0",
	"0",
};

/* Draw text to screen */
void drawText(const char* text, float x, float y, float size, u32 color) {
	float halfSize = size * .5f;
	float original_y = y;

	while (*text) {
		if (*text != 32) {
			const char** letter;
			if (*text == 47) letter = letters[27];
			else if (*text == 46) letter = letters[26];
			else letter = letters[*text - 'A'];
			float original_x = x;

			for (int i = 0; i < 7; i++) {
				const char* row = letter[i];
				while (*row) 
				{
					if (*row == '0')
						drawRect(x, y, halfSize, halfSize, color);
					x += size;
					row++;
				}
				y -= size;
				x = original_x;
			}
		}
		text++;
		x += size * 6.f;
		y = original_y;
	}
}


void drawTable(int mode, 
				float half_size_of_each_cell, 
				float distance_of_each_cell, 
				u32* cell_color, 
				u32 background_color, 
				const u32 number_of_cell_color, 
				int** scores, 
				u32 number_color)
{
	// Handle exception
	if (scores == nullptr)
		return;

	float x0, y0;
	// Fomula
	if (mode % 2 == 1) {
		x0 = -(half_size_of_each_cell 
			* (mode - 1) 
			+ distance_of_each_cell 
			* ((int) mode / 2));
		y0 = -x0;
	}
	else {
		x0 = -(half_size_of_each_cell 
			* (mode - 1) 
			+ 0.5f 
			* (mode - 2) 
			* distance_of_each_cell + 1);
		y0 = -x0;
	}
	// Draw background
	drawRect(0, 
			0, 
			-x0 + half_size_of_each_cell * 1.5f, 
			y0 + half_size_of_each_cell * 1.5f, 
			background_color);
	
	// Draw cells
	for (int i = 0; i < mode; i++) 
		for (int j = 0; j < mode; j++)
			drawRect(x0 + j * half_size_of_each_cell * 2.f + distance_of_each_cell * j, 
					y0 - i * half_size_of_each_cell * 2.f - distance_of_each_cell * i, 
					half_size_of_each_cell, 
					half_size_of_each_cell, 
					cell_color[(scores[i][j] == 0) ? 0 : ((u32)log2(scores[i][j]) % number_of_cell_color)]);


	// Draw number
	for (int i = 0; i < mode; i++)
		for (int j = 0; j < mode; j++)
			if (scores[i][j] != 0)
				drawNumber(scores[i][j], 
							x0 + j * half_size_of_each_cell * 2.f + distance_of_each_cell * j, 
							y0 - i * half_size_of_each_cell * 2.f - distance_of_each_cell * i, 
							1, 
							number_color);

}

void showCursorPosition() {
	POINT point;
	if (!GetCursorPos(&point))
	{
		drawNumber(point.x, point.x - 5, point.y - 5, 1, 0x3333ff);
		drawNumber(point.y, point.x - 3, point.y - 5, 1, 0x3333ff);
	}
}