#include <stdlib.h>
#include <stdio.h>

#include <GL/gl.h>
#include <GL/glu.h>

#include "window.h"
#include "drawing3D.h"

void drawing2D_set(void) {
	glMatrixMode(GL_PROJECTION);
	//glDisable(GL_DEPTH_TEST);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(0.0, windowWidth, windowHeight, 0.0, -1.0, 10.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glDisable(GL_CULL_FACE);
	glClear(GL_DEPTH_BUFFER_BIT);
}

void drawing2D_stop(void) {
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_CULL_FACE);
}

void drawing2D_gray(void) {
	glDisable(GL_TEXTURE_2D);
	glColor4f(.0f, .0f, .0f, 0.5f);
	glBegin(GL_QUADS);
		glVertex2i(0, 0);
		glVertex2i(windowWidth, 0);
		glVertex2i(windowWidth, windowHeight);
		glVertex2i(0, windowHeight);
	glEnd();
	glColor4f(1.f, 1.f, 1.f, 1.f);
	glEnable(GL_TEXTURE_2D);
}
