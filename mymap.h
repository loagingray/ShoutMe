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
#include <GL/glaux.h>// GLaux���ͷ�ļ� 
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

const int size = 11;
const GLfloat room_h = 5.0;

extern int gallery[size][size];

extern GLuint maze_texture;
extern GLuint ground_texture;
extern GLuint ceiling_texture;

void myinit();													// ��ͼ����ĳ�ʼ��
int LoadGLTextures(GLuint& myTexture, const char* chFileName);	// ����λͼ��ת�������� 
AUX_RGBImageRec *LoadBMP(char * Filename);						// ����λͼͼ��

void make_box();												//��һ��ǽ��
void draw_maze();												//����ͼ

void mylight();													//�̶���Դ


#endif