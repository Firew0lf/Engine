#ifndef WINDOW_H
#define WINDOW_H

#include <SDL2/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>

void window_init(void);
void window_exit(void);
void window_resize(int w, int h);

void window_render(void);
int window_getFps(void);

SDL_Window *windowMain;
SDL_GLContext *windowMainGLContext;
SDL_Renderer *windowMainRenderer;

int windowWidth;
int windowHeight;

#endif
