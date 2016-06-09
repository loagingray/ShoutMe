#include "enemy.h"

const int enemy_num = 1;
const int hit_rate = 80;
Enemy enemy[enemy_num];
GLuint enemy_texture;

//��ʼ��
void enemy_init() {
	enemy[0].now_x = 2 * 10.0, enemy[0].now_y = 0, enemy[0].now_z = 6 * 10.0;
	enemy[0].width = 1;
	draw_enemy(enemy[0]);
}

void draw_enemy(Enemy this_enemy) {
	glPushMatrix();
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	glTranslatef((float)this_enemy.now_x, 0.0, (float)this_enemy.now_z);
	//if(!this_enemy.hit) glColor3f(1.0, 1.0, 0.0);
	//else glColor3f(1.0, 0.0, 0.0);
	glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP); //�������������Զ����ɼ�������ͼ����
	glEnable(GL_TEXTURE_GEN_S);
	glEnable(GL_TEXTURE_GEN_T);
	glEnable(GL_TEXTURE_2D);
	if (!this_enemy.hit)
	{
		//glEnable(GL_TEXTURE_2D);
		LoadGLTextures(enemy_texture, "test2.bmp");
		glBindTexture(GL_TEXTURE_2D, enemy_texture);
		glutSolidSphere(this_enemy.width, 50, 50);
	}
	else
	{
		//ʹ������ʧ
	}

	glPopAttrib();
	glPopMatrix();
}

//����ж�
void if_hit_enemy() {
	double me_to_enemy_x, me_to_enemy_z;
	double length;
	double dot_product;
	double this_cos;
	double min_cos;
	int if_hit;
	srand((unsigned)time(NULL));
	//�������е�Ŀ��
	for(int i = 0; i < enemy_num; i++) {
		//Ŀ����������ߵ�����
		me_to_enemy_x = enemy[i].now_x - me.now_x;
		me_to_enemy_z = enemy[i].now_z - me.now_z;
		//��Ŀ��ľ���
		length = sqrt(me_to_enemy_x*me_to_enemy_x + me_to_enemy_z*me_to_enemy_z);

		//���·ֱ�Ϊ����� ��ʱ��ǹ����Ŀ��ֱ���������ߵļнǵ����ң�Ŀ����ռ�ӽǵ�����
		dot_product = me_to_enemy_x * me.lx + me_to_enemy_z* me.lz;
		this_cos = dot_product / length;
		min_cos = sqrt(length*length / (length*length + enemy[i].width*enemy[i].width));

		//���������
		if_hit = (this_cos > min_cos || this_cos < -min_cos) && ((rand() % 100) < hit_rate);
		//(̫Զ�˻�Ĭ���䲻��)
		if(if_hit && length < 45) {
			enemy[i].hit = 1;
			draw_enemy(enemy[i]);
			me.score++;
		}
	}
}

void Mouse(int button, int state, int x, int y) {//���������
	if(state == GLUT_DOWN && button == GLUT_LEFT_BUTTON) {
		if_hit_enemy();
	}
}