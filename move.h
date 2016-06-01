#ifndef move_h
#define move_h

#define FREEGLUT_STATIC
#define _CRT_SECURE_NO_DEPRECATE
#pragma comment(lib, "glaux.lib")

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
#include "mymap.h"

//我(相机)所在位置及属性的结构
struct MyPosition {
	GLfloat angle = 0.0;							//视角转动量
	GLfloat now_x = 10.0, now_y = 0, now_z = 10.0;	//位置
	GLfloat lx = 0.0, ly = 0.0, lz = 1.0;			//视角看向的地方的向量
	GLfloat y_rotate = 1.0;							//上下看
	int score = 0;									//我的得分
};

extern MyPosition me;

extern GLfloat Pi;
extern GLfloat mouse_prex, mouse_prey;


void MoveCamera(GLint forward, GLint leftright);	//相机的位置移动
void KeyProcess(unsigned char key, int x, int y);	//位移按键和退出
void RotateCamera(GLfloat ang);						//视角的旋转
void MouseMove(int xMouse, int yMouse);				//鼠标移动


#endif