#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include <GL/gl.h>
#include <GL/glu.h>

#include "camera.h"

#define radToDeg(a) a*(180.0/M_PI)
#define shortToRad(a) a*(M_PI/32768)

const GLfloat angleMult = (M_PI/pow(2,(sizeof(GLbyte)*8))/4); // 1/4 value = 1/4 turn

void camera_look(camera_pos eye) {
	GLdouble x = eye.posX/CAMERA_FPN_DIV;
	GLdouble y = eye.posY/CAMERA_FPN_DIV;
	GLdouble z = eye.posZ/CAMERA_FPN_DIV;
	GLdouble vx = cos(shortToRad(eye.pitch)) * cos(shortToRad(eye.yaw));
	GLdouble vy = sin(shortToRad(eye.pitch));
	GLdouble vz = cos(shortToRad(eye.pitch)) * sin(shortToRad(eye.yaw));
	gluLookAt(x, y, z, x+vx, y+vy, z+vz, 0.0, 1.0, 0.0);
}

void camera_move(camera_pos *eye,  GLint x, GLint y, GLint z) {
	eye->posX = x*CAMERA_FPN_DIV;
	eye->posY = y*CAMERA_FPN_DIV;
	eye->posZ = z*CAMERA_FPN_DIV;
}

void camera_movefpn(camera_pos *eye, GLint x, GLint y, GLint z) {
	eye->posX = x;
	eye->posY = y;
	eye->posZ = z;
}

void camera_moved(camera_pos *eye, GLdouble x, GLdouble y, GLdouble z) {
	eye->posX = (GLint)(x*CAMERA_FPN_DIV);
	eye->posY = (GLint)(y*CAMERA_FPN_DIV);
	eye->posZ = (GLint)(z*CAMERA_FPN_DIV);
}
