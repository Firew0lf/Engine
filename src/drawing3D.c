#include <stdio.h>
#include <stdlib.h>

#include <GL/gl.h>
#include <GL/glu.h>

#include "main.h"
#include "log.h"
#include "drawing3D.h"
#include "window.h"
#include "blocks.h"

const int fpsMax = 60;

GLfloat fov = 90.0f;

void drawing3D_waitForVBlank(void) {
	
}

// renders
void drawing3D_block(int id, int x, int y, int z) {
	float fx = (float)x;
	float fy = (float)y;
	float fz = (float)z;
	
	glBegin(GL_QUADS);
		/* Front Face */
		glBindTexture(GL_TEXTURE_2D, blocks_get(id)->textures[FACE_FRONT]);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(fx-0.5f, fy-0.5f, fz+0.5f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(fx+0.5f, fy-0.5f, fz+0.5f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(fx+0.5f, fy+0.5f, fz+0.5f);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(fx-0.5f, fy+0.5f, fz+0.5f);

		/* Back Face */
		glBindTexture(GL_TEXTURE_2D, blocks_get(id)->textures[FACE_BACK]);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(fx-0.5f, fy-0.5f, fz-0.5f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(fx-0.5f, fy+0.5f, fz-0.5f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(fx+0.5f, fy+0.5f, fz-0.5f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(fx+0.5f, fy-0.5f, fz-0.5f);

		/* Top Face */
		glBindTexture(GL_TEXTURE_2D, blocks_get(id)->textures[FACE_TOP]);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(fx-0.5f, fy+0.5f, fz-0.5f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(fx-0.5f, fy+0.5f, fz+0.5f);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(fx+0.5f, fy+0.5f, fz+0.5f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(fx+0.5f, fy+0.5f, fz-0.5f);

		/* Bottom Face */
		glBindTexture(GL_TEXTURE_2D, blocks_get(id)->textures[FACE_BOTTOM]);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(fx-0.5f, fy-0.5f, fz-0.5f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(fx+0.5f, fy-0.5f, fz-0.5f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(fx+0.5f, fy-0.5f, fz+0.5f);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(fx-0.5f, fy-0.5f, fz+0.5f);

		/* Right face */
		glBindTexture(GL_TEXTURE_2D, blocks_get(id)->textures[FACE_RIGHT]);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(fx+0.5f, fy-0.5f, fz-0.5f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(fx+0.5f, fy+0.5f, fz-0.5f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(fx+0.5f, fy+0.5f, fz+0.5f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(fx+0.5f, fy-0.5f, fz+0.5f);

		/* Left Face */
		glBindTexture(GL_TEXTURE_2D, blocks_get(id)->textures[FACE_LEFT]);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(fx-0.5f, fy-0.5f, fz-0.5f);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(fx-0.5f, fy-0.5f, fz+0.5f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(fx-0.5f, fy+0.5f, fz+0.5f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(fx-0.5f, fy+0.5f, fz-0.5f);
	glEnd();
}

/*
Mask:
	LSB: Front
	2  : Back
	4  : Top
	8  : Bottom
	16 : Right
	32 : Left
	64 : -
	MSB: set to disable backface culling
*/
void drawing3D_blockMasked(int id, int x, int y, int z, char mask) {
	float fx = (float)x;
	float fy = (float)y;
	float fz = (float)z;
	
	if (mask&128)
		glDisable(GL_CULL_FACE);
	
	glBegin(GL_QUADS);
		/* Front Face */
		if (mask&1) {
			glBindTexture(GL_TEXTURE_2D, blocks_get(id)->textures[FACE_FRONT]);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(fx-0.5f, fy-0.5f, fz+0.5f);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(fx+0.5f, fy-0.5f, fz+0.5f);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(fx+0.5f, fy+0.5f, fz+0.5f);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(fx-0.5f, fy+0.5f, fz+0.5f);
		}
		
		/* Back Face */
		if (mask&2) {
			glBindTexture(GL_TEXTURE_2D, blocks_get(id)->textures[FACE_BACK]);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(fx-0.5f, fy-0.5f, fz-0.5f);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(fx-0.5f, fy+0.5f, fz-0.5f);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(fx+0.5f, fy+0.5f, fz-0.5f);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(fx+0.5f, fy-0.5f, fz-0.5f);
		}

		/* Top Face */
		if (mask&4) {
			glBindTexture(GL_TEXTURE_2D, blocks_get(id)->textures[FACE_TOP]);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(fx-0.5f, fy+0.5f, fz-0.5f);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(fx-0.5f, fy+0.5f, fz+0.5f);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(fx+0.5f, fy+0.5f, fz+0.5f);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(fx+0.5f, fy+0.5f, fz-0.5f);
		}
		
		/* Bottom Face */
		if (mask&8) {
			glBindTexture(GL_TEXTURE_2D, blocks_get(id)->textures[FACE_BOTTOM]);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(fx-0.5f, fy-0.5f, fz-0.5f);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(fx+0.5f, fy-0.5f, fz-0.5f);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(fx+0.5f, fy-0.5f, fz+0.5f);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(fx-0.5f, fy-0.5f, fz+0.5f);
		}

		/* Right face */
		if (mask&16) {
			glBindTexture(GL_TEXTURE_2D, blocks_get(id)->textures[FACE_RIGHT]);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(fx+0.5f, fy-0.5f, fz-0.5f);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(fx+0.5f, fy+0.5f, fz-0.5f);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(fx+0.5f, fy+0.5f, fz+0.5f);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(fx+0.5f, fy-0.5f, fz+0.5f);
		}

		/* Left Face */
		if (mask&32) {
			glBindTexture(GL_TEXTURE_2D, blocks_get(id)->textures[FACE_LEFT]);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(fx-0.5f, fy-0.5f, fz-0.5f);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(fx-0.5f, fy-0.5f, fz+0.5f);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(fx-0.5f, fy+0.5f, fz+0.5f);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(fx-0.5f, fy+0.5f, fz-0.5f);
		}
	glEnd();
	
	if (mask&128)
		glEnable(GL_CULL_FACE);
}
