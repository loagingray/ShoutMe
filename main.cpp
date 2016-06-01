#define FREEGLUT_STATIC
#define _CRT_SECURE_NO_DEPRECATE
//#pragma warning(disable:4996)
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
#include "mymap.h"
#include "move.h"
#include "enemy.h"

const int window_h = 1080;
const int window_w = 1920;

void draw_front_sight(void) {
	//-----------------------------------------
	//画准心
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-19.2, 19.2, -10.8, 10.8);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glPushAttrib(GL_ALL_ATTRIB_BITS);
	glBegin(GL_LINES);
	glColor3f(1.0, 0.0, 0.0);
	glVertex2f(-0.30, 0.0);
	glVertex2f(-0.10, 0.0);
	glVertex2f(0.10, 0.0);
	glVertex2f(0.30, 0.0);
	glVertex2f(-0.20, 0.1);
	glVertex2f(-0.05, 0.1);
	glVertex2f(0.05, 0.1);
	glVertex2f(0.20, 0.1);
	glVertex2f(-0.20, -0.1);
	glVertex2f(-0.05, -0.1);
	glVertex2f(0.05, -0.1);
	glVertex2f(0.20, -0.1);
	glEnd();

	glPointSize(3.0);
	glBegin(GL_POINTS);
	glVertex2f(0.0, 0.0);
	glEnd();

	glPopAttrib();
}

void display(void) {
	glShadeModel(GL_SMOOTH);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glClearColor(1.0, 1.0, 1.0, 0);
	draw_front_sight();		//准星

	//准备画地图
	glEnable(GL_DEPTH_TEST);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(30.0, (double)window_w / (double)window_h, 1.0, 100.0);
	//mylight();
	gluLookAt(me.now_x, me.now_y, me.now_z, me.now_x + me.lx, me.y_rotate, me.now_z + me.lz, 0.0, 1.0, 0.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//固定光照
	mylight();
	//地图
	draw_maze();
	//敌人1
	enemy_init();

	glutSwapBuffers();
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);
	glutCreateWindow("SM");
	glutFullScreen();
	myinit();
	glutDisplayFunc(display);
	glutKeyboardFunc(KeyProcess);
	glutPassiveMotionFunc(MouseMove);
	glutMouseFunc(Mouse);
	glutMotionFunc(MouseMove);
	glutMainLoop();
	return 0;
}
