#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include <SDL2/SDL.h>

#include "main.h"
#include "types.h"
#include "log.h"
#include "drawing3D.h"
#include "drawing2D.h"
#include "window.h"
#include "events.h"
#include "blocks.h"
#include "camera.h"
#include "world.h"
#include "gui.h"

#ifndef DEBUG
void error(int code, const char *err) {
	fprintf(stderr, "FATAL ERROR: %s\nError code: %i.\n", err, code);
	exit(-1);
}
#endif

int main(int argc, char **argv) {
	log_setLevel(loggingLevel_trace);
	
	log_write(loggingLevel_info, "Starting engine version " VERSION);
	
	clock_t ts, tf;
	ts = clock();
	
	window_init();
	blocks_init();
	world_init();
	gui_init();
	
	tf = clock();
	
	log_write(loggingLevel_info, "Engine started, took %f ms", ((float)(tf-ts)/1000));
	
	camera_pos playerCamera;
	camera_moved(&playerCamera, -3.0, 1.0, 0.0);
	while (shouldExit == false) {
		events_handleEvents();
		
		{
			camera_look(playerCamera);
			drawing3D_block(0, 0, 0, 0);
			drawing3D_block(0, 1, 1, 1);
			drawing3D_block(0, 1, 0, 1);
			
			drawing2D_set();
			gui_draw();
			drawing2D_stop();
		}
		
		window_render();
		window_getFps();
	}
	
	blocks_exit();
	window_exit();
	
	return 0;
}
