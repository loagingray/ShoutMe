#ifndef mymap_h
#define mymap_h

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

const int size = 11;
const GLfloat room_h = 5.0;

extern int gallery[size][size];

extern GLuint maze_texture;
extern GLuint ground_texture;
extern GLuint ceiling_texture;

void myinit();													// 地图纹理的初始化
int LoadGLTextures(GLuint& myTexture, const char* chFileName);	// 载入位图并转换成纹理 
AUX_RGBImageRec *LoadBMP(char * Filename);						// 载入位图图象

void make_box();												//画一块墙壁
void draw_maze();												//画地图

void mylight();													//固定光源


#endif