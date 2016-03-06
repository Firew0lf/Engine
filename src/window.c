#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include <SDL2/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include "main.h"
#include "types.h"
#include "log.h"
#include "drawing3D.h"

const int FLAGS = (SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);

SDL_Window *windowMain;
SDL_GLContext *windowMainGLContext;
SDL_Renderer *windowMainRenderer;

int windowWidth = 640;
int windowHeight = 480;

int fpsCounter = 0;
int fpsNumber = 0;

const char *mainTitle = "Engine";

void window_init(void) {
	// SDL base stuff
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		error(1, SDL_GetError());
	}
	
	if ((windowMain = SDL_CreateWindow("Engine", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, windowWidth, windowHeight, FLAGS)) == NULL) {
		error(1, SDL_GetError());
	}
	SDL_SetWindowMinimumSize(windowMain, 100, 100);
	
	// Renderer stuff
	windowMainGLContext = SDL_GL_CreateContext(windowMain); // yes, it's openGL stuff
	
	int oglId = -1;
	int rdnum = SDL_GetNumRenderDrivers();
	for (int i=0;i<rdnum;i++) {
		SDL_RendererInfo info;
		if (SDL_GetRenderDriverInfo(i, &info)) {
			continue;
		}
		if (!strcmp(info.name, "opengl")) {
			oglId = i;
		}
	}
	if (oglId == -1) {
		error(-1, "Cannot find the OpenGL renderer driver.");
	}
	
	if ((windowMainRenderer = SDL_CreateRenderer(windowMain, oglId, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC)) < 0) {
		error(1, SDL_GetError());
	}
	
	// OpenGL stuff
	
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, true);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	if (SDL_GL_SetSwapInterval(17) < 0) {
		log_write(loggingLevel_warn, "Unable to setup VSync ! %s", SDL_GetError());
	}
	
	glShadeModel(GL_SMOOTH);
	
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	
	//glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
	glClearDepth(1.0f);
	
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(fov, (float)windowWidth/(float)windowHeight, 1.0f, 100.0f);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glViewport(0, 0, windowWidth, windowHeight);
	
	if (glGetError() != GL_NO_ERROR) {
		error(glGetError(), "OpenGL error.");
	}
	
	log_write(loggingLevel_debug, "GL version: %s", glGetString(GL_VERSION));
	log_write(loggingLevel_debug, "GL vendor: %s", glGetString(GL_VENDOR));
	log_write(loggingLevel_debug, "GL renderer: %s", glGetString(GL_RENDERER));
	log_write(loggingLevel_debug, "Video driver: %s", SDL_GetCurrentVideoDriver());
	
	// nothing else to do
}

void window_exit(void) {
	SDL_GL_DeleteContext(windowMainGLContext);
	SDL_DestroyRenderer(windowMainRenderer);
	SDL_DestroyWindow(windowMain);
	SDL_Quit();
}

void window_resize(int w, int h) {
	windowWidth = w;
	windowHeight = h;
	glViewport(0, 0, windowWidth, windowHeight);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(fov, (float)windowWidth/(float)windowHeight, 1.0f, 100.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void window_render(void) {
	//render
	//SDL_RenderPresent(windowMainRenderer);
	SDL_GL_SwapWindow(windowMain);
	
	// reset stuff
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor4f(1.f, 1.f, 1.f, 1.f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	// FPS counter
	fpsCounter++;
}

int window_getFps(void) {
	static int second;
	if (second != time(NULL)) {
		fpsNumber = fpsCounter;
		fpsCounter = 0;
		char *title = malloc(strlen(mainTitle)+20);
		sprintf(title, "%s | %d FPS", mainTitle, fpsNumber);
		SDL_SetWindowTitle(windowMain, title);
		free(title);
		second = time(NULL);
	}
	return fpsNumber;
}

