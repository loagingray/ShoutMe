#include "mymap.h"

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

GLuint maze_texture;
GLuint ground_texture;
GLuint ceiling_texture;

// 载入位图图象
AUX_RGBImageRec *LoadBMP(char * Filename) { 
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
	int Status = FALSE;													// Status 状态指示器  
	AUX_RGBImageRec *TextureImage;										//保存贴图数据的指针
	char* file_name = (char*)chFileName;
	if(TextureImage = LoadBMP(file_name)) {								//载入贴图数据
		Status = 1;
		glGenTextures(1, &myTexture);									// 创建一个纹理，myTexture
		glBindTexture(GL_TEXTURE_2D, myTexture);						//绑定纹理，然后对该纹理区添加纹理数据
		// 生成纹理 
		glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage->sizeX, TextureImage->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage->data);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);//设置滤波为线性滤波
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);//线性滤波
		if(TextureImage) {												//释放资源
			if(TextureImage->data) {
				free(TextureImage->data);
			}
			free(TextureImage);
		}
	}
	return Status;
}

void myinit() {
	glClearColor(0.5f, 0.5f, 0.5f, 0.0f);
	glColor3f(1.0, 1.0, 1.0);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
	LoadGLTextures(maze_texture, "xiao.bmp");			//for maze
	LoadGLTextures(ground_texture, "ground.bmp");		//for ground
	LoadGLTextures(ceiling_texture, "ceiling.bmp");		//for ceiling
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

//这里将每面墙都画成了一个正方体，这样不论哪面墙都可以调用这个函数
void make_box() {
	glBindTexture(GL_TEXTURE_2D, maze_texture);        //使用贴图纹理
	glPushMatrix();
	glBegin(GL_QUADS);  //启用四边形带绘制模式绘制

	// 绘制前面，这里开始确定纹理坐标，然后是确定点的位置
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-room_h, -room_h, room_h);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(room_h, -room_h, room_h);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(room_h, room_h, room_h);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-room_h, room_h, room_h);


	// 绘制后面
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-room_h, -room_h, -room_h);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-room_h, room_h, -room_h);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(room_h, room_h, -room_h);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(room_h, -room_h, -room_h);


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
	glTexCoord2f(1.0f, 1.0f); glVertex3f(room_h, room_h, -room_h);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(room_h, room_h, room_h);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(room_h, -room_h, room_h);

	// 左面
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-room_h, -room_h, -room_h);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-room_h, -room_h, room_h);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-room_h, room_h, room_h);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-room_h, room_h, -room_h);

	glEnd();

	glPopMatrix();
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