#include "enemy.h"

const int enemy_num = 1;
const int hit_rate = 80;
Enemy enemy[enemy_num];

//初始化
void enemy_init() {
	enemy[0].now_x = 2 * 10.0, enemy[0].now_y = 0, enemy[0].now_z = 6 * 10.0;
	enemy[0].width = 1;
	draw_enemy(enemy[0]);
}

void draw_enemy(Enemy this_enemy) {
	glPushMatrix();
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	glTranslatef((float)this_enemy.now_x, 0.0, (float)this_enemy.now_z);
	if(!this_enemy.hit) glColor3f(1.0, 1.0, 0.0);
	else glColor3f(1.0, 0.0, 0.0);
	glutSolidSphere(this_enemy.width, 50, 50);
	glPopAttrib();
	glPopMatrix();
}

//射击判定
void if_hit_enemy() {
	double me_to_enemy_x, me_to_enemy_z;
	double length;
	double dot_product;
	double this_cos;
	double min_cos;
	int if_hit;
	srand((unsigned)time(NULL));
	//遍历所有的目标
	for(int i = 0; i < enemy_num; i++) {
		//目标与相机连线的向量
		me_to_enemy_x = enemy[i].now_x - me.now_x;
		me_to_enemy_z = enemy[i].now_z - me.now_z;
		//与目标的距离
		length = sqrt(me_to_enemy_x*me_to_enemy_x + me_to_enemy_z*me_to_enemy_z);

		//以下分别为点积， 此时的枪口与目标分别与相机连线的夹角的余弦，目标所占视角的余弦
		dot_product = me_to_enemy_x * me.lx + me_to_enemy_z* me.lz;
		this_cos = dot_product / length;
		min_cos = sqrt(length*length / (length*length + enemy[i].width*enemy[i].width));

		//如果射中了
		if_hit = (this_cos > min_cos || this_cos < -min_cos) && ((rand() % 100) < hit_rate);
		//(太远了会默认射不中)
		if(if_hit && length < 45) {
			enemy[i].hit = 1;
			draw_enemy(enemy[i]);
			me.score++;
		}
	}
}

void Mouse(int button, int state, int x, int y) {//处理鼠标点击
	if(state == GLUT_DOWN && button == GLUT_LEFT_BUTTON) {
		if_hit_enemy();
	}
}