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
#include <GL/glaux.h>// GLaux���ͷ�ļ� 
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "mymap.h"

//��(���)����λ�ü����ԵĽṹ
struct MyPosition {
	GLfloat angle = 0.0;							//�ӽ�ת����
	GLfloat now_x = 10.0, now_y = 0, now_z = 10.0;	//λ��
	GLfloat lx = 0.0, ly = 0.0, lz = 1.0;			//�ӽǿ���ĵط�������
	GLfloat y_rotate = 1.0;							//���¿�
	int score = 0;									//�ҵĵ÷�
};

extern GLint myfovy;
extern MyPosition me;

extern GLfloat Pi;
extern GLfloat mouse_prex, mouse_prey;


void MoveCamera(GLint forward, GLint leftright);	//�����λ���ƶ�
void KeyProcess(unsigned char key, int x, int y);	//λ�ư������˳�
void RotateCamera(GLfloat ang);						//�ӽǵ���ת
void MouseMove(int xMouse, int yMouse);				//����ƶ�


#endif