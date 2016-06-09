#include "move.h"

MyPosition me;
GLint myfovy = 30;
GLint fovy_x = 0;
GLfloat Pi = 3.1415926536;
GLfloat mouse_prex, mouse_prey;

void fovy_control(int controller) {
	if(controller == 1) {
		myfovy = 40 / Pi * atan(0.3*fovy_x) + 30;
	}
	else if(controller == 0) {
		myfovy = 30;
	}
	if(fovy_x >= 40) {
		fovy_x = 40;
	}
	else if(fovy_x <= -40){
		fovy_x = -40;
	}
}
//�����λ���ƶ�
void MoveCamera(GLint forward, GLint leftright) {
	me.now_x = me.now_x + forward*me.lx*0.1 + leftright*me.lz*0.1;		//���������ĸı����ӽǷ���ǰ�������ƶ�ֵ�ڸ÷����ͶӰ����
	me.now_z = me.now_z + forward*me.lz*0.1 - leftright*me.lx*0.1;

	glLoadIdentity();
	gluLookAt(me.now_x, me.now_y, me.now_z, me.now_x + me.lx, me.y_rotate, me.now_z + me.lz, 0.0, 1.0, 0.0);
}
//λ�ư������˳�
void KeyProcess(unsigned char key, int x, int y) {
	GLfloat old_x = me.now_x;
	GLfloat old_z = me.now_z;

	switch(key) {
	case 'w':												//wasd����ǰ������ƶ�
		MoveCamera(5, 0); break;
	case 'a':
		MoveCamera(0, 5); break;
	case 's':
		MoveCamera(-5, 0); break;
	case 'd':
		MoveCamera(0, -5); break;
	case 'c':
		fovy_x -= 10; fovy_control(1); break;
	case 'x':
		fovy_x = 0;   fovy_control(0); break;
	case 'z':
		fovy_x += 10; fovy_control(1); break;
	case  27:
		exit(0); break;
	default: break;
	}

	for(int i = 0; i<size; i++) {
		for(int j = 0; j<size; j++) {
			if(gallery[i][j] == 1) {
				GLfloat gallery_pos_x = (GLfloat)j*10.0;
				GLfloat gallery_pos_z = (GLfloat)i*10.0;
				if(me.now_x>gallery_pos_x - 5.0 && me.now_x<gallery_pos_x + 5.0
					&& me.now_z>gallery_pos_z - 5.0 && me.now_z<gallery_pos_z + 5.0) {
					//printf("��ײǽ�ˣ���\n");
					me.now_x = old_x;
					me.now_z = old_z;
				}
			}
		}
	}
	glutPostRedisplay();
}
//�ӽǵ���ת
void RotateCamera(GLfloat ang) {							//�ƶ����ʱ���õ�ת���ӽǺ���
	me.lx = sin(ang);
	me.lz = -cos(ang);
	glLoadIdentity();
	gluLookAt(me.now_x, me.now_y, me.now_z, me.now_x + me.lx, me.now_y + me.ly, me.now_z + me.lz, 0.0, 1.0, 0.0);
}
//����ƶ�
void MouseMove(int xMouse, int yMouse) {
	ShowCursor(FALSE);

	me.y_rotate -= 0.01*(yMouse - mouse_prey);
	if(me.y_rotate>3.0) me.y_rotate = 3.0;
	else if(me.y_rotate<-1.0) me.y_rotate = -1.0;

	me.angle += (xMouse - mouse_prex) / 80;
	RotateCamera(me.angle);

	glutPostRedisplay();

	mouse_prex = xMouse;
	mouse_prey = yMouse;
}