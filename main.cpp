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

const int window_h = 1080;
const int window_w = 1920;
const GLfloat room_h = 5.0;
const int size = 11;
const GLfloat Pi = 3.1415926536;
static GLfloat mouse_prex, mouse_prey;

GLuint maze_texture;
GLuint ground_texture;
GLuint ceiling_texture;

struct MyPosition {
	GLfloat angle = 0.0;
	GLfloat now_x = 10.0, now_y = 0, now_z = 10.0;
	GLfloat lx = 0.0, ly = 0.0, lz = 1.0;
	GLfloat y_rotate = 1.0;
} me;

struct Enemy {
	GLfloat now_x, now_y, now_z;
} enemy_1, enemy_2;


int gallery[size][size] = {
		{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
		{ 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1 },
		{ 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1 },
		{ 1, 0, 0, 1, 1, 1, 1, 1, 0, 0, 1 },
		{ 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1 },
		{ 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1 },
		{ 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1 },
		{ 1, 0, 0, 1, 0, 0, 1, 1, 0, 0, 1 },
		{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
		{ 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1 },
		{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }
};

AUX_RGBImageRec *LoadBMP(char * Filename) {// 载入位图图象 
	FILE *File = NULL;
	if(!Filename)
		return NULL;
	File = fopen(Filename, "r");
	if(File) {
		fclose(File);
		return auxDIBImageLoad(Filename);
	}
	return NULL;
}

// 载入位图(调用上面的代码)并转换成纹理 
int LoadGLTextures(GLuint& myTexture, const char* chFileName) {
	int Status = FALSE; // Status 状态指示器  
	AUX_RGBImageRec *TextureImage;										//保存贴图数据的指针
	char* file_name = (char*)chFileName;
	if(TextureImage = LoadBMP(file_name)) {					//载入贴图数据
		Status = 1;
		glGenTextures(1, &myTexture);										// 创建一个纹理，myTexture
		glBindTexture(GL_TEXTURE_2D, myTexture);							//绑定纹理，然后对该纹理区添加纹理数据
		// 生成纹理 
		glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage->sizeX, TextureImage->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage->data);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);		//设置滤波为线性滤波
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);		//线性滤波
		if(TextureImage) {													//释放资源
			if(TextureImage->data) {
				free(TextureImage->data);
			}
			free(TextureImage);
		}
	}
	return Status;
}

//这里将每面墙都画成了一个正方体，这样不论哪面墙都可以调用这个函数
void make_box() {
	glBindTexture(GL_TEXTURE_2D, maze_texture);        //使用贴图纹理
	glPushMatrix();
	glBegin(GL_QUADS);  //启用四边形带绘制模式绘制

	// 绘制前面，这里开始确定纹理坐标，然后是确定点的位置
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-room_h, -room_h, room_h);
	glTexCoord2f(1.0f, 0.0f); glVertex3f( room_h, -room_h, room_h);
	glTexCoord2f(1.0f, 1.0f); glVertex3f( room_h,  room_h, room_h);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-room_h,  room_h, room_h);


	// 绘制后面
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-room_h, -room_h, -room_h);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-room_h,  room_h, -room_h);
	glTexCoord2f(0.0f, 1.0f); glVertex3f( room_h,  room_h, -room_h);
	glTexCoord2f(0.0f, 0.0f); glVertex3f( room_h, -room_h, -room_h);


	//// 上面
	//glTexCoord2f(0.0f, 1.0f); glVertex3f(-room_h,  room_h, -room_h);
	//glTexCoord2f(0.0f, 0.0f); glVertex3f(-room_h,  room_h,  room_h);
	//glTexCoord2f(1.0f, 0.0f); glVertex3f( room_h,  room_h,  room_h);
	//glTexCoord2f(1.0f, 1.0f); glVertex3f( room_h,  room_h, -room_h);

	//  //底面

	//  glTexCoord2f(1.0f, 1.0f); glVertex3f(-room_h, -room_h, -room_h);
	//  glTexCoord2f(0.0f, 1.0f); glVertex3f( room_h, -room_h, -room_h);
	//  glTexCoord2f(0.0f, 0.0f); glVertex3f( room_h, -room_h,  room_h);
	//  glTexCoord2f(1.0f, 0.0f); glVertex3f(-room_h, -room_h,  room_h);

	// 右面
	glTexCoord2f(1.0f, 0.0f); glVertex3f(room_h, -room_h, -room_h);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(room_h,  room_h, -room_h);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(room_h,  room_h,  room_h);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(room_h, -room_h,  room_h);

	// 左面
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-room_h, -room_h, -room_h);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-room_h, -room_h,  room_h);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-room_h,  room_h,  room_h);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-room_h,  room_h, -room_h);

	glEnd();

	glPopMatrix();
}

void myinit() {
	glClearColor(0.5f, 0.5f, 0.5f, 0.0f);
	glColor3f(1.0, 1.0, 1.0);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
	//遍历的加载图片
	/*	for (int i = 0; i < 32; i++)
	{
	char temp1[10];
	char* temp2 = ".bmp";
	itoa(i + 1, temp1, 10);
	strcat(temp1, temp2);
	LoadGLTextures(maze_texture[i], temp1);            //载入纹理贴图
	}
	LoadGLTextures(maze_texture[39], "100.bmp");
	LoadGLTextures(maze_texture[38], "0.bmp");*/
	LoadGLTextures(maze_texture, "wenli.bmp");//for maze
	LoadGLTextures(ground_texture, "ground.bmp");//for ground
	LoadGLTextures(ceiling_texture, "ceiling.bmp");//for ceiling
}

void mylight() {
	GLfloat Va[] = { 0.3, 0.3, 0.3, 1.0 };
	GLfloat Vd[] = { 0.5, 0.5, 0.5, 1.0 };
	GLfloat Vs[] = { 0.8, 0.8, 0.8, 1.0 };
	//GLfloat Vp[] = { me.now_x, me.now_y, me.now_z, 1.0 };
	GLfloat Vp[] = { 10.0, 3.0, 10.0, 1.0 };

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);
	glLightfv(GL_LIGHT0, GL_AMBIENT, Va);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, Vd);
	glLightfv(GL_LIGHT0, GL_SPECULAR, Vs);
	glLightfv(GL_LIGHT0, GL_POSITION, Vp);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);
}

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
	glVertex2f( 0.10, 0.0);
	glVertex2f( 0.30, 0.0);
	glVertex2f(-0.20, 0.1);
	glVertex2f(-0.05, 0.1);
	glVertex2f( 0.05, 0.1);
	glVertex2f( 0.20, 0.1);
	glVertex2f(-0.20,-0.1);
	glVertex2f(-0.05,-0.1);
	glVertex2f( 0.05,-0.1);
	glVertex2f( 0.20,-0.1);
	glEnd();

	glPointSize(3.0);
	glBegin(GL_POINTS);
	glVertex2f(0.0, 0.0);
	glEnd();

	glPopAttrib();
}

void draw_enemy(Enemy this_enemy) {
	glPushMatrix();
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	glTranslatef((float)this_enemy.now_x*10.0, 0.0, (float)this_enemy.now_z*10.0);
	glColor3f(1.0, 1.0, 0.0);
	glutSolidSphere(1, 50, 50);
	glPopAttrib();
	glPopMatrix();
}

void draw_maze() {
	//---------------------------------------------------
	//画地面
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, ground_texture);
	glBegin(GL_QUADS);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(0, -room_h, 0);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(2 * size * room_h, -room_h, -2 * size * room_h);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(2 * size * room_h, -room_h, 2 * size * room_h);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-2 * size * room_h, -room_h, 2 * size * room_h);
	glEnd();
	glPopMatrix();

	//---------------------------------------------------
	//画天空
	glPushMatrix();
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	glBindTexture(GL_TEXTURE_2D, ceiling_texture);
	glBegin(GL_QUADS);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(0, room_h, 0);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(2 * size * room_h, room_h, -2 * size * room_h);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(2 * size * room_h, room_h, 2 * size * room_h);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-2 * size * room_h, room_h, 2 * size * room_h);
	glEnd();
	glPopAttrib();
	glPopMatrix();

	//---------------------------------------------------
	//画墙壁
	for(int i = 0; i<size; i++) {
		for(int j = 0; j<size; j++) {
			if(gallery[i][j] == 1) {
				glPushMatrix();
				glPushAttrib(GL_ALL_ATTRIB_BITS);
				glTranslatef((float)j*10.0f, 0.0f, (float)i*10.0f);
				make_box();
				glPopAttrib();
				glPopMatrix();
			}
		}
	}
}

void display(void) {
	glShadeModel(GL_SMOOTH); 
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glClearColor(1.0, 1.0, 1.0, 0);
	draw_front_sight();		//准星
	
	//-----------------------------------------
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
	//---------------------------------------------------
	//敌人1
	enemy_1.now_x = 2.0, enemy_1.now_y = 0.0, enemy_1.now_z = 7.0;
	draw_enemy(enemy_1);

	glutSwapBuffers();
}

void MoveCamera(GLint forward, GLint leftright) {
	me.now_x = me.now_x + forward*me.lx*0.1 + leftright*me.lz*0.1;		//相机的坐标的改变由视角方向前后左右移动值在该方向的投影决定
	me.now_z = me.now_z + forward*me.lz*0.1 - leftright*me.lx*0.1;

	glLoadIdentity();
	gluLookAt(me.now_x, me.now_y, me.now_z, me.now_x + me.lx, me.y_rotate, me.now_z + me.lz, 0.0, 1.0, 0.0);
}

void KeyProcess(unsigned char key, int x, int y) {
	GLfloat old_x = me.now_x;
	GLfloat old_z = me.now_z;

	switch(key) {
	case 'w':												//wasd控制前左后右移动
		MoveCamera(5, 0); break;
	case 'a':
		MoveCamera(0, 5); break;
	case 's':
		MoveCamera(-5, 0); break;
	case 'd':
		MoveCamera(0, -5); break;
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
					//printf("你撞墙了！！\n");
					me.now_x = old_x;
					me.now_z = old_z;
				}
			}
		}
	}
	glutPostRedisplay();
}

void RotateCamera(GLfloat ang) {							//移动鼠标时调用的转动视角函数
	me.lx = sin(ang);
	me.lz = -cos(ang);
	glLoadIdentity();
	gluLookAt(me.now_x, me.now_y, me.now_z, me.now_x + me.lx, me.now_y + me.ly, me.now_z + me.lz, 0.0, 1.0, 0.0);
}

void Mouse(int button, int state, int xMouse, int yMouse) {
	if(state == GLUT_UP)
		mouse_prex = xMouse, mouse_prey = yMouse;
}

void MouseMove(int xMouse, int yMouse) {
	ShowCursor(FALSE);

	me.y_rotate -= 0.01*(yMouse - mouse_prey);
	if(me.y_rotate>3.0) me.y_rotate = 3.0;
	else if(me.y_rotate<-1.0) me.y_rotate = -1.0;

	me.angle += (xMouse - mouse_prex) / 50;
	RotateCamera(me.angle);

	glutPostRedisplay();

	mouse_prex = xMouse;
	mouse_prey = yMouse;
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
	glutMotionFunc(MouseMove);
	glutMainLoop();
	return 0;
}
