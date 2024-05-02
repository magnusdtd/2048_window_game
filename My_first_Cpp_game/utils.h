#pragma once
#include <iostream>
typedef char s8;
typedef unsigned char u8;
typedef short s16;
typedef unsigned short u16;
typedef int s32;
typedef unsigned int u32;
typedef long long s64;
typedef unsigned long long u64;

const int MAXN = (int)2e5 + 1;
const long long INF = (long long)1e9;

template <typename T>
class Stack {
    T top;
    T a[MAXN];
public:
    Stack() { top = -1; }
    bool push(T x);
    T pop();
    bool isEmpty() { return (top < 0); }
};

int clamp(int min, int val, int max);
int random(int start, int end);