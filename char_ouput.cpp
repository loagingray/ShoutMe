#include "char_output.h"

void drawString(const char* str) {
	static int isFirstCall = 1;
	static GLuint lists;

	if(isFirstCall) {
		isFirstCall = 0;
		lists = glGenLists(MAX_CHAR);

		wglUseFontBitmaps(wglGetCurrentDC(), 0, MAX_CHAR, lists);
	}
	
	while(*str != '\0') {
		glCallList(lists + *str);
		str++;
	}
}

void displayString() {
	char str[100];
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	glColor3f(0.0, 1.0, 0.0);
	sprintf(str, "Current Score: %d  Current Position: x = %f, z = %f", me.score, me.now_x, me.now_z);
	glRasterPos2f(7.0, 10.0);
	drawString(str);
	glPopAttrib();
}