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

// ����λͼͼ��
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

// ����λͼ(��������Ĵ���)��ת�������� 
int LoadGLTextures(GLuint& myTexture, const char* chFileName) {
	int Status = FALSE;													// Status ״ָ̬ʾ��  
	AUX_RGBImageRec *TextureImage;										//������ͼ���ݵ�ָ��
	char* file_name = (char*)chFileName;
	if(TextureImage = LoadBMP(file_name)) {								//������ͼ����
		Status = 1;
		glGenTextures(1, &myTexture);									// ����һ������myTexture
		glBindTexture(GL_TEXTURE_2D, myTexture);						//������Ȼ��Ը������������������
		// �������� 
		glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage->sizeX, TextureImage->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage->data);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);//�����˲�Ϊ�����˲�
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);//�����˲�
		if(TextureImage) {												//�ͷ���Դ
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
	//������
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
	//�����
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
	//��ǽ��
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

//���ｫÿ��ǽ��������һ�������壬������������ǽ�����Ե����������
void make_box() {
	glBindTexture(GL_TEXTURE_2D, maze_texture);        //ʹ����ͼ����
	glPushMatrix();
	glBegin(GL_QUADS);  //�����ı��δ�����ģʽ����

	// ����ǰ�棬���￪ʼȷ���������꣬Ȼ����ȷ�����λ��
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-room_h, -room_h, room_h);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(room_h, -room_h, room_h);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(room_h, room_h, room_h);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-room_h, room_h, room_h);


	// ���ƺ���
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-room_h, -room_h, -room_h);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-room_h, room_h, -room_h);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(room_h, room_h, -room_h);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(room_h, -room_h, -room_h);


	//// ����
	//glTexCoord2f(0.0f, 1.0f); glVertex3f(-room_h,  room_h, -room_h);
	//glTexCoord2f(0.0f, 0.0f); glVertex3f(-room_h,  room_h,  room_h);
	//glTexCoord2f(1.0f, 0.0f); glVertex3f( room_h,  room_h,  room_h);
	//glTexCoord2f(1.0f, 1.0f); glVertex3f( room_h,  room_h, -room_h);

	//  //����

	//  glTexCoord2f(1.0f, 1.0f); glVertex3f(-room_h, -room_h, -room_h);
	//  glTexCoord2f(0.0f, 1.0f); glVertex3f( room_h, -room_h, -room_h);
	//  glTexCoord2f(0.0f, 0.0f); glVertex3f( room_h, -room_h,  room_h);
	//  glTexCoord2f(1.0f, 0.0f); glVertex3f(-room_h, -room_h,  room_h);

	// ����
	glTexCoord2f(1.0f, 0.0f); glVertex3f(room_h, -room_h, -room_h);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(room_h, room_h, -room_h);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(room_h, room_h, room_h);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(room_h, -room_h, room_h);

	// ����
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