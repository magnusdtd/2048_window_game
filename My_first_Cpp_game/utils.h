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

int clamp(int min, int val, int max);
int random(int start, int end);