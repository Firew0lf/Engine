#ifndef CAMERA_H
#define CAMERA_H

#define CAMERA_FPN_DIV 32

typedef struct {
	GLint posX;
	GLint posY;
	GLint posZ;
	GLshort yaw;
	GLshort pitch;
} camera_pos;

void camera_look(camera_pos eye);
void camera_move(camera_pos *eye, GLint x, GLint y, GLint z);
void camera_moved(camera_pos *eye, GLdouble x, GLdouble y, GLdouble z);

#endif
