#include "utils.h"

int clamp(int min, int val, int max)
{
	if (val < min)  return min;
	if (val > max) return max;
	return val;
}

int random(int start, int end)
{
	return start + rand() % (end - start + 1);
}