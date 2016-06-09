#ifndef char_output_h
#define char_output_h

#define FREEGLUT_STATIC
#define _CRT_SECURE_NO_DEPRECATE
#pragma   comment(lib, "glaux.lib")

#ifdef _DEBUG
#pragma comment(lib, "freeglut_staticd.lib")
#else
#pragma comment(lib, "freeglut_static.lib")
#endif

#include <GL/freeglut.h>
#include <GL/glaux.h>// GLaux库的头文件 
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "move.h"
#define MAX_CHAR 128


void drawString(const char* str);

void displayString();

#endif