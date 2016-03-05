#include <stdio.h>
#include <stdlib.h>

#include "gui.h"
#include "drawing2D.h"
#include "texture.h"
#include "log.h"

gui *guis[65536];
int currentGUI = 0;

void gui_init(void) {
	printf("GUI size: %lu\n", sizeof(gui));
}

void gui_draw(void) {
	if (currentGUI == 0) {
		return;
	}
	drawing2D_gray();
}

void gui_open(int id) {
	currentGUI = id;
	log_write(loggingLevel_debug, "Opened GUI %i.", id);
}

void gui_close(void) {
	currentGUI = 0;
}

int gui_current(void) {
	return currentGUI;
}
