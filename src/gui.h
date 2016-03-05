#ifndef GUI_H
#define GUI_H

#include <GL/gl.h>
#include <GL/glu.h>

#include "types.h"

typedef struct {
	float x;
	float y;
	GLuint texture;
	bool ghost:1; // is the slot a ghost slot ?
	unsigned int type:2; // 0: item; 1: fluid; 2: gas; 3: energy (ID behaves like a gauge)
} slot;

typedef struct {
	slot slots[256];
	// TODO something
} gui;


void gui_init(void);
void gui_draw(void);
void gui_open(int id);
void gui_close(void);
int gui_current(void);

#endif
