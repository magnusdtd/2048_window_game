#include "lib.h"
#include "renderer.h"

void renderBackGround(RenderState renderState)
{
	unsigned int* pixel = (unsigned int*) renderState.memory;
	for (int y = 0; y < renderState.height; y++)
	{
		for (int x = 0; x < renderState.width; x++)
		{
			*pixel++ = x * y;
		}
	}
}