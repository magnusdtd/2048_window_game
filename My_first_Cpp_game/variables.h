#pragma once
/*WARNING: carefull whenever you change this variable*/
//=======================//
#ifndef VARIABLES_H
#define VARIABLES_H
#include "RenderState.h"
#include "platformCommon.h"
#include "game.h"

extern bool running;
extern RenderState renderState;
extern Input input;
extern float renderScale;
extern int a[4][4];
extern Game the_2048;

#endif
//=====================//
