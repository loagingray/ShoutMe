#ifndef enemy_h
#define enemy_h

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
#include <time.h>			//为了设置随机数
#include "move.h"

//目标结构， 含目标的位置，宽度和是否打中的信息
struct Enemy{
	GLfloat now_x, now_y, now_z;
	GLfloat width;
	int hit = 0;
};

void draw_enemy(Enemy this_enemy);
void enemy_init();

void if_hit_enemy();
void Mouse(int button, int state, int x, int y);

#endif