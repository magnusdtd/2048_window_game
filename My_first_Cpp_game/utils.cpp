#include "utils.h"

template <typename T>
bool Stack<T>::push(T x) {
    if (top >= (MAXN - 1))
        return false;
    else {
        a[++top] = x;
        return true;
    }
}
template <typename T>
T Stack<T>::pop() {
    if (top <= 0) {
        return -INF;
    }
    else {
        T x = a[top--];
        return x;
    }
}

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