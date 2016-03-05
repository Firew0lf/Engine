#include <stdio.h>
#include <stdlib.h>

#include <SDL2/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include "main.h"
#include "types.h"
#include "window.h"
#include "drawing3D.h"
#include "log.h"
#include "gui.h"

void events_handleEvents(void) {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
			case SDL_QUIT:
				log_write(loggingLevel_info, "Exiting ...");
				setState(state_exiting);
				break;

			case SDL_WINDOWEVENT:
				if (event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED && event.window.windowID == SDL_GetWindowID(windowMain)) {
					window_resize(event.window.data1, event.window.data2);
				}
				break;
			
			case SDL_KEYDOWN:
				if (event.key.keysym.sym == SDLK_F11 && event.key.repeat == 0) {
					
					static bool state;
					static int winW, winH, winX, winY; // size before fullscreen-ing
					static SDL_DisplayMode win; // same
					if (state == true) {
						state = false;
						SDL_SetWindowFullscreen(windowMain, 0);
						printf("Restore to %ix%i\n", winW, winH);
						
						SDL_SetWindowSize(windowMain, winW, winH);
						SDL_SetWindowPosition(windowMain, winX, winY);
					} else {
						state = true;
						SDL_GetWindowSize(windowMain, &winW, &winH); // backup window size
						SDL_GetWindowPosition(windowMain, &winX, &winY);
						printf("Backup to %ix%i @ %ix%i\n", winW, winH, winX, winY);
						SDL_GetWindowDisplayMode(windowMain, &win);
						SDL_DisplayMode dpmode;
						SDL_GetCurrentDisplayMode(SDL_GetWindowDisplayIndex(windowMain), &dpmode);
						printf("Setting to %ix%i\n", dpmode.w, dpmode.h);
						SDL_SetWindowSize(windowMain, dpmode.w, dpmode.h);
						SDL_SetWindowFullscreen(windowMain, SDL_WINDOW_FULLSCREEN);
					}
					
				} else if (event.key.keysym.sym == SDLK_e && event.key.repeat == 0) {
					if (gui_current() != 0) {
						gui_close();
					} else {
						gui_open(1);
					}
				}
		
		}
	}
}
