#include <stdlib.h>
#include <stdio.h>

#include <SDL2/SDL.h>

#include "lua/lua.h"
#include "lua/lapi.h"
#include "lua/lualib.h"
#include "lua/lauxlib.h"

#include "main.h"
#include "types.h"
#include "log.h"
#include "modloader.h"
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

lua_State *mainState;

void setState(engineState state) {
	currentState = state;
}

engineState currentState = state_undef;
int main(int argc, char **argv) {
	log_setLevel(loggingLevel_trace);
	mainState = luaL_newstate();
	if (!mainState) {
		error(1, "Failed to allocate memory for a lua_State.");
	}
	luaL_openlibs(mainState);
	
	log_write(loggingLevel_info, "Starting engine version " VERSION);
	
	window_init();
	blocks_init();
	world_init();
	gui_init();
	
	int modsNumber = modloader_countMods();
	log_write(loggingLevel_info, "Found %i mods.", modsNumber);
	
	modloader_loadMods(modsNumber);
	
	camera_pos playerCamera;
	camera_moved(&playerCamera, -3.0, 0.0, 0.0);
	while (currentState != state_exiting) {
		events_handleEvents();
		
		{
			camera_look(playerCamera);
			drawing3D_block(0, 0, 0, 0);
			drawing3D_block(0, 1, 1, 1);
			
			drawing2D_set();
			gui_draw();
			drawing2D_stop();
		}
		
		window_render();
		window_getFps();
	}
	window_exit();
	return 0;
}
